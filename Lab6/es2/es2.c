#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig)
{
}

int main(int argc, char const *argv[])
{
	signal(SIGCHLD,handler);
	signal(SIGINT,handler);
	
	pid_t p1;
	p1=fork();
	if (p1==0)
	{
		//figlio
		pause();
		printf("Pid_Figlio: %d\n",getpid());
		printf("Figlio termina esecuzione\n");
		exit(0);
	}
	else
	{
		//padre
		sleep(1);
		pause();
		kill(p1,SIGINT);
		pause();
		printf("Padre termina esecuzione\n");
	}
	return 0;
}