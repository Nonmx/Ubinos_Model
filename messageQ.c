#include "messageQ.h"
#include "kernel.h"
#include <stdio.h>


int F = 0;
int R = 0;

int MQ_empty()
{
	if (F == R)
		return 1;//empty
	else
		return 0;//nonempty
}

int MQ_full()
{
	if ((R + 1) % (messageQ_SIZE + 1) == F)
		return 1;
	else
		return 0;
}

<<<<<<< HEAD
int push_message_into_MQ(msgq_pt *msgq,unsigned char *message)
=======
int push_message_into_MQ(msgq_pt msgq,unsigned char *message)
>>>>>>> e94333783459236c94766bd2b4167d37f9f48215
{
	if (MQ_full())
	{
		printf("messageQ is full!\n\n");
		return 0;
	}
	else
	{
		for (int i = 0; i < messageQ_SIZE; i++)
		{
<<<<<<< HEAD
			msgq->Message_Queue[R].message[i] = message[i];
			//printf("mess is %c", Message_Queue[R].messgae[i]);
		}

=======
			msgq[0].Message_Queue[R].message[i] = message[i];
			//printf("mess is %c", Message_Queue[R].messgae[i]);
		}
		//printf("mess is %s\n\n", Message_Queue->messgae);
>>>>>>> e94333783459236c94766bd2b4167d37f9f48215
		R = (messageQ_SIZE + R + 1) % messageQ_SIZE;

		return 1;
	}
}

<<<<<<< HEAD
int get_message_from_MQ(msgq_pt *msgq , unsigned char* message)
{
	//printf("mess is %s \n\n", Message_Queue->messgae);
	if (MQ_empty())
=======
int get_message_from_MQ(msgq_pt msgq,unsigned char* message)
{
//	printf("mess is %s \n\n", Message_Queue->messgae);
	if (MQ_empty() == 0)
>>>>>>> e94333783459236c94766bd2b4167d37f9f48215
	{
		printf("messageQ is empty\n\n");
		return 0;
	}
	else
	{
		for (int i = 0; i < messageQ_SIZE; i++)
		{
<<<<<<< HEAD
			message[i] = msgq->Message_Queue[F].message[i];
		}
		
=======
			message[i] = msgq[0].Message_Queue[F].message[i];
		}

>>>>>>> e94333783459236c94766bd2b4167d37f9f48215
		//printf("mess is %s \n\n", message);
		F = (F + 1) % messageQ_SIZE;
		return 1;
	}
}

