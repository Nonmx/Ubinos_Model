/*
	뮤텍스에 의한 우선순의 역전 상황을 방지하는 뮤텍스의
	우선순위 상속 priority inheritance 특성 시험
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
	}\
}


void TASK(1)
{
	JUMP_1();
L_1_0:
	printf("뮤텍스가 이미 태스크 3에 의해 잠겨졌으므로 태스크 1은 잠든다 (block인 상태)\n\n");
	current_pc[1]++;
	flag = mutex_lock(mutex);
	if (flag)
		return;
L_1_1:
	printf("시점 7 에서 태스크를 잠금 해제하고\n\n");


	current_pc[1]++;
	flag = mutex_unlock(mutex);
	if (flag)
		return;
L_1_2:
	printf("종료된다\n\n");
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
	printf("시점 4에서 태스크 2가 수행중이어야 한다\n\n");

L_2_1:

	printf("시점 5에서 태스크 2가 종료된\n\n");
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
		case 3:\
			goto L_3_3;break;\
		case 4:\
			goto L_3_4;break;\
	}\
}


void TASK(3)
{
	JUMP_3();
L_3_0:
	printf("생성된 태스크 3는 뮤텍스를 잠근다\n\n");
	current_pc[3]++;
	flag = mutex_lock(mutex);
	if (flag)
		return;
L_3_1:
	printf("시점 2에서 제일 높은 우선순위로 태스크1을 생성한다\n\n");
	current_pc[3]++;
	flag = task_create(1);
	if (flag)
		return;

L_3_2:
	printf("시점4에서 중간 우선순위로 태스크 2를 생성한다\n\n");
	current_pc[3]++;
	flag = task_create(2);
	if (flag)
		return;
L_3_3:
	printf("시점 6 에서 태스크 2가 뮤텍스 잠금 해제를 시도한다\n\n.");
	current_pc[3]++;
	flag = mutex_unlock(mutex);
	if (flag)
		return;
L_3_4:
	printf("Task3 Terminate\n\n");
	current_pc[2] = 0;
	flag = TerminateTask();
	if (flag)
		return;
}


void main()
{
	mutex_create(mutex);

	printf("시점 1 중간 제일 낮은 우선순위로 태스크 2를 생선한다.\n\n");
	task_create(3);
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

	}
}