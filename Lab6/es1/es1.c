#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#define BUFF_SIZE 500

void handler(int sig)
{


}

int main(int argc, char const *argv[])
{
	signal(SIGUSR1,handler);
	signal(SIGCHLD,handler);
	pid_t p1,p2;
	char buff[BUFF_SIZE];

	p1=fork();
	if (p1==0)
	{	
		//figlio1
		pause();
		FILE *file=fopen("test_1.txt","r");
		while(fgets(buff,BUFF_SIZE,file)!=NULL)
		{
			printf("%s", buff);
		}
		printf("\n[ Figlio1 termina esecuzione]\n");
		fclose(file);
		exit(0);
	}
	else
	{
		p2=fork();
		if (p2==0)
		{
			//figlio2
			pause();
			FILE *file=fopen("test_2.txt","r");
			while(fgets(buff,BUFF_SIZE,file)!=NULL)
			{
				printf("%s", buff);
			}
			printf("\n[ Figlio2 termina esecuzione]\n");
			fclose(file);
			exit(0);
		}
		//padre
		sleep(2);
		kill(p1,SIGUSR1);
		pause();
		kill(p2,SIGUSR1);
		pause();
		printf("Padre termina esecuzione\n");
	}
	return 0;
}