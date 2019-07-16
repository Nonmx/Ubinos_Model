/*

Test on basic functions of mutex
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
	printf("뮤텍스가 이미 태스크 2에 의해 잠겨졌으므로 태스크 1은 잠든다 (block인 상태)\n\n");
	current_pc[1]++;
	flag = mutex_lock(mutex);
	if (flag)
		return;
L_1_1:
	printf("시점 7 에서 태스크 1이 뮤텍스를 잠금 해제하고\n");
	current_pc[1]++;
	flag = mutex_unlock(mutex);
	if (flag)
		return;
L_1_2:
	printf("시점 8 까지 휴면 sleep을 시도한다\n\n");
	current_pc[1]++;
	flag = task_sleep(1000);
	if (flag)
		return;
L_1_3:
	printf("시점 9 에서 태스크 1이 시점 10 까지를 제한 시간으로 두고 뮤텍스 잠그기를 시도한다\n\n");
	current_pc[1]++;
	flag = mutex_lock_timed(mutex,1000);
	if (flag)
		return;
L_1_4:
	printf("잠금할 수 없지만 시간이 된면 수행할수 있다,\n\n Task1 Termiante\n\n");
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
		case 2:\
			goto L_2_2; break;\
		case 3:\
			goto L_2_3;break;\
		case 4:\
			goto L_2_4;break;\
		case 5:\
			goto L_2_5;break;\
		case 6:\
			goto L_2_6;break;\
		case 7:\
			goto L_2_7;break;\
	}\
}


void TASK(2)
{
	JUMP_2();
L_2_0:
	printf("생성된 태스크 2는 뮤텍스를 잠근다\n\n");
	current_pc[2]++;
	flag = mutex_lock(mutex);
	if (flag)
		return;
L_2_1:
	printf("시점 2에서 높은 우선순위로 태스크1을 생성한다\n\n");
	current_pc[2]++;
	flag = task_create(1);
	if (flag)
		return;
L_2_2:
	printf("시점 4에서 태스크 2가 뮤텍스 잠그기를 다시 한번 시도한다\n\n");
	current_pc[2]++;
	flag = mutex_lock(mutex);
	if (flag)
		return;
L_2_3:
	printf("시점 5 에서 태스크 2가 뮤텍스 잠금 해제를 시도한다\n\n.");
	current_pc[2]++;
	flag = mutex_unlock(mutex);
	if (flag)
		return;
L_2_4:
	printf("시점 6 에서 태스크 2가 다시 한번 뮤텍스 잠금 해제를 시도한다\n\n.");
	current_pc[2]++;
	flag = mutex_unlock(mutex);
	if (flag)
		return;
L_2_5:
	printf("태스크 2가 깨어나서 뮤텍스를 잠그다\n\n");
	current_pc[2]++;
	flag = mutex_lock(mutex);
	if (flag)
		return;
L_2_6:
	printf("마지막인 task2 mutex 해제한다 \n\n");
	current_pc[2]++;
	flag = mutex_unlock(mutex);
	if (flag)
		return;
L_2_7:
	printf("Task2 Terminate\n\n");
	current_pc[2] = 0;
	flag = TerminateTask();
	if (flag)
		return;
}




void main()
{
	mutex_create(mutex);

	printf("시점 1 중간 우선순의로 태스크 2를 생선한다.\n\n");
	task_create(2);
	ubik_comp_start();

	mutex_delete(mutex);
}

int mutex_checker;
int sleep_checker;
void running()
{
	while (current_tid >= 0)
	{
		mutex_checker++;
		sleep_checker++;
		if (mutex_checker < 10 && sleep_checker < 10)
		{
		sleep_time:

			if (current_tid == 1)
				TASK(1);
			else if (current_tid == 2)
				TASK(2);
		}
		else if (sleep_checker == 10)
		{
			if (time_checker(1))
				goto sleep_time;
		}
		else if (mutex_checker == 11)
		{
			mutex_time_checker(mutex,1);
			mutex_checker = 0;
			sleep_checker = 0;
		}

	}
}