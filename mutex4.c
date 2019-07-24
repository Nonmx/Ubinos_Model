/*
	 priority inheritance test
*/

#define TASK(t) TASK_##t()

#include <stdio.h>
#include "os.h"

int task_counter[NUM_OF_TASKS];
int flag;

mutex_pt mutex;


#define JUMP_1(){\
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
	}\
}


void TASK(1)
{
	JUMP_1();
L_1_0:
	printf("task1 mutex lock 호출한다\n\n");
	current_pc[1]++;
	flag = mutex_lock(mutex);
	if (flag)
		return;
L_1_1:
	printf("task1에서 task2가 create한다\n\n");
	flag = task_create(2);
	current_pc[1]++;
	if (flag)
		return;
L_1_2:
	printf("at this point, the priority of task1 is %d\n\n", task_dyn_info[1].dyn_prio);
	printf("after task3, task1 is going to Running and create task4\n\n");
	current_pc[1]++;
	flag = task_create(4);
	if (flag)
		return;
L_1_3:
	current_pc[1]++;
	printf("at this point, the priority of task1 is %d\n\n", task_dyn_info[1].dyn_prio);
	printf("after task4, task1 going to mutex_unlock\n\n");
	flag = mutex_unlock(mutex);
	printf("at this point, the priority of task1 is %d\n\n", task_dyn_info[1].dyn_prio);
	if (flag)
		return;
L_1_4:
	printf("task1 terminate\n\n");
	current_pc[1] = 0;
	flag = TerminateTask();
	if (flag)
		return;

}


#define JUMP_2(){\
	switch (current_pc[2])\
	{\
		case 0:\
			goto L_2_0; break;\
		case 1:\
			goto L_2_1; break;\
	}\
}


void TASK(2)
{
	JUMP_2();
L_2_0:
	current_pc[2]++;
	printf("i am task2, i am going to create task3\n\n");
	flag = task_create(3);
	if (flag)
		return;

L_2_1:

	printf("task2 going to Terminate\n\n");
	current_pc[2] = 0;
	flag = TerminateTask();
	if (flag)
		return;


}

#define JUMP_3(){\
	switch (current_pc[3])\
	{\
		case 0:\
			goto L_3_0; break;\
		case 1:\
			goto L_3_1; break;\
		case 2:\
			goto L_3_2; break;\
	}\
}


void TASK(3)
{
	JUMP_3();
L_3_0:
	printf("i am task3 , i am going to lock the mutex \n\n");
	current_pc[3] =1 ;
	flag = mutex_lock(mutex);
	if (flag)
		return;
L_3_1:
	printf("task3\n\n");

	printf("task3는 unlcok API 호출할 것이다.\n\n");
	current_pc[3] = 2;
	flag = mutex_unlock(mutex);
	if (flag)
		return;
L_3_2:
	printf("Task3 Terminate\n\n");
	current_pc[3] = 0;
	flag = TerminateTask();
	if (flag)
		return;
}


#define JUMP_4(){\
	switch (current_pc[4])\
	{\
		case 0:\
			goto L_4_0; break;\
		case 1:\
			goto L_4_1; break;\
		case 2:\
			goto L_4_2; break;\
	}\
}


void TASK(4)
{
	JUMP_4();
L_4_0:
	printf("i am task4 , i am going to lock the mutex \n\n");
	current_pc[4]++;
	flag = mutex_lock(mutex);
	if (flag)
		return;
L_4_1:
	printf("task4\n\n");
	printf("task4는 unlcok API 호출할 것이다.\n\n");
	current_pc[4]++;
	flag = mutex_unlock(mutex);
	if (flag)
		return;

L_4_2:
	printf("Task4 Terminate\n\n");
	current_pc[4] = 0;
	flag = TerminateTask();
	if (flag)
		return;
}


void main()
{
	mutex_create(mutex);

	printf("main함수에서 task1 create 할 것이다 \n\n");
	task_create(1);
	ubik_comp_start();

	mutex_delete(mutex);
}

int mutex_checker;
int sleep_checker;
void running()
{
	while (current_tid >= 0)
	{
		if (current_tid == 1)
			TASK(1);
		else if (current_tid == 2)
			TASK(2);
 		else if (current_tid == 3)
			TASK(3);
		else if (current_tid == 4)
			TASK(4);

	}
}