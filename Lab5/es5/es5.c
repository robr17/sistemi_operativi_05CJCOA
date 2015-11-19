#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig)
{
	if (sig!=SIGCHLD)
	{
		printf("PidFiglio:%d  PidPadre:%d  Segnale:%d\n",getpid(),getppid(),sig);
	}
	
}

int main(int argc, char const *argv[])
{
	if(argc!=2)
	{
		fprintf(stderr, "Error arguments\n");
		exit(EXIT_FAILURE);
	}
	signal(SIGUSR1,handler);
	signal(SIGCHLD,handler);
	int i,n;
	pid_t pid;
	n=atoi(argv[1]);
	for (i=0;i<n;i++)
	{
		pid=fork();
		if (pid==0)
		{
			printf("Figlio%d  Pid:%d  PidPadre:%d\n",i,getpid(),getppid());
			pause();
			exit(0);
		}
		sleep(2);
		kill(pid,SIGUSR1);
		pause();
	}

	return 0;
}