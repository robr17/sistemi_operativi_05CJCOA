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
#include <stdbool.h>
#include <sys/wait.h>
#include <malloc.h>

#define CHECK_FORK if(pid==-1) { fprintf(stderr, "Fork error\n"); exit(EXIT_FAILURE); }

#define vers_1_2

int main (int argc, char *argv[]) {
	if(argc!=1) {
		fprintf(stderr,"Arguments error\n");
		exit(EXIT_FAILURE);
	}

	int n,i,status,*vett_pid,cnt,j;
	pid_t pid;

	printf("Quanti figli si desidera creare? ");
	scanf("%d",&n);
	
	#ifdef vers_1_2
	/**
	 * Il padre deve creare n figli e aspettare la fine
	 * di ognuno di loro prima di terminare la propria esecuzione
	 */
	vett_pid=(int*)calloc(sizeof(int),n);

	for(i=0;i<n;i++) {
		pid=fork();
		CHECK_FORK
		if(pid==0) { //figlio
			break;
		}
		if(pid) {
			vett_pid[i]=pid;
			//printf("scritto pid %d , iterazione %d \n", pid, i);
			if(i+1==n) {
				j=0;
				cnt=0;
				while(cnt!=n) {
					if(waitpid(vett_pid[j],&status,0) && WIFEXITED(status)!=0)
						cnt++;
					else if(WIFEXITED(status)==0) {
						fprintf(stderr, "Error WIFEXITED\n");
						exit(EXIT_FAILURE);
					}
					if(j==n-1)
						j=0;
					j++;
				}
				//fine processo padre
				printf("--> Il padre termina <--\n");
				exit(EXIT_SUCCESS);
			}
		}
	} //da questo punto il codice sarà eseguito solo dai figli
	printf("I'm a child. I've finished\n");
	free(vett_pid);
	
	#else
	/**
	 * Il padre deve creare n figli, ma aspettare la
	 * fine di m figli, m<n, prima di terminare la
	 * propria esecuzione
	 * N.B. Il padre assicura di terminare la propria esecuzione
	 * dopo l'esecuzione di m figli, ma potrebbe terminare dopo
	 * un numero l>m figli
	 */
	int m;

	printf("Quanti figli si desidera aspettare? ");
	scanf("%d",&m);

	vett_pid=(int*)calloc(sizeof(int),m);

	for(i=0;i<n;i++) {
		pid=fork();
		CHECK_FORK
		if(pid==0) { //figlio
			break;
		}
		if(pid) {
			if(i<m) vett_pid[i]=pid;
			if(i+1==n) {
				j=0;
				cnt=0;
				while(cnt!=m) {
					if(waitpid(vett_pid[j],&status,0) && WIFEXITED(status)!=0)
						cnt++;
					else if(WIFEXITED(status)==0) {
						fprintf(stderr, "Error WIFEXITED\n");
						exit(EXIT_FAILURE);
					}
					if(j==m-1)
						j=0;
					j++;
				}
				//fine processo padre
				printf("--> Il padre termina <--\n");
				exit(EXIT_SUCCESS);
			}
		}
	} //da questo punto il codice sarà eseguito solo dai figli
	printf("I'm a child. I've finished\n");
	free(vett_pid);	

	#endif


	return(0);
}
