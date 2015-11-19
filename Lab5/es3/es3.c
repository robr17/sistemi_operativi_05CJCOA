#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <malloc.h>
#include <string.h>

void handler(int sig)
{

}


int main (int argc, char **argv)
{
	pid_t pid;
	pid=fork();
	int f1=open("son1.txt",O_RDONLY);
	int f2=open("son2.txt",O_RDONLY);
	char *buff1,*buff2;
	buff1=(char*)calloc(51,sizeof(char));
	buff2=(char*)calloc(51,sizeof(char));
	if(pid!=0)
	{ //sono nel padre
		if(fork())
		{//sono nel padre
			
		}
		else
		{// secondo figlio
			fprintf(stdout,"Pid2=%d Padre=%d\n",getpid(),getppid());
			read(f2,buff2,50);
			buff2=strcat(buff2,"\n");
			write(1,buff2,51);
			close(f2);
			free(buff2);
			sleep(5);
			
		//exit
		}
	}
	else
	{//primo figlio
		fprintf(stdout,"Pid1=%d Padre=%d\n",getpid(),getppid());
		read(f1,buff1,50);
		buff1=strcat(buff1,"\n");
		write(1,buff1,51);			
		close(f1);
		free(buff1);

	//exit	
	
	}
	return 0;


}
