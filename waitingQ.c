#include "waitingQ.h"
#include "ubinos.h"
#include <stdio.h>


WQ waitingQ[NUM_OF_TASKS];
int act_counter[NUM_OF_TASKS + 1];
int P;
int Front = 0;
int Rear = 0;

int empty()
{
	if (Front == Rear)
		return 1;
	else
		return 0;
}

int full()
{
	if ((Rear + 1) % (QSIZE +1)  == Front)
		return 1;
	else
		return 0;
}  

int enQ(unsigned char tid, unsigned char p)
{
	if (full())
	{
		printf("waittingQ is full!\n");
		return 0;
	}
	else 
	{
		//printf("enQ -> rear: %d\n\n", Rear);
		task_state[tid] = Blocked;
		//printf("task_state[tid][act_counter[tid]] = %d \n", task_state[tid]);
		waitingQ[Rear].tid = tid;
		waitingQ[Rear].prio = p;
		Rear = (QSIZE + Rear + 1) % QSIZE;
		return 1;
	}


}

int deQ(unsigned char *tid, unsigned char *prio)
{
	if (empty())
	{
		printf("waitingQ is empty\n");
		//current_tid = -1;
		current_tid = 0;
		current_prio = 0;
		P = 0;
		return 0;
	}
	else {
		*tid = waitingQ[Front].tid;
		*prio = waitingQ[Front].prio;

		waitingQ[Front].tid = -1;
		waitingQ[Front].prio = -1;

		Front = (Front + 1) % QSIZE;
		P = *prio;

		return 1;

	}

}


int get_task_from_WQ(unsigned char* tid, unsigned char* prio) //not running
{
	if (empty())
	{
		printf("waitingQ is empty\n");
		//current_tid = -1;
		return 0;
	}
	else {
		//printf("deQ -> get_task_from_WQ ->front : %d\n\n", Front);
		TID[0] = waitingQ[Front].tid;
		PRI[0] = waitingQ[Front].prio;

		waitingQ[Front].tid = -1;
		waitingQ[Front].prio = -1;

		Front = (Front + 1) % QSIZE;
		P = *prio;

		return 1;

	}

}