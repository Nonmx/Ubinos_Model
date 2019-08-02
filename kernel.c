<<<<<<< HEAD
/*
kernel.c includes implementation of system services(APIs) of Ubinos.

Author: YangSong
Date: 08/01/2019
=======
ï»¿/*
kernel.c includes implementation of system services(APIs) of OSEK/VDX OS spec.
Now there are only 8 APIs. APIs can be added later.
Author: Yoohee
Date: 08/09/2016
>>>>>>> 59709d25f7c376cd156b035c7f3ec64a43fd4d61
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

<<<<<<< HEAD
//	if (task_static_info[reftask].max_act_cnt == 0)
//		initialize();
=======
	if (task_static_info[reftask].max_act_cnt == 0)
		initialize();
>>>>>>> 59709d25f7c376cd156b035c7f3ec64a43fd4d61

	//check whether max activation count has been reached
	if (reftask < 0 || reftask > NUM_OF_TASKS)
	{
		e_code = E_OS_ID;
		return 0;
	}
	else if (task_dyn_info[reftask].act_cnt < task_static_info[reftask].max_act_cnt)
	{
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
<<<<<<< HEAD

		task_state[tid] = Ready;
		push_task_into_readyQ(tid, task_static_info[tid].prio, 0, 0);

=======
		
		task_state[tid] = Ready;
		push_task_into_readyQ(tid, task_static_info[tid].prio, 0, 0);
		
>>>>>>> 59709d25f7c376cd156b035c7f3ec64a43fd4d61

		//If this task has a higher priority than the current running task
		//push_task_into_readyQ(current_tid, task_static_info[current_tid].prio, 0, PREEMPT);

		if ((reschedule(API_task_create, current_tid)) != 0)//priority based
		{
			return 1;

		}
		else if (Round_Robin_Schedule())//round robin
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


int mutex_create(mutex_pt* mutex)
{
<<<<<<< HEAD
	mutex->flag = 0; // mutex »ý¼º
	mutex->owner = 0;
	mutex->lock_counter = 0;
//	mutex->lock_call[NUM_OF_TASKS] = 0;
	mutex->tra_flag = 0;

=======
	mutex->flag = 0; // mutex ìƒì„±
	
>>>>>>> 59709d25f7c376cd156b035c7f3ec64a43fd4d61
	return 1;
}

unsigned char Before_temp;
unsigned char After_temp;
unsigned char temp_tid;
unsigned char temp_prio;


int mutex_lock(mutex_pt* mutex)
{
	mutex->lock_call[current_tid] = 1;
<<<<<<< HEAD
	if (mutex->flag == 0 && mutex->owner == 0)//first time 
	{
		mutex->flag = 1;
		mutex->owner = current_tid;
=======
	if (mutex->flag == 0 && mutex->owner== 0)//first time 
	{
		mutex->flag = 1;
		mutex->owner= current_tid;
>>>>>>> 59709d25f7c376cd156b035c7f3ec64a43fd4d61
		mutex->lock_counter = 1;
		//mutex[0].call[current_tid]++;

		return 1;
	}
<<<<<<< HEAD
	else if (mutex->lock_counter >= 1 && mutex->owner == current_tid)// mutex ¿©·Á¹ø Àá±ÝÇÒ ¼ö ÀÖ´Ù.
=======
	else if (mutex->lock_counter >= 1 && mutex->owner== current_tid)// mutex ì—¬ë ¤ë²ˆ ìž ê¸ˆí•  ìˆ˜ ìžˆë‹¤.
>>>>>>> 59709d25f7c376cd156b035c7f3ec64a43fd4d61
	{
		mutex->lock_counter++;
		return 1;
	}
	else
	{
		if (task_static_info[mutex->owner].prio < task_static_info[current_tid].prio)
		{
			mutex->tra_flag = 1;
			After_temp = current_prio;
			Before_temp = task_static_info[mutex->owner].prio; // unlock

			task_state[current_tid] = Blocked;
<<<<<<< HEAD
			push_task_into_WQ(current_tid, current_prio); // ¼öÇàÁßÀÎ task°¡ lock µÉ ¼ö ¾øÀ¸¸é waitQ·Î push ÇÑ´Ù
			int loc = 0;
			for (loc = front[task_dyn_info[mutex->owner].dyn_prio]; loc < rear[task_dyn_info[mutex->owner].dyn_prio]; loc++)
			{
				//mutex °¡Áö°í ÀÖ´Â task ²¨³¾ ¶§ ±îÁö 
				get_task_from_readyQ_position(&temp_tid, &temp_prio, mutex);
				if (temp_tid == mutex->owner)
				{
					task_dyn_info[temp_tid].dyn_prio = After_temp; // priorit inherit
					push_task_into_readyQ(temp_tid, task_dyn_info[temp_tid].dyn_prio, current_pc[temp_tid], PREEMPT); // mutex°¡Áö°í ÀÖ´Â ³·Àº priorityÀÎ task°¡ ¸ÕÀú readyQ¿¡¼­ ²¨³»¼­ priority »ó¼ÓÇÑ ´ÙÀ½¿¡ readyQ·Î ´Ù½Ã push ÇÑ´Ù
=======
			push_task_into_WQ(current_tid, current_prio); // ìˆ˜í–‰ì¤‘ì¸ taskê°€ lock ë  ìˆ˜ ì—†ìœ¼ë©´ waitQë¡œ push í•œë‹¤
			int loc = 0;
			for(loc = front[task_dyn_info[mutex->owner].dyn_prio];loc< rear[task_dyn_info[mutex->owner].dyn_prio];loc++)
			{
				//mutex ê°€ì§€ê³  ìžˆëŠ” task êº¼ë‚¼ ë•Œ ê¹Œì§€ 
				get_task_from_readyQ_position(&temp_tid,&temp_prio,mutex);
				if(temp_tid == mutex->owner)
				{
					task_dyn_info[temp_tid].dyn_prio = After_temp; // priorit inherit
					push_task_into_readyQ(temp_tid, task_dyn_info[temp_tid].dyn_prio, current_pc[temp_tid], PREEMPT); // mutexê°€ì§€ê³  ìžˆëŠ” ë‚®ì€ priorityì¸ taskê°€ ë¨¼ì € readyQì—ì„œ êº¼ë‚´ì„œ priority ìƒì†í•œ ë‹¤ìŒì— readyQë¡œ ë‹¤ì‹œ push í•œë‹¤
>>>>>>> 59709d25f7c376cd156b035c7f3ec64a43fd4d61
					break;
				}
				else
				{
<<<<<<< HEAD
					push_task_into_readyQ(temp_tid, task_dyn_info[temp_tid].dyn_prio, current_pc[temp_tid], PREEMPT);
=======
					push_task_into_readyQ(temp_tid,task_dyn_info[temp_tid].dyn_prio,current_pc[temp_tid],PREEMPT						);
>>>>>>> 59709d25f7c376cd156b035c7f3ec64a43fd4d61
				}
			}
			return reschedule(API_mutex_lock, current_tid);


		}
		else
		{
			task_state[current_tid] = Blocked;
			push_task_into_WQ(current_tid, current_prio);
			return reschedule(API_mutex_lock, current_prio);
		}
	}
}


int mutex_unlock(mutex_pt* mutex)
{
<<<<<<< HEAD
	if (mutex->flag == 1 && mutex->lock_counter == 1 && mutex->lock_call[current_tid] > 0)
	{
		if (mutex->tra_flag > 0) // priority ºÏ±¸
=======
	if (mutex->flag == 1  && mutex->lock_counter == 1 && mutex->lock_call[current_tid] > 0)
	{
		if (mutex->tra_flag > 0) // priority ë¶êµ¬
>>>>>>> 59709d25f7c376cd156b035c7f3ec64a43fd4d61
		{
			mutex->tra_flag = 0;
			task_dyn_info[current_tid].dyn_prio = task_static_info[current_tid].prio;
			push_task_into_readyQ(current_tid, task_dyn_info[current_tid].dyn_prio, current_pc[current_tid], PREEMPT);


		}
		mutex->flag = 0;
		mutex->owner = 0;
		mutex->lock_counter = 0;
		mutex->lock_call[current_tid] = 0;
<<<<<<< HEAD
		get_task_from_WQ(&temp_tid, &temp_prio); // blockÁßÀÎ tid Å‰µæ
		if (is_sleeping() && mutex->lock_call[temp_tid] > 0) // Áö±Ý waitQ¿¡¼­(block) task°¡ ÀÖÀ¸¸é ±×¸®°í ÇØ´çtask ÀÌ¹Ì mutex_lock È£ÃâÇÏ¸é 
		{
			//blockµÈ task ¼öÇàµÉ ¶§ mutex °¡Áö°í ÀÖ´Â »óÅÂ·Î resume
=======
		get_task_from_WQ(&temp_tid,&temp_prio); // blockì¤‘ì¸ tid í­ë“
		if (is_sleeping() && mutex->lock_call[temp_tid] > 0) // ì§€ê¸ˆ waitQì—ì„œ(block) taskê°€ ìžˆìœ¼ë©´ ê·¸ë¦¬ê³  í•´ë‹¹task ì´ë¯¸ mutex_lock í˜¸ì¶œí•˜ë©´ 
		{	
			//blockëœ task ìˆ˜í–‰ë  ë•Œ mutex ê°€ì§€ê³  ìžˆëŠ” ìƒíƒœë¡œ resume
>>>>>>> 59709d25f7c376cd156b035c7f3ec64a43fd4d61


			task_state[temp_tid] = Ready;
			mutex->flag = 1;
			mutex->owner = temp_tid;
			mutex->lock_counter = 1;
<<<<<<< HEAD
			push_task_into_readyQ(temp_tid, temp_prio, current_pc[temp_tid], PREEMPT);//readyQ·Î Ãß°¡ÇØ¼­ ¹Ù·Î ½ÇÇàÇÏÁö ¾Ê´Â´Ù.
			return reschedule(API_mutex_unlock, current_tid); // ³ôÀº priority ÀÎ TASK°¡ ÀÖÀ¸¸é preempt ÇØ¾ß ÇÑ´Ù.

=======
			push_task_into_readyQ(temp_tid, temp_prio, current_pc[temp_tid], PREEMPT);//readyQë¡œ ì¶”ê°€í•´ì„œ ë°”ë¡œ ì‹¤í–‰í•˜ì§€ ì•ŠëŠ”ë‹¤.
			return reschedule(API_mutex_unlock,current_tid); // ë†’ì€ priority ì¸ TASKê°€ ìžˆìœ¼ë©´ preempt í•´ì•¼ í•œë‹¤.
			
>>>>>>> 59709d25f7c376cd156b035c7f3ec64a43fd4d61
		}

		return 1;
	}
	else if (mutex->lock_counter > 1)
	{
		mutex->lock_counter--;
		return 1;
	}
	else
	{
		return 0;
	}
}

int mutex_islocked(mutex_pt* mutex)
{
	if (mutex->flag == 1)
		return 1;//locked
	else
		return 0;//unlocked
}

int mutex_delete(mutex_pt* mutex)
{
	mutex->flag = -1;
	return 1;
}




<<<<<<< HEAD
int mutex_time_checker(mutex_pt* mutex, unsigned char tid)//
{

	if (mutex->lock_call[tid] == 99 && mutex->flag == 0 && mutex->owner == 0)
	{
		mutex->flag = 1;
		mutex->owner = tid;
		mutex->lock_counter = 1;
		return 1;
	}
	else if (mutex->lock_call[tid] == 99 && mutex->flag >= 1 && mutex->owner == tid)
	{
		mutex->lock_counter++;
		return 1;
	}
	else if (mutex->lock_call[tid] == 99 && !(mutex->owner == tid))
	{
		return 0;
	}
}


int mutex_lock_timed(mutex_pt* mutex, unsigned int time)
=======
int mutex_time_checker(mutex_pt* mutex,unsigned char tid)//
{
	
		if (mutex->lock_call[tid] == 99 && mutex->flag == 0 && mutex->owner == 0)
		{
			mutex->flag = 1;
			mutex->owner = tid;
			mutex->lock_counter = 1;
			return 1;
		}
		else if (mutex->lock_call[tid] == 99 && mutex->flag >= 1 && mutex->owner == tid)
		{
			mutex->lock_counter++;
			return 1;
		}
		else if (mutex->lock_call[tid] == 99 && !(mutex->owner == tid))
		{
			return 0;
		}
}


int mutex_lock_timed(mutex_pt* mutex,unsigned int time) 
>>>>>>> 59709d25f7c376cd156b035c7f3ec64a43fd4d61
{
	mutex->lock_call[current_tid] = 99;

	return 1;
}




int sem_create(sem_pt* sem)
{
	sem->counter = 0;
	return 1;
}

int sem_delete(sem_pt* sem)
{
	sem->counter = -1;
	return 1;
}

int sem_give(sem_pt* sem)
{
	if (!(empty()))
	{
<<<<<<< HEAD
		get_task_from_WQ(&temp_tid, &temp_prio);
		push_task_into_readyQ(temp_tid, temp_prio, current_pc[temp_tid], PREEMPT);
		return reschedule(API_sem_give, current_tid);
		//	return 1;// ³ôÀº priority task ÀÖÀ¸¸é ¹Ù·Î ¼öÇà
	//	else return 0;//³ôÀº priority ¾øÀ¸¸é Round robin ¹ß»ý°¡´É¼ºÀÌ ÀÖ´Ù.
=======
		get_task_from_WQ(&temp_tid,&temp_prio);
		push_task_into_readyQ(temp_tid, temp_prio, current_pc[temp_tid], PREEMPT);
		return reschedule(API_sem_give, current_tid);
		//	return 1;// ë†’ì€ priority task ìžˆìœ¼ë©´ ë°”ë¡œ ìˆ˜í–‰
	//	else return 0;//ë†’ì€ priority ì—†ìœ¼ë©´ Round robin ë°œìƒê°€ëŠ¥ì„±ì´ ìžˆë‹¤.
>>>>>>> 59709d25f7c376cd156b035c7f3ec64a43fd4d61
	}
	else
	{
		sem->counter = sem->counter + 1;
		return 1;
	}
}


int sem_take(sem_pt* sem)
{
	if (sem->counter > 0)
	{
		sem->counter = sem->counter - 1;
		return 1;

	}
	else
	{
		push_task_into_WQ(current_tid, current_prio);
		return(reschedule(API_sem_take, current_tid));
	}
}

<<<<<<< HEAD
int sem_take_timed(sem_pt* sem, unsigned int timed)
{
	sem->lock_call[current_tid] = 99; // ¾î´À ÅÂ½ºÅ©°¡ sem_task_time API È£ÃâÇÏ´ÂÁö ±â·Ï
=======
int sem_take_timed(sem_pt* sem, unsigned int timed) 
{
	sem->lock_call[current_tid] = 99; // ì–´ëŠ íƒœìŠ¤í¬ê°€ sem_task_time API í˜¸ì¶œí•˜ëŠ”ì§€ ê¸°ë¡
>>>>>>> 59709d25f7c376cd156b035c7f3ec64a43fd4d61
}

int sem_time_checker(sem_pt* sem, unsigned char tid)
{
	if (sem->lock_call[tid] == 99)
	{
		if (sem->counter > 0)
		{
			sem->counter = sem->counter - 1;
			return 1;
		}
		else
		{
			push_task_into_WQ(tid, task_dyn_info[tid].dyn_prio);
			return (reschedule(API_sem_take, tid));
		}
	}
}


//message Q
int msgq_create(msgq_pt* msgq_p, unsigned int msgsize, unsigned int maxcount) //for noting
{
<<<<<<< HEAD
	//message staticÀûÀ¸·Î ±¸Çö
=======
	//message staticì ìœ¼ë¡œ êµ¬í˜„
>>>>>>> 59709d25f7c376cd156b035c7f3ec64a43fd4d61
	msgq_p->flag = 1; //created scuessful
	return 1;
}



<<<<<<< HEAD
int msgq_send(msgq_pt* msgq_p, unsigned char* message)
{
	if (!(empty()) && msgq_p->flag == 1)
	{
		get_task_from_WQ(&temp_tid, &temp_prio);
		push_task_into_readyQ(temp_tid, temp_prio, current_pc[temp_prio], PREEMPT);
		return reschedule(API_msgq_send, current_tid);
	}
	else if (msgq_p->flag == 1)
	{
		push_message_into_MQ(msgq_p, message);
=======
int msgq_send(msgq_pt* msgq_p , unsigned char* message) 
{
	if (!(empty()) && msgq_p->flag == 1)
	{
		get_task_from_WQ(&temp_tid,&temp_prio);
		push_task_into_readyQ(temp_tid, temp_prio, current_pc[temp_prio], PREEMPT);
		return reschedule(API_msgq_send, current_tid);
	}
	else if(msgq_p->flag == 1)
	{
		push_message_into_MQ(msgq_p,message);
>>>>>>> 59709d25f7c376cd156b035c7f3ec64a43fd4d61
		return 1;

	}
	else return 0;
}

int msgq_receive(msgq_pt* msgq_p, unsigned char* message)
{
<<<<<<< HEAD
	if (!(MQ_empty()) && msgq_p->flag == 1)
	{
		get_message_from_MQ(msgq_p, message);
		return 1;
	}
	else if (msgq_p->flag == 1)
=======
	if (!(MQ_empty ()) && msgq_p->flag == 1)
	{
		get_message_from_MQ(msgq_p,message);
		return 1;
	}
	else if(msgq_p->flag == 1)
>>>>>>> 59709d25f7c376cd156b035c7f3ec64a43fd4d61
	{
		push_task_into_WQ(current_tid, current_prio);
		return(reschedule(API_msgq_receive, current_tid));
	}
	else return 0;
}

int os_on;
const int ON = 1;
const int OFF = 0;

void ubik_comp_start()
{
	if (os_on == OFF)
	{
		os_on = ON;
<<<<<<< HEAD
//		running(); //call tasks here
=======
		running(); //call tasks here
>>>>>>> 59709d25f7c376cd156b035c7f3ec64a43fd4d61
	}
}

void ShutDownOS()
{
	if (os_on == ON)
	{
		os_on = OFF;
	}
}
