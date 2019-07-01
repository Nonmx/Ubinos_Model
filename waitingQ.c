#include "waitingQ.h"
#include "ubinos.h"


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

void enQ(unsigned char tid, unsigned char p)
{
	if (full())
	{
		printf("waittingQ is full!\n");
	}
	else 
	{
		task_state[tid][act_counter[tid]] = Blocked;
		waitingQ[Rear].tid = tid;
		waitingQ[Rear].prio = p;
		Rear = (QSIZE + Rear + 1) % QSIZE;
	}


}

void deQ(unsigned char *tid, unsigned char *prio)
{
	if (empty())
	{
		printf("waitingQ is empty\n");
		current_tid = -1;
	}
	else {
		*tid = waitingQ[Front].tid;
		*prio = waitingQ[Front].prio;

		waitingQ[Front].tid = -1;
		waitingQ[Front].prio = -1;

		Front = (Front + 1) % QSIZE;
		P = *prio;

	}

}