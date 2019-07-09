#include "ubinos.h"

#define messgaeQ_SIZE 15

typedef struct
{
	unsigned char messgae[messgaeQ_SIZE];
}MQ;

//int Front = 0;
//int Rear = 0;

MQ Messahe_Queue[messgaeQ_SIZE];

int push_message_into_MQ(unsigned char*);
int get_message_from_MQ(unsigned char*);

int MQ_empty();
int MQ_full();

