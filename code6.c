#define TASK(t) TASK_##t()
/*
  같은 priority 인 경우에 mutex test
*/

#include "os.h"
#include <stdio.h>
#include <assert.h>
//#include "readyQ.h"


mutex_pt mutex;

int RR();


int task_counter[NUM_OF_TASKS];

int flag;
int counter;
int i = 0;
int j = 0;

#define jump_1(){\
	switch (current_pc[1])\
	{\
		case 0:\
			goto L_1_0;break;\
		case 1:\
			goto L_1_1;break;\
		case 2:\
			goto L_1_2;break;\
		case 3:\
			goto L_1_3;break;\
	}\
}

int num = 0;
void TASK(1) //Adding
{
	jump_1();
	L_1_0:

	current_pc[1]++;
	flag = RR();
	if (flag)
		return;
	L_1_1:
	current_pc[1]++;
	while (i < 20)
	{
		mutex_lock(mutex);
		i++;
		num++;
		printf("[add] num: %d \r\n", num);
		mutex_unlock(mutex);
		//flag = RR();
		flag = task_sleep(1000);
		//printf("task1 -> flag : %d\n\n", flag);
		if (flag)
			return;
	L_1_2:
		;
	}
L_1_3:
	current_pc[1] = 0;
	flag = TerminateTask();
	if (flag)
		return;

}



#define jump_2(){\
	switch (current_pc[2])\
	{\
		case 0:\
			goto L_2_0;break;\
		case 1:\
			goto L_2_1;break;\
		case 2:\
			goto L_2_2;break;\
		case 3:\
			goto L_2_3;break;\
	}\
}

void TASK(2) //Adding
{
	jump_2();
	L_2_0:

	current_pc[2]++;
	flag = RR();
	if (flag)
		return;
	L_2_1:
	current_pc[2]++;
	while (i < 20)
	{
		mutex_lock(mutex);
		i++;
		num--;
		printf("[sub] num: %d \r\n", num);
		mutex_unlock(mutex);
		//flag = RR();
		flag = task_sleep(1000);
		if (flag)
			return;
	L_2_2:
		;
	}
	L_2_3:
	current_pc[2] = 0;
	flag = TerminateTask();
	if (flag)
		return;

}



void main()
{

	mutex_create(mutex);

	task_create(1);
	task_create(2);

	ubik_comp_start();

	mutex_delete(mutex);

}

int time = 0;
void running()
{
	while (current_tid >= 0)
	{
		time++;
		if (time < 3)
		{
			A:
			if (current_tid == 1)
				TASK(1);
			else if (current_tid == 2)
				TASK(2);
		}
		else if (time == 3)
		{
			time_checker(1);
			//time = 2;
			goto A;
		}
		else if (time == 4)
		{
			time_checker(2);
			time = 0;
		}


	}
}

extern int reschedule_2(unsigned char);

int RR()
{
	if ((reschedule_2(current_tid)) != 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}