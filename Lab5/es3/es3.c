//Giuseppe Raffa
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <malloc.h>
#include <string.h>

void handler(int sig)
{
	if(sig==SIGUSR1)
	{
		int f=open("son1.txt",O_RDONLY);
		char *buff;
		buff=(char*)calloc(51,sizeof(char));
		fprintf(stdout,"Pid1=%d Padre=%d\n",getpid(),getppid());
		read(f,buff,50);
		buff=strcat(buff,"\n");
		write(1,buff,51);
		close(f);
		free(buff);
	}
	else if(sig==SIGUSR2)
	{
		int f=open("son2.txt",O_RDONLY);
		char *buff;
		buff=(char*)calloc(51,sizeof(char));
		fprintf(stdout,"Pid2=%d Padre=%d\n",getpid(),getppid());
		read(f,buff,50);
		buff=strcat(buff,"\n");
		write(1,buff,51);
		close(f);
		free(buff);
		sleep(5);
	}
	//invio SIGCHLD
}


int main (int argc, char **argv)
{
	signal(SIGUSR1,handler);
	signal(SIGUSR2,handler);
	signal(SIGCHLD,handler);
	pid_t pid1,pid2;
	pid1=fork();
	if(pid1!=0)
	{ //sono nel padre
		pid2=fork();
		if (pid2==0)
		{	//secondo figlio
			pause();
			exit(0);
		}
	}
	else
	{//primo figlio
		pause();
		exit(0);
	}
	sleep(5);
	kill(pid2,SIGUSR2);
	pause();
	kill(pid1,SIGUSR1);
	pause();
	printf("Padre Termina\n");
	return 0;
}
