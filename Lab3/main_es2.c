// Giuseppe Raffa
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>

int main (int argc, char *argv[]) {
	if(argc!=2) {
		fprintf(stderr,"Arguments Error\n");
		exit(EXIT_FAILURE);
	}
	
	int n, *array, i;
	pid_t pid;

	n=atoi(argv[1]);
	array=(int*)malloc(sizeof(int)*n);
	if(array==NULL) {
		fprintf(stderr, "Malloc error\n");
		exit(EXIT_FAILURE);
	}

	printf("Inserire %d interi: \n",n);
	for(i=0;i<n;i++) {
		scanf("%d",&array[i]);
	}

	//devo creare n-1 processi più il processo padre
	
	for(i=0;i<n;i++) {
		if((pid=fork())==-1)	{
			fprintf(stderr, "Fork error\n");
			exit(EXIT_FAILURE);
		}
		else if(pid) { //sono nel padre
			wait();
			printf("%d ", array[i]);
			exit(EXIT_SUCCESS);
			//break;
		}
		else { //sono nel figlio
			continue;
		}
	}
	//printf("\n");
	free(array);

	return(0);
}