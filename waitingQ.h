#include "ubinos.h"

#define QSIZE 15

typedef struct
{
	unsigned char tid;
	unsigned char prio;
}WQ;

//int Front = 0;
//int Rear = 0;

unsigned char TID[1];
unsigned char PRI[1];


int push_task_into_WQ(unsigned char, unsigned char);
int get_task_from_WQ();

int empty();
int full();

