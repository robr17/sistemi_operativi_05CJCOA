//Roberto Ricci
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#define N 10
#define M 5

/*	Se definito il padre attende tutti gli N figli creati e termina.
	Se non definito il padre attende gli ultimi M<N figli creati e termina.
*/
#define switch

int main (int argc, char **argv) {

	int i, status;
	pid_t pid_v[N], pid;

	for (i=0; i<N; i++) {
		pid = fork();
		if (pid < 0) {
			fprintf(stderr, "Errore nella generazione del processo figlio.\n");
			exit(EXIT_FAILURE);
		} else if (pid == 0) {
			fprintf(stdout, "Termina il processo figlio PID = %d PPID = %d.\n", getpid(), getppid());
			exit(EXIT_SUCCESS);
		} else if (pid) {
			pid_v[i] = pid;
		}
	}
	
	#ifdef switch

	for (i=0; i<N; i++) {
		waitpid(pid_v[i], &status, 0);
		if (!WIFEXITED(status)) {
			printf("Uno dei processi non è stato eseguito correttamente.\n");
			exit(EXIT_FAILURE);
		}
	}

	#else

	for (i=N-1; i>=M; i--) {
		waitpid(pid_v[i], &status, 0);
		if (!WIFEXITED(status)) {
			printf("Uno dei processi non è stato eseguito correttamente.\n");
			exit(EXIT_FAILURE);
		}
	}

	#endif

	fprintf(stdout, "Termina il processo padre PID = %d.\n", getpid());

	exit(EXIT_SUCCESS);
}
