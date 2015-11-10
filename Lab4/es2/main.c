// Giuseppe Raffa
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main () {
	char str[100];
	int i;
	fork();
	for (i=0; i<2; i++){
	if (fork()!=0) {
		sprintf (str, "echo system with i=%d", i);
		system (str);
	} else {
		sprintf (str, "exec with i=%d", i);
		execlp ("echo", "myPgrm", str,NULL);
		}
	}
	return (0);
}

/**
 * In questo esempio è evidente come l'uso dell'execlp sia diverso da quello della system.
 * Infatti, se l'execlp fosse sostituita da una system, si avrebbe più output perchè ci sarebbero
 * più processi che eseguirebbero la fork nella seconda iterazione del for. Invece, l'uso della system call
 * execlp fa in modo che i processi che la eseguono, non ritornino più al processo chiamante e quindi
 * terminino la loro esecuzione.
 */