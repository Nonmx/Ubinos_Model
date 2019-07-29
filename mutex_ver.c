#include <stdio.h>
#include "os.h"
#include <time.h>
#include <windows.h>
#include <assert.h>
#include "readyQ.h"



int flag;

unsigned char T_id[5] = {1,2,3,4,5};

unsigned char tp_tid;
unsigned char tp_prio;
mutex_pt mutex;

extern int Round_Rpbin_Schedule();

void main()
{
	flag = mutex_create(mutex);
	if (flag)
		printf("mutex create sucess\n\n");
	else
		printf("mutex create failed\n\n");

	srand((unsigned)time(NULL));

	int s = 0;
	for (int j = 0; j < 5; j++)
	{
		s++;
		//task_static_info[T_id[i]].prio = rand() % 5 + 1;
		//printf("the priority : %d of Tid: %d \n\n", task_static_info[T_id[i]].prio, T_id[i]);
		task_static_info[T_id[j]].prio = s;
		task_static_info[T_id[j]].max_act_cnt = 1;
		task_dyn_info[T_id[j]].dyn_prio = task_static_info[T_id[j]].prio;
		task_dyn_info[T_id[j]].act_cnt = 0;
	}



	for (int i = 0; i < 5; i++)
	{
		flag = task_create(T_id[i]);
		if (flag)
			printf("task_create is created sucess,the tid of running : %d \n\n", current_tid);
		else printf("task_create failed the tid of running : %d \n\n", current_tid);

		tp_tid = current_tid;
		tp_prio = current_prio;

		flag = Round_Rpbin_Schedule();
		if (flag)
			printf("round robin sucess and before round robin tid : %d \n after round robin tid : %d\n\n", tp_tid, current_tid);
		else printf("round robin failed and before round robin tid : %d \n after round robin tid : %d\n\n", tp_tid, current_tid);


		flag = mutex_lock(mutex);
		if (flag)
			printf("mutex_lock sucessful\n, the mutex owner is tid : %d\n\n", mutex[0].owner);
		else printf("mutex_lock failed \n, the mutex owner is tid : %d\n\n", mutex[0].owner);

		srand((unsigned)time(NULL));
		int checker = rand() % 1 + 0;
		printf("checker is %d\n\n", checker);
		if (checker)
		{
			flag = mutex_unlock(mutex);
			if (flag)
				printf(" mutex unlock sucessful \n, the mutex owner is tid : %d\n\n", mutex[0].owner);
			else printf("mutex unlock failed \n, the mutex owner is tid : %d\n\n", mutex[0].owner);
		}


	}

	while (current_tid >= 0)
	{
		flag = TerminateTask();
	}

	assert(current_tid == -1);
}