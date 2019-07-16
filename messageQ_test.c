/*
이 파일은 messageQ test 위한 생성한 파일입니다.
*/


//#include "os.h"
#include <stdio.h>
#include "messageQ.h"
#include "windows.h"


int main()
{
	char M[25] = "i love you!";
	char rec[25];
	push_message_into_MQ(M);

	get_message_from_MQ(rec);
	printf("mess is %s", rec);

	

	running();
	return 0;

	//system("pause");

}

void running()
{
	printf("running!");
}