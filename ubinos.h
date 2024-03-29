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
<<<<<<< HEAD
	API_task_create,
	API_task_suspend,
	API_TerminateTask,
	API_task_resume,
=======
	API_task_create, 
	API_task_suspend, 
	API_TerminateTask, 
	API_task_resume, 
>>>>>>> 59709d25f7c376cd156b035c7f3ec64a43fd4d61
	API_task_sleep,
	API_sem_take,
	API_msgq_receive,
	API_mutex_lock,
	API_msgq_send,
	API_sem_give,
	API_mutex_unlock
}API;
extern API api;

<<<<<<< HEAD
typedef enum Mess {
=======
typedef enum Mess{
>>>>>>> 59709d25f7c376cd156b035c7f3ec64a43fd4d61
	PB_KEY_CHANGE_EVT,
	PB_BATT_EVT,
	PB_TIME_EVT,
	PB_BLE_EVT,
	PB_AFE_EVT,
	PB_POPUP_EVT,
	PB_ALARM_EVT,
	PB_PNIP_EVT,
	PB_ACTIVITY_EVT,
	PB_GLUCOSE_EVT,
	PB_PAAR_TAG_EVT,
	PB_PEDOMETER_EVT,
	PB_SMART_CART_TALK_EVT,
	PB_TEST_MSG_EVT,
	PB_QC_EVT,
	PB_BLE_CONTROL_EVT,
	PB_SMART_CAR_TALK_EVT,
	PB_LF_EVT,
	PB_UI_REFRESH_EVT,
	PB_WDT_REFRESH_EVT
}Mess;

Mess MESS;

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
<<<<<<< HEAD
	int flag;// -1 = mutex 없다, 0 = unlocked, 1 = locked
	unsigned char owner;//locked 가지고 있는  task
	unsigned int lock_counter;
	int lock_call[NUM_OF_TASKS];
	unsigned int tra_flag;
=======
	 int flag;// -1 = mutex �뾾�떎, 0 = unlocked, 1 = locked
	 unsigned char owner;//locked 媛�吏�怨� �엳�뒗  task
	 unsigned int lock_counter;
     	 int lock_call[NUM_OF_TASKS];
	 unsigned int tra_flag;
>>>>>>> 59709d25f7c376cd156b035c7f3ec64a43fd4d61
}mutex_pt;


typedef struct {
	int counter;
	unsigned int lock_call[NUM_OF_TASKS];
<<<<<<< HEAD
	//unsigned char Lock; //locked?? task ????
=======
	//unsigned char Lock; //locked占쏙옙 task 占쏙옙占쏙옙
>>>>>>> 59709d25f7c376cd156b035c7f3ec64a43fd4d61
}sem_pt;

#define messageQ_SIZE 25

<<<<<<< HEAD
typedef struct {
=======
typedef struct{
>>>>>>> 59709d25f7c376cd156b035c7f3ec64a43fd4d61
	unsigned char message[messageQ_SIZE];
}MQ;

typedef struct {
	int flag;
	MQ Message_Queue[messageQ_SIZE];
}msgq_pt;

/*typedef struct{
	unsigned char prio;
	unsigned char tid;

}Current;*/ //current information

extern unsigned char current_prio;
extern signed char current_tid;

//Current current[NUM_OF_TASKS];
<<<<<<< HEAD
extern int current_pc[NUM_OF_TASKS + 1];
=======
extern int current_pc[NUM_OF_TASKS+1];
>>>>>>> 59709d25f7c376cd156b035c7f3ec64a43fd4d61

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
