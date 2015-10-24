#include	<stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define TRUE 1
#define BUFFSIZE 1024

int main ( int argc, char *argv[] ){
	int c;
	int buff[BUFFSIZE];
	int fr,fw;
	if(argc!=3) {
		fprintf(stderr,"Error arguments\n");
		exit(1);
	}
	fr=open(argv[1],O_RDONLY);
	fw=open(argv[2],O_WRONLY | O_CREAT);
	if (fr==-1) {
		fprintf(stderr,"Error file fr\n");
		exit(2);
	}
	if (fw==-1) {
		fprintf(stderr,"Error file fw\n");
		exit(3);
	}
	c=BUFFSIZE;
	while(read(fr,buff,BUFFSIZE)==BUFFSIZE) {
		if(write(fw,buff,BUFFSIZE)==-1) {
			fprintf(stderr,"Error write\n");
			exit(4);
		}
	}
	close(fr); close(fw);
	return 0;
}



