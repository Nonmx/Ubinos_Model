#include "ubinos.h"

<<<<<<< HEAD
//#define messageQ_SIZE 25

/*(typedef struct
{
	unsigned char messgae[messageQ_SIZE];
}MQ;*/

//int Front = 0;
//int Rear = 0;

//MQ Message_Queue[messageQ_SIZE];

int push_message_into_MQ(msgq_pt*,unsigned char*);
int get_message_from_MQ(msgq_pt*,unsigned char*);
=======

int push_message_into_MQ(msgq_pt,unsigned char*);
int get_message_from_MQ(msgq_pt,unsigned char*);
>>>>>>> e94333783459236c94766bd2b4167d37f9f48215

int MQ_empty();
int MQ_full();

