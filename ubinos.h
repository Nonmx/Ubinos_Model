/*
author: yangsong
*/


#ifndef UBINOS_H_
#define UBINOS_H_

/* get configuration from config.h file */
#include "config.h" //config ??
//#include <windows.h>
/* define ERROR codes -- from OSEK/VDX OS specification */
#define E_OK 0
#define E_OS_ACCESS 1
#define E_OS_CALLLEVEL 2
#define E_OS_ID 3
#define E_OS_LIMIT 4
#define E_OS_NOFUNC 5
#define E_OS_RESOURCE 6
#define E_OS_STATE 7
#define E_OS_VALUE 8
#define E_OS_DISABLEDINT 9

/* define ERROR code -- additional ones for managing ready queue. */
#define E_OVER_QUEUE_SIZE 21
#define E_QUEUE_MANAGE 22
#define TEST 23
//ubinos?????????

/* Task states */
typedef enum state {
	Suspended, Ready, Running, Blocked
}State;

typedef enum API {
	API_task_create, API_task_suspend, API_TerminateTask, API_task_resume, API_task_sleep,API_sem_take,API_msgq_receive,BIN
}API;
extern API api;

/* Data structure that store initial configurations */
typedef struct
{
	unsigned char prio;
	unsigned char max_act_cnt;
	//unsigned char preemptable;
}task_static_config;

/* DS to store dynamic state information */
typedef struct {
	unsigned char act_cnt;
	unsigned char dyn_prio;
	unsigned char preemptable;
}task_dynamic_stat;

typedef struct {
	 int flag;//-1 = mutex 없다, 0 = unlocked, 1 = locked
	 unsigned char owner[NUM_OF_TASKS];//locked인 task 지정
	 unsigned int lock_counter;
	 unsigned int lock_call[NUM_OF_TASKS];
}mutex_pt[1];


typedef struct {
	int counter;
	//unsigned char Lock; //locked인 task 지정
}sem_pt[1];

typedef struct {
	unsigned owner[NUM_OF_TASKS];
}msgq_pt[1];

/*typedef struct{
	unsigned char prio;
	unsigned char tid;

}Current;*/ //current information

extern unsigned char current_prio;
extern signed char current_tid;

//Current current[NUM_OF_TASKS];
extern int current_pc[NUM_OF_TASKS];

extern unsigned char e_code;

/*
Arrays to save attributes.
They are actually declared in osek.h
*/
extern task_static_config task_static_info[NUM_OF_TASKS]; //static configuration of tasks
extern task_dynamic_stat task_dyn_info[NUM_OF_TASKS]; //dynamic state of tasks
extern unsigned char task_state[NUM_OF_TASKS]; //state of tasks(??)
extern int PC[NUM_OF_TASKS]; //Program Counter
/* inline functions to get current information of the model. (allocation, event set/clear) */


extern void initialize();
extern void running();
extern void startup_process(unsigned char min, unsigned char max);


//Time-dependent definitions



#endif
