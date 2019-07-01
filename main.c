#include <stdio.h>

typedef struct
{
	int i;
}A[1];

void plus(A);

int umain()
{
	A a;
	a[0].i = 0;
	plus(a);
	printf("%d", a[0].i);
	
}

void plus(A a)
{
	a[0].i = 1;
}

