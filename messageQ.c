#include "messageQ.h"
#include "kernel.h"
#include <stdio.h>


int F = 0;
int R = 0;

int MQ_empty()
{
	if (F == R)
		return 0;
	else
		return 1;
}

int MQ_full()
{
	if ((R + 1) % (messageQ_SIZE + 1) == F)
		return 1;
	else
		return 0;
}

int push_message_into_MQ(unsigned char *message)
{
	if (MQ_full())
	{
		printf("messageQ is full!\n\n");
		return 0;
	}
	else
	{
		//*Messahe_Queue->messgae = message;
		for (int i = 0; i < messageQ_SIZE; i++)
		{
			Message_Queue[R].messgae[i] = message[i];
		}
		R = (messageQ_SIZE + R + 1) % messageQ_SIZE;

		return 1;
	}
}

int get_message_from_MQ(unsigned char* message)
{
	if (MQ_empty() == 0)
	{
		printf("messageQ is empty\n\n");
		return 0;
	}
	else
	{
		for (int i = 0; i < messageQ_SIZE; i++)
		{
			message[i] = Message_Queue[F].messgae[i];
		}
		F = (F + 1) % messageQ_SIZE;
		return 1;
	}
}

