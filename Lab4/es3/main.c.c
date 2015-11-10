// Giuseppe Raffa, Umberto Reale, Marco Sapei
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

#define PRINT " Pid: %d --- Pid Padre: %d\n",getpid(),getppid()
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
		wait(NULL); //rimane il padfe di P2, cioè PL
		pid_t pid_ll=0,pid_lr=0;
		pid_lr=fork(); //??
		if(pid_lr==0) { //sono il figlio PLR
			if(!fork()) { //sono P5
				printf("P5" PRINT);
				EXIT
			}
			wait(NULL);
			EXIT /**forse ?????????**/
		} //da qui in poi solo PL è ancora vivo
		else { //devo creare PLL
			pid_ll=fork();
			if(pid_ll==0) { //devo creare P4
				if(!fork()) { //sono P4
					printf("P4" PRINT);
					EXIT
				}
				wait(NULL); //colui che aspetta è PLL
				//printf("sono qua\n");
				pid_t pid_lll=0,pid_llr=0;
				pid_lll=fork();
				if(pid_lll==0) { //devo creare P7
					if(!fork()) {
						printf("P7" PRINT);
						EXIT
					}
					wait(NULL);
					EXIT /** forseeeeeeeeeee **/
				}
				else { //devo creare pllr per poi creare p8
					pid_llr=fork();
					if(pid_llr==0) {
						if(!fork()) {
							printf("P8" PRINT);
							EXIT
						}
						wait(NULL);
						EXIT /** forseeeeeeeeeeeeeee **/
					}
				}
				//- - -
				//printf("sono qua\n");
				wait(NULL);
				EXIT /*** forseeeeeeeeeeeeeee ***/
			}/**chiusura if(pid_ll==0)**/
				//printf("sono qua\n");
		}
		//- qui 4 fottuti processi di MINKIA!!!!!!!
		//printf("sono qua");
		wait(NULL); //aspetta l'if precedente
		wait(NULL); //aspetta plr
		if(!fork()) {
			printf("P10" PRINT);
			EXIT
		}
		wait(NULL);
		EXIT
	}
	else {
		pid_r=fork();  //eseguita dal master
		if(pid_r==0) { //il master0 crea il master destro PR
			if(!fork()) {
				printf("P3" PRINT);
				EXIT
			}		
			wait(NULL);
			if(!fork()) {
				printf("P6" PRINT);
				EXIT
			}		
			wait(NULL);
			if(!fork()) {
				printf("P9" PRINT);
				EXIT
			}		
			wait(NULL);
			if(!fork()) {
				printf("P11" PRINT);
				EXIT
			}		
			wait(NULL);
			EXIT
		}
	}
	wait(NULL);

	wait(NULL);
	if(!fork()) {
		printf("P12" PRINT);
		EXIT
	}		


	return(0);
}
