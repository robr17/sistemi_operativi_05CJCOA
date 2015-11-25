#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define BUFF_SIZE 500

int main(int argc, char const *argv[])
{
	char buff[BUFF_SIZE];
	fgets(buff,BUFF_SIZE,stdin);
	
	int i=0;
	
	for(i=0;i<strlen(buff);i++)
		printf("%c",toupper(buff[i]));
	
	return 0;
}