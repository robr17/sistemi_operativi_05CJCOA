#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <wait.h>

void handler(int sig)
{
}

int main(int argc, char const *argv[])
{
	signal(SIGUSR1,handler);
	signal(SIGUSR2,handler);
	//signal(SIGCHLD,handler);
	
	pid_t p1,p2;

	p1=fork();
	if (p1==0)
	{
		//figlio1
		sleep(2);
		printf("Figlio1: SIGUSR1 inviato\n");
		kill(getppid(),SIGUSR1);
		pause();
		printf("Figlio1: SIGUSR2 ricevuta\n");
		exit(0);
	}
	else
	{
		p2=fork();
		if (p2==0)
		{
			pause();
			printf("Figlio2: SIGUSR1 ricevuto\n");
			printf("Figlio2: SIGUSR2 inviato\n");
			kill(getppid(),SIGUSR2);
			exit(0);
			//figlio2
		}

		//padre
		pause();
		printf("Padre: SIGUSR1 ricevuto\n");
		kill(p2,SIGUSR1);
		pause();
		printf("Padre: SIGUSR2 ricevuto\n");
		kill(p1,SIGUSR2);
		wait(NULL);
		wait(NULL);
		printf("Padre Terminato\n");
		//waitpid(p1,&status,0);
	}

	return 0;
}