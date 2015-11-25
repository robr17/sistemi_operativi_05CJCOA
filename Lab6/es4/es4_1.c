#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFF_SIZE 500

int main(int argc, char const *argv[])
{
	char buff[BUFF_SIZE];
	fgets(buff,BUFF_SIZE,stdin);
	execlp("echo","output",buff,NULL);
	return 0;
}