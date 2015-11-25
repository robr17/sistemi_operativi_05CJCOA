#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int a,b;

void man (int sig)
{
	if(sig==SIGUSR2)
	{
		printf("Somma = %d\n",a+b);
	}
	else if(sig==SIGUSR1)
	{
		printf("Differenza = %d\n",a-b);
	}
	else
	{
		exit(0);
	}
}

int main (int argc, char **argv)
{	
	(void*) signal (SIGUSR1,man);
	(void*) signal (SIGUSR2,man);
	(void*) signal (SIGINT,man);
	a=atoi(argv[1]);
	b=atoi(argv[2]);
	int n;
	while(1)
	{

	}

	return 0;
}
