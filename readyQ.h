/*
readyQ.h includes functions and attributes relevant to ready queue of OSEK OS.
Author: Yoohee
Date: 08/09/2016
*/
#include "config.h"
#include "ubinos.h"
//#include "initialize.c"
#ifndef READY_Q_
#define READY_Q_
#define MAX_QUEUE_LENGTH 15

typedef enum {
	ACTIVATE, PREEMPT, RELEASE
}push_type;

typedef struct queue {
	unsigned char tid;
	unsigned char pc; //pc
	unsigned char activation_order;
	push_type type;
}Queue;

extern unsigned char idx;
extern int front[MAX_PRIORITY + 1];
extern unsigned char k;
extern int rear[MAX_PRIORITY + 1];
extern unsigned char max_prio;
extern int size[MAX_PRIORITY + 1];
extern int wholesize;
#define is_full(p) (size[(p)] == MAX_QUEUE_LENGTH-1)
#define is_empty() (wholesize == 0)
extern Queue readyQ[MAX_PRIORITY + 1][MAX_QUEUE_LENGTH];
int reschedule(API api, unsigned char);
int Round_Robin_Schedule();
void push_task_into_readyQ(unsigned char t, unsigned char p, int pc, push_type flag);
void get_task_from_readyQ(unsigned char* t, unsigned char* p);
<<<<<<< HEAD
//mutex ������ �ִ� task ������ 
=======
//mutex 가지고 있는 task 꺼내기 
>>>>>>> 59709d25f7c376cd156b035c7f3ec64a43fd4d61
void get_task_from_readyQ_position(unsigned char*, unsigned char*, mutex_pt*);
//void get_task_form_readyQ_RR(unsigned char *t, unsigned char *p, int);
void initializeQueue();

extern unsigned char min_activation_order[NUM_OF_TASKS + 1];
extern unsigned char max_activation_order[NUM_OF_TASKS + 1];
extern unsigned char cur_activation_order[NUM_OF_TASKS + 1];

#endif
