// Giuseppe Raffa
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdbool.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define exit exit(EXIT_SUCCESS);
#define wait wait(NULL);

int main (int argc, char *argv[]) {
	if(argc!=1) {
		fprintf(stderr,"Arguments error\n");
		exit
	}

	if (!fork())
	{
		printf("P1 Pid=%d PidPadre=%d\n",getpid(),getppid());
		exit
	}
	wait

	pid_t pid_2=fork();
	if (pid_2==0)
	{
		//sono in "P2"
		//exit
		if (!fork())
		{
			printf("P2 Pid=%d PidPadre=%d\n",getpid(),getppid());
			exit
		}
		wait

		pid_t pid_5=fork();
		if (pid_5==0)
		{
			printf("P5 Pid=%d PidPadre=%d\n",getpid(),getppid());
			exit
		}
		else
		{
			pid_t pid_4=fork();
			if (pid_4==0)
			{
				//sono in "P4"
				if(!fork())
				{
					printf("P4 Pid=%d PidPadre=%d\n",getpid(),getppid());
					exit	
				}
				wait

				pid_t pid_7=fork();
				if (pid_7==0)
				{
					printf("P7 Pid=%d PidPadre=%d\n",getpid(),getppid());
					exit
				}
				else
				{
					pid_t pid_8=fork();
					if (pid_8==0)
					{
						printf("P8 Pid=%d PidPadre=%d\n",getpid(),getppid());
						exit
					}
					wait
				}
				wait
				wait
				exit
			}
			wait
			wait
			if (!fork())
			{
				printf("P10 Pid=%d PidPadre=%d\n",getpid(),getppid());
				exit
			}
		}
		exit
		
	}

	pid_t pid_3=fork();
	if (pid_3==0)
	{
		if (!fork())
		{
			printf("\tP3 Pid=%d PidPadre=%d\n",getpid(),getppid());
			exit
		}
		wait
		if (!fork())
		{
			printf("\tP6 Pid=%d PidPadre=%d\n",getpid(),getppid());
			exit
		}
		wait
		if (!fork())
		{
			printf("\tP9 Pid=%d PidPadre=%d\n",getpid(),getppid());
			exit
		}
		wait
		if (!fork())
		{
			printf("\tP11 Pid=%d PidPadre=%d\n",getpid(),getppid());
			exit
		}
		wait
		exit
	}
	else
	{
		//sono in PM
		wait
		wait
		pid_t pid_12=fork();
		if (pid_12==0)
		{
			printf("P12 Pid=%d PidPadre=%d\n",getpid(),getppid());
			exit
		}
		wait
		//fine
	}


	return(0);
}
