#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

int main (int argc, char **argv)
{
	int pid=atoi(argv[1]);
	
	if(strcmp("SIGUSR1",argv[2])==0)
	{
		kill(pid,SIGUSR1);
	}
	else if(strcmp("SIGUSR2",argv[2])==0)
	{
		kill(pid,SIGUSR2);
	}
	else
		kill(pid,SIGINT);
	

	return 0;
}

