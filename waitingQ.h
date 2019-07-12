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


int enQ(unsigned char, unsigned char);
int deQ(unsigned char*, unsigned char*);
int get_task_from_WQ(unsigned char*, unsigned char*);

int empty();
int full();

