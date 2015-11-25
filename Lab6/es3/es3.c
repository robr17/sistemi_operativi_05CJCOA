#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFF_SIZE 500
#define SIZE 16

int main(int argc, char const *argv[])
{
	int stream[2];
	pipe(stream);
	pid_t p1;
	p1=fork();
	if (p1==0)
	{
		//figlio
		close(stream[0]);
		FILE *fp;
		fp=fopen("file.txt","r");
		char buff[BUFF_SIZE];
		while(fgets(buff,BUFF_SIZE,fp)!=NULL)
		{
			printf("%s",buff);
			write(stream[1],buff,SIZE);
		}
		exit(0);
	}
	else
	{
		//padre
		printf("Processo Padre\n");
		close(stream[1]);
		read(stream[0],0,SIZE);
	}

	return 0;
}