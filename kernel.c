/*
kernel.c includes implementation of system services(APIs) of OSEK/VDX OS spec.
Now there are only 8 APIs. APIs can be added later.
Author: Yoohee
Date: 08/09/2016
*/
#include <stdio.h>
#include "ubinos.h"
#include "kernel.h"
#include "readyQ.h"
#include "mylib.h"
#include "waitingQ.h"
#include "messageQ.h"

//part of task_sleep


extern void eventually(int);

extern unsigned char max_activation_order[NUM_OF_TASKS + 1];
extern unsigned char cur_activation_order[NUM_OF_TASKS + 1];
API api;
extern signed char current_tid;
unsigned char current_prio;
//unsigned char e_code;
extern int act_counter[NUM_OF_TASKS + 1];
int task_create(unsigned char reftask)
{
	api = API_task_create;

	if (task_static_info[reftask].max_act_cnt == 0)
		initialize();

	//check whether max activation count has been reached
	if (reftask < 0 || reftask > NUM_OF_TASKS)
	{
		e_code = E_OS_ID;
		return 0;
	}
	else if (task_dyn_info[reftask].act_cnt < task_static_info[reftask].max_act_cnt)
	{
		if (task_state[reftask] == Suspended)
		{
			int i;
			//When it is transferred from suspended state, then all events are cleared.
			for (i = 0; i < NUM_EVENTS; i++)
			{
				//Event_Table[i].task_alloc[reftask] = 0; //Cleared
			}
		}
		task_dyn_info[reftask].act_cnt++;
		push_task_into_readyQ(reftask, task_static_info[reftask].prio, 0, 0);
	}
	else
	{
		e_code = E_OS_LIMIT;

		return 0;
	}
	/* background task of Erika? */
	if (current_tid == -1) {
		current_tid = reftask;
		return reschedule(API_task_create, current_tid);
	}
	return reschedule(API_task_create, current_tid);
}

int TerminateTask()
{
	api = API_TerminateTask;
	/*if (has_resource(current_tid))
	{
		e_code = E_OS_RESOURCE;

	}*/
	if (task_dyn_info[current_tid].act_cnt > 0)
		task_dyn_info[current_tid].act_cnt--;
	if (task_dyn_info[current_tid].act_cnt > 0)
	{
		task_state[current_tid] = Ready;
		//eventually(current_tid);
	}
	else
	{
		task_state[current_tid] = Suspended;
	}
	min_activation_order[current_tid] = cur_activation_order[current_tid] + 1;
	return reschedule(API_TerminateTask, current_tid);
}

int task_suspend(unsigned char reftask)// implement later
{
	return 0;
}




unsigned char task_tid;
//double task_time;
int task_sleep(double time)
{

	if (task_state[current_tid] == Running)
	{
		api = API_task_sleep;
		task_state[current_tid] = Blocked;
		//printf("task_state[%d] = %d", current_tid, task_state[current_tid]);
		return(reschedule(API_task_sleep, current_tid));

		//return current_tid;
	}
	else if (task_state[current_tid] == Suspended)
	{
		return 0; //
	}

}




int time_checker(unsigned char tid)//Wake up the task
{
	if (task_state[tid] == Blocked)
	{
		
		task_state[tid] = Ready;
		push_task_into_readyQ(tid, task_static_info[tid].prio, 0, 0);
		

		//If this task has a higher priority than the current running task
		//push_task_into_readyQ(current_tid, task_static_info[current_tid].prio, 0, PREEMPT);

		if ((reschedule(API_task_create, current_tid)) != 0)//priority based
		{
			return 1;

		}
		else if ((reschedule_2(current_tid)) != 0)//round robin
		{
			return 1;
		}
		else
		{
			return 0; //Not up to the appointed time
		}
	}
	else
	{
		return 0;
	}
}


int mutex_create(mutex_pt mutex)
{
	mutex[0].flag = 0; // mutex 생성
}

unsigned char task_list[NUM_OF_TASKS]; 

int mutex_lock(mutex_pt mutex)
{
	mutex[0].lock_call[current_tid] = 1;
	if (mutex[0].flag == 0 && mutex[0].owner[current_tid] == 0)//first time 
	{
		mutex[0].flag = 1;
		mutex[0].owner[current_tid] = 1;
		mutex[0].lock_counter = 1;
		//mutex[0].call[current_tid]++;

		return 0;
	}
	else if (mutex[0].lock_counter >= 1 && mutex[0].owner[current_tid] == 1)// mutex 여려번 잠금할 수 있다.
	{
		mutex[0].flag = 1;
		mutex[0].owner[current_tid] = 1;
		mutex[0].lock_counter++;
		return 0;
	}
	else
	{
		task_state[current_tid] = Blocked;
		enQ(current_tid,current_prio);
		reschedule(current_tid, current_prio);
		return 1;
	}
}


