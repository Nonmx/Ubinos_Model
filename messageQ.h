#include "ubinos.h"

#define messageQ_SIZE 15

typedef struct
{
	unsigned char messgae[messageQ_SIZE];
}MQ;

//int Front = 0;
//int Rear = 0;

MQ Message_Queue[messageQ_SIZE];

int push_message_into_MQ(unsigned char*);
int get_message_from_MQ(unsigned char*);

int MQ_empty();
int MQ_full();

