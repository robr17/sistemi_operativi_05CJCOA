
// Giuseppe Raffa

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define A

int main (int argc, char *argv[]) {
	if(argc!=1) {
		fprintf(stderr,"Arguments error\n");
		exit(-1);
	}

	int i;
	
	#ifdef A
	for(i=1;i<=2;i++){
		if(!fork()){
			printf("%d\n", i);
		}
	}
	printf("%d\n", i);
	#endif

	#ifdef B
	for(i=3;i>1;i--) {
		if(fork())
			printf("%d\n",i);
	printf("%d\n",i);
	}
	#endif

	#ifdef C
	for(i=0;i<2;i++) {
		if(fork())
			fork();
	}
	printf("%d\n",i);
	#endif

	#ifdef D
	for(i=2;i>=1;i--)
		if(!fork())
			printf("%d\n",-i);
		else
			printf("%d\n",i);
	#endif
	return 0;
}