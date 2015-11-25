//Roberto Ricci
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

int main (int argc, char **argv) {

	pid_t pid;

	if (argc != 3) {
		fprintf(stderr, "Errore nell'immissione dei parametri.\n");
		exit(EXIT_FAILURE);
	}

	pid = atoi(argv[1]);

	if (!strcmp(argv[2], "somma")) {
		kill(pid, SIGUSR1);
	} else if (!strcmp(argv[2], "differenza")) {
		kill(pid, SIGUSR2);
	} else if (!strcmp(argv[2], "fine")) {
		kill(pid, SIGINT);
	}

	return 0;
}