int mutex_unlock(mutex_pt mutex)
{
	if (mutex[0].flag == 1 && mutex[0].owner[current_tid] == 1 && mutex[0].lock_counter == 1 && mutex[0].lock_call[current_tid] > 0)
	{
		mutex[0].flag = 0;
		mutex[0].owner[current_tid] = 0;
		mutex[0].lock_counter = 0;
		mutex[0].lock_call[current_tid] = 0;
		get_task_from_WQ(TID, PRI); // block중인 tid 흭득
		if (is_sleeping() && mutex[0].lock_call[TID[0]] > 0) // 지금 sleeping아닌 waitQ에서(block) task가 있으면 그리고 해당task 이미 mutex_lock 호출하면 
		{	
			//block된 task 수행될 때 mutex 가지고 있는 상태로 resume
			task_state[TID[0]] = Blocked;
			mutex[0].flag = 1;
			mutex[0].owner[TID[0]] = 1;
			mutex[0].lock_counter = 1;
			push_task_into_readyQ(TID[0], PRI[0], 0, PREEMPT);//readyQ로 추가해서 바로 실행하지 않는다.
			return 1;
		}
		return 0;
	}
	else if (mutex[0].owner[current_tid] == 1 && mutex[0].lock_counter > 1)
	{
		mutex[0].flag = 1;
		mutex[0].owner[current_tid] = 1;
		mutex[0].lock_counter--;
	}
	else
	{
		return 0;
	}
}

int mutex_islocked(mutex_pt mutex)
{
	if (mutex[0].flag == 1)
		return 1;//locked
	else
		return 0;//unlocked
}

int mutex_delete(mutex_pt mutex)
{
	mutex[0].flag = -1;
	return 1;
}




/*int mutex_time_checker(mutex_pt mutex)
{
	if (mutex[0].flag == 0 && mutex[0].owner[current_tid] == 0) //first time 잠금
	{
		mutex[0].flag == 1;
		mutex[0].owner[current_tid] = 1;
		mutex[0].lock_counter = 1;
	}
	else if (mutex[0].lock_counter >= 1 && mutex[0].owner[current_tid] == 1)
	{
		mutex[0].lock_counter++;
	}
	else
	{
		return 0;
	}
}

int mutex_lock_timed(mutex_pt mutex,unsigned int time) 
{
	mutex[0].call = 1;

}*/




int sem_create(sem_pt sem)
{
	sem[0].counter = 0;
	return 1;
}

int sem_delete(sem_pt sem)
{
	sem[0].counter = -1;
	return 1;
}

int sem_give(sem_pt sem)
{
	if (!(empty()))
	{
		push_task_into_readyQ(current_tid,current_prio,0, PREEMPT);
		deQ(&current_tid, &current_prio);
		return 1;
	}
	else
	{
		sem[0].counter = sem[0].counter + 1;
	}
}


int sem_take(sem_pt sem)
{
	if (sem[0].counter > 0)
	{
		sem[0].counter = sem[0].counter - 1;
		return 1;

	}
	else
	{
		enQ(current_tid, current_prio);
		return (reschedule(API_sem_take, current_tid));
	}
}

int sem_take_timed(sem_pt sem, unsigned int timed) //和普通的sem_take 没啥区别
{
	if (sem[0].counter > 0)
	{
		sem[0].counter = sem[0].counter - 1;
		return 1;
	}
	else
	{
		enQ(current_tid, current_prio);
		return (reschedule(API_sem_take, current_tid));
	}
}


//message Q
int msgq_create(msgq_pt msgq_p, unsigned int msgsize, unsigned int maxcount) //for noting
{
	return 1;
}

int msgq_send(msgq_pt msgq_p , unsigned char* message) 
{
	if (!(MQ_empty()))
	{
		push_task_into_readyQ(current_tid, current_prio, 0, PREEMPT);
		deQ(&current_tid, &current_prio);
		return 1;
	}
	else
	{
		push_message_into_MQ(message);
		return 1;

	}
}

int msgq_receive(msgq_pt msgq_p, unsigned char* message)
{
	if (MQ_empty() == 1)
	{
		get_message_from_MQ(message);
		return 0;
	}
	else
	{
		enQ(current_tid, current_prio);
		return(reschedule(API_msgq_receive, current_tid));
	}
}

int os_on;
const int ON = 1;
const int OFF = 0;

void ubik_comp_start()
{
	if (os_on == OFF)
	{
		os_on = ON;
		running(); //call tasks here
	}
}

void ShutDownOS()
{
	if (os_on == ON)
	{
		os_on = OFF;
	}
}
