//Giuseppe Raffa
//Il padre invia al figlio SIGUSR1, SIGUSR2, SIGINT e termina il programma
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

pid_t p1;
int i=0;

void handler(int sig)
{
	if (p1==0)
	{
		//handler figlio
		printf("Figlio: ");
		if (sig==SIGUSR1)
		{
			printf("SIGUSR1\n");
			kill(getppid(),SIGUSR2);
		}
		else if (sig==SIGUSR2)
		{
			printf("SIGUSR2\n");
			kill(getppid(),SIGUSR1);
		}
		else if(sig==SIGINT)
		{
			printf("SIGINT\n");
			kill(getppid(),SIGINT);
		}
		
	}
	else 
	{ //handler padre
		printf("Padre: ");
		if (sig==SIGUSR1)
		{
			printf("SIGUSR1\n");
		}
		else if (sig==SIGUSR2)
		{
			printf("SIGUSR2\n");
		}
		else if(sig==SIGINT)
		{
			printf("SIGINT\n");
		}
	}
}

int main(int argc, char const *argv[])
{
	signal(SIGUSR1,handler);
	signal(SIGUSR2,handler);
	signal(SIGINT,handler);

	p1=fork();
	if (p1==0)
	{
		//figlio
		while(i!=3){
			pause();
			i++;
		}
		printf("Termina figlio\n");
		exit(0);
	}
	else
	{
		//padre
		sleep(2);
		kill(p1,SIGUSR1);
		pause();
		sleep(2);
		kill(p1,SIGUSR2);
		pause();
		sleep(2);
		kill(p1,SIGINT);
		pause();
		printf("Termina Padre\n");
	}
	return 0;
}