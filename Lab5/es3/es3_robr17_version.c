//Roberto Ricci
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

int f1;
char buffer[50];

void manager(int sig) {

	if (sig == SIGUSR1) {
		read(f1, buffer, 50);
		printf("Sono il figlio 1, stampo son1.txt.\n");
		printf("%s\n", buffer);
		printf("Sono il figlio 1, termino.\n");
	}

	return;
}

int main () {

	(void) signal(SIGUSR1, manager);

	pid_t pid1, pid2;
	int f2;

	f1 = open("./son1.txt", O_RDONLY);
	f2 = open("./son2.txt", O_RDONLY);

	pid1 = fork();
	if (pid1) {
		pid2 = fork();
		if (pid2) {
			printf("Ho generato i due figli %d e %d.\n", pid1, pid2);
			printf("Aspetto i due figli.\n");
			wait();
			printf("Uno dei due figli ha terminato.\n");
			wait();
			printf("Anche l'altro ha terminato.\n");
		} else if (!pid2) {
			sleep(5);
			read(f2, buffer, 50);
			printf("Sono il figlio 2, stampo son2.txt e attendo.\n");
			printf("%s\n", buffer);
			sleep(5);
			printf("Sono il figlio 2, termino.\n");
			kill(pid1, SIGUSR1);
			exit(EXIT_SUCCESS);
		}
	} else if (!pid1) {
		sleep(5);
		pause();
		exit(EXIT_SUCCESS);
	}

	return 0;
}
