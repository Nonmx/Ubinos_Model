

#define QSIZE 15

typedef struct
{
	unsigned char tid;
	unsigned char prio;
}WQ;

//int Front = 0;
//int Rear = 0;

void enQ(unsigned char, unsigned char);
void deQ(unsigned char*, unsigned char*);

int empty();
int full();

