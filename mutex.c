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
	printf("���ؽ��� �̹� �½�ũ 2�� ���� ��������Ƿ� �½�ũ 1�� ���� (block�� ����)\n\n");
	current_pc[1]++;
	flag = mutex_lock(mutex);
	if (flag)
		return;
L_1_1:
	printf("���� 7 ���� �½�ũ 1�� ���ؽ��� ��� �����ϰ�\n");
	current_pc[1]++;
	flag = mutex_unlock(mutex);
	if (flag)
		return;
L_1_2:
	printf("���� 8 ���� �޸� sleep�� �õ��Ѵ�\n\n");
	current_pc[1]++;
	flag = task_sleep(1000);
	if (flag)
		return;
L_1_3:
	printf("���� 9 ���� �½�ũ 1�� ���� 10 ������ ���� �ð����� �ΰ� ���ؽ� ��ױ⸦ �õ��Ѵ�\n\n");
	current_pc[1]++;
	flag = mutex_lock_timed(mutex,1000);
	if (flag)
		return;
L_1_4:
	printf("����� �� ������ �ð��� �ȸ� �����Ҽ� �ִ�,\n\n Task1 Termiante\n\n");
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
	printf("������ �½�ũ 2�� ���ؽ��� ��ٴ�\n\n");
	current_pc[2]++;
	flag = mutex_lock(mutex);
	if (flag)
		return;
L_2_1:
	printf("���� 2���� ���� �켱������ �½�ũ1�� �����Ѵ�\n\n");
	current_pc[2]++;
	flag = task_create(1);
	if (flag)
		return;
L_2_2:
	printf("���� 4���� �½�ũ 2�� ���ؽ� ��ױ⸦ �ٽ� �ѹ� �õ��Ѵ�\n\n");
	current_pc[2]++;
	flag = mutex_lock(mutex);
	if (flag)
		return;
L_2_3:
	printf("���� 5 ���� �½�ũ 2�� ���ؽ� ��� ������ �õ��Ѵ�\n\n.");
	current_pc[2]++;
	flag = mutex_unlock(mutex);
	if (flag)
		return;
L_2_4:
	printf("���� 6 ���� �½�ũ 2�� �ٽ� �ѹ� ���ؽ� ��� ������ �õ��Ѵ�\n\n.");
	current_pc[2]++;
	flag = mutex_unlock(mutex);
	if (flag)
		return;
L_2_5:
	printf("�½�ũ 2�� ����� ���ؽ��� ��״�\n\n");
	current_pc[2]++;
	flag = mutex_lock(mutex);
	if (flag)
		return;
L_2_6:
	printf("�������� task2 mutex �����Ѵ� \n\n");
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

	printf("���� 1 �߰� �켱���Ƿ� �½�ũ 2�� �����Ѵ�.\n\n");
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