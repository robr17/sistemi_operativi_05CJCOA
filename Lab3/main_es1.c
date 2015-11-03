// Giuseppe Raffa
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define CHECK_FORK(x) if(x==-1) { \
					  	printf("Fork error\n"); \
					  	exit(EXIT_FAILURE); } 	 

int main (int argc, char *argv[]) {
	if(argc!=3) {
		fprintf(stderr,"Arguments error\n");
		exit(EXIT_FAILURE);
	}

	int i,n,t;
	pid_t pid;
	n=atoi(argv[1]);
	t=atoi(argv[2]);

	for(i=0;i<n;i++) {
		pid=fork();
		CHECK_FORK(pid);
		if(pid) {
			pid=fork();
			CHECK_FORK(pid);
			if(pid) exit(EXIT_SUCCESS);
		}

	}
	sleep(t);
	printf("Exit figlio\n");
	exit(EXIT_SUCCESS);
	return(0);
}
