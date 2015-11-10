// Giuseppe Raffa
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdbool.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define PRINT "Pid: %d --- Pid Padre: %d\n",getpid(),getppid()
#define CHECK(pid) if(pid==-1) {printf(" --> Fork error\n"); exit(EXIT_FAILURE);}
#define EXIT exit(EXIT_SUCCESS);

int main (int argc, char *argv[]) {
	if(argc!=1) {
		fprintf(stderr,"Arguments error\n");
		exit(EXIT_FAILURE);
	}

	pid_t pid,pid_r=0,pid_l=0;
	pid=fork(); //master0
	CHECK(pid)
	if(pid==0) {
		printf("P1" PRINT);
		EXIT
	}
	wait(NULL);//continua master0
	pid_l=fork(); //il master0 crea il master sinistro PL
	CHECK(pid_l)
	if(pid_l==0) { //albero sinistro SONO PL
		if(!fork()) { //P2, il master PL aspetta la sua esecuzione e poi procede avanti
			printf("P2" PRINT);
			EXIT
	}
	wait(NULL);
	pid_t pid_ll=0,pid_lr=0;
	pid_lr=fork();
	if(pid_lr==0) { //sono il figlio PLR
		if(!fork()) { //sono P5
			printf("P5" PRINT);
			EXIT
		}
		wait(NULL);
	}
	else { //devo creare PLL
		pid_ll=fork();
		if(pid_ll==0) { //devo creare P4
			if(!fork()) {
				pid_t pid_lll=0,pid_llr=0;
				pid_lll=fork();
				if(pid_lll==0) { //devo creare P7
					if(!fork()) {
						printf("P7" PRINT);
						EXIT
					}
				wait(NULL);
				}
				else { //devo creare pllr per poi creare p8 
					pid_llr=fork();
					if(!fork()) {
						printf("P8" PRINT);
						EXIT
					}
				wait(NULL);
				}
				wait(NULL);
			}
		}
		wait(NULL); //aspetta l'if precedente
	}
	wait(NULL); //aspetta plr
	//
	//
	//exit
	}
	else {
		pid_r=fork();  //eseguita dal master
		if(pid_r==0) { //il master0 crea il master destro PR 
			//albero destro e creo p3 SONO PR
			//
			//
			//exit
		}
	}
	wait(NULL);
	wait(NULL);




	return(0);
}
