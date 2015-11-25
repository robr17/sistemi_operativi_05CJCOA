//Roberto Ricci
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int a, b, res;

void manager (int sig) {

	if (sig == SIGUSR1) {
		res = a + b;
		fprintf(stdout, "Ho ricevuto SIGUSR1, la somma di a e b è %d\n", res);
	} else if (sig == SIGUSR2) {
		res = a - b;
		fprintf(stdout, "Ho ricevuto SIGUSR2, la differenza di a e b è %d\n", res);
	} else if (sig == SIGINT) {
		fprintf(stdout, "Ho ricevuto SIGINT, termino il processo.\n");
		exit(EXIT_SUCCESS);
	}
	return;
}

int main (int argc, char **argv) {

	(void) signal (SIGUSR1, manager);
	(void) signal (SIGUSR2, manager);
	(void) signal (SIGINT, manager);

	if (argc != 3) {
		fprintf(stderr, "Errore nell'immissione dei parametri.\n");
		exit(EXIT_FAILURE);
	}

	a = atoi(argv[1]);
	b = atoi(argv[2]);

	while(1) {}

	return 0;
}
