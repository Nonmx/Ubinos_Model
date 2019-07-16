/*
	���ؽ��� ���� �켱���� ���� ��Ȳ�� �����ϴ� ���ؽ���
	�켱���� ��� priority inheritance Ư�� ����
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
	printf("���ؽ��� �̹� �½�ũ 3�� ���� ��������Ƿ� �½�ũ 1�� ���� (block�� ����)\n\n");
	current_pc[1]++;
	flag = mutex_lock(mutex);
	if (flag)
		return;
L_1_1:
	printf("���� 7 ���� �½�ũ�� ��� �����ϰ�\n\n");


	current_pc[1]++;
	flag = mutex_unlock(mutex);
	if (flag)
		return;
L_1_2:
	printf("����ȴ�\n\n");
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
	printf("���� 4���� �½�ũ 2�� �������̾�� �Ѵ�\n\n");

L_2_1:

	printf("���� 5���� �½�ũ 2�� �����\n\n");
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
	printf("������ �½�ũ 3�� ���ؽ��� ��ٴ�\n\n");
	current_pc[3]++;
	flag = mutex_lock(mutex);
	if (flag)
		return;
L_3_1:
	printf("���� 2���� ���� ���� �켱������ �½�ũ1�� �����Ѵ�\n\n");
	current_pc[3]++;
	flag = task_create(1);
	if (flag)
		return;

L_3_2:
	printf("����4���� �߰� �켱������ �½�ũ 2�� �����Ѵ�\n\n");
	current_pc[3]++;
	flag = task_create(2);
	if (flag)
		return;
L_3_3:
	printf("���� 6 ���� �½�ũ 2�� ���ؽ� ��� ������ �õ��Ѵ�\n\n.");
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

	printf("���� 1 �߰� ���� ���� �켱������ �½�ũ 2�� �����Ѵ�.\n\n");
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