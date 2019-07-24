#include <assert.h>
//#include "../model/ubinos.h"
#include <stdio.h>
#include "os.h"
#include "readyQ.h"
#include "config.h"
#include <time.h>
//#include "readyQ.c"



int flag;
unsigned char T_id;
unsigned char T_pir;

int be_rear;
int be_front;

unsigned char tp_tid;
unsigned char tp_prio;

//extern unsigned char nondet_uchar();


void main() // verfy the safety of task_create API and round robin scheduler
{

	srand((unsigned)time(NULL));
	for (int i = 0; i < 5; i++)
	{
		//create new task
		//T_id = nondet_uchar();
		//__CPROVER_assume(T_id >= 1 && T_id < NUM_OF_TASKS);
		T_id = rand() %10;
		task_static_info[T_id].prio = rand()%5+1;
		//__CPROVER_assume(task_static_info[T_id].prio >= 1 && task_static_info[T_id].prio < MAX_PRIORITY);
		task_static_info[T_id].max_act_cnt = 1;

		task_dyn_info[T_id].dyn_prio = task_static_info[T_id].prio;
		task_dyn_info[T_id].act_cnt = 0;

		//assert(0);

		be_rear = rear[task_static_info[T_id].prio];
		be_front = front[task_static_info[T_id].prio];

		//previous running task
		tp_tid = current_tid;
		tp_prio = current_prio;
		//assert(0);
		flag = task_create(T_id);
		//assert(flag == 1 ? rear[task_static_info[current_tid].prio] == be_rear + 1 : rear[task_static_info[current_tid].prio] == be_rear + 1);

		//assert(flag == 1 ? front[task_static_info[current_tid].prio] == be_front + 1 : front[task_static_info[T_id].prio] == be_front);
		//assert(flag == 1 ? task_state[current_tid] == Running : task_state[T_id] == Ready);

		flag = reschedule_2(current_tid);

		//assert(flag == 1 ? !(current_tid == tp_tid) && task_static_info[current_tid].prio == task_static_info[tp_tid].prio : current_tid == tp_tid);
		//assert(flag == 1 ? rear[task_static_info[current_tid].prio] == be_rear + 2 : rear[task_static_info[current_tid].prio] == be_rear);
		//assert(flag == 1 ? task_static_info[current_tid].prio == task_static_info[tp_tid].prio : 1);

	}


	for (int i = 0; i < 5; i++)
	{
		flag = TerminateTask();
		assert(flag == 1 ? task_state[T_id] == Suspended : 1);
	}

}
