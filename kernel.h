/*
kernel.h includes prototype of API of ubinos OS
Mapping from OSEK OS model

Date:05/20/2019
Author : Yang Song

*/

#include "config.h"

unsigned char ecode;
unsigned char error[NUM_OF_TASKS];

int task_create(unsigned char);
//mapping from ActivateTASK

int task_suspend(unsigned char);
//mapping from TerminateTask();

int TerminateTask();

//part of task_sleep
int task_sleep(double);
//int task_wakeup(unsigned char, double);
int time_checker(unsigned char);


//void RR(unsigned char); //round robin scheduler

//part of mutex
int mutex_create(mutex_t);
int mutex_delete(mutex_t);
int mutex_lock(mutex_t);
int mutex_unlock(mutex_t);
int mutex_islocked(mutex_t);

//part of semaphore
int sem_create(sem_pt);
int sem_delete(sem_pt);
int sem_take(sem_pt);
int sem_give(sem_pt);


extern int os_on;
extern const int ON;
extern const int OFF;
void ubik_comp_start();
void ShutDownOS();
//mapping from kernel.h
