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
		case 4:\
			goto L_1_4;break;\
		case 5:\
			goto L_1_5;break;\
	}\
}

int num = 0;
void TASK(1) //Adding
{
	jump_1();
L_1_0:
	current_pc[1] = 1;
	flag = RR();
	if (flag)
		return;
	L_1_1:
	while (i < 20)
	{
		i++;
		current_pc[1] = 2;
		flag = mutex_lock(mutex);
		if (flag)
			return;
	L_1_2:
		flag = RR();
		current_pc[1] = 3;
		if (flag)
			return;
	L_1_3:
		num++;
		printf("[add] num: %d \r\n", num);
		flag = mutex_unlock(mutex);
		current_pc[1] = 4;
		if (flag)
			return;
	L_1_4:
		//flag = RR();
		printf("task1 going to sleeping \n\n");
		flag = task_sleep(1000);
		current_pc[1] = 5;
		//printf("task1 -> flag : %d\n\n", flag);
		if (flag)
			return;
	L_1_5:
		;
	}

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
		case 4:\
			goto L_2_4;break;\
		case 5:\
			goto L_2_5;break;\
	}\
}

void TASK(2) //Adding
{
	jump_2();
	L_2_0:

	current_pc[2] = 1;
	flag = RR();
	if (flag)
		return;
	L_2_1:
	while (j < 20)
	{
		j++;
		flag  = mutex_lock(mutex);
		current_pc[2] = 2;
		if (flag)
			return;
	L_2_2:
		flag = RR();
		current_pc[2] = 3;
		if (flag)
			return;
	L_2_3:
		num--;
		printf("[sub] num: %d \r\n", num);
		flag = mutex_unlock(mutex);
		current_pc[2] = 4;
		if (flag)
			return;
	L_2_4:
		//flag = RR();
		printf("task2 going to sleeping\n\n");
		flag = task_sleep(1000);
		current_pc[2] = 5;
		if (flag)
			return;
	L_2_5:
		;
	}
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
		//printf("the %d time, task_state[1] = %d \n\n", time, task_state[1]);
		if (time < 9)
		{
			A:
			if (current_tid == 1)
				TASK(1);
			else if (current_tid == 2)
				TASK(2);
		}
		else if (time == 9)
		{
			if(time_checker(1))
			//time = 2;
				goto A;
		}
		else if (time == 10)
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