// Giuseppe Raffa
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main (int argc, char **argv) {
	int i = 0;
	fprintf (stdout, "%d %d\n", getpid(), ++i);
	execl (argv[0], argv[0], (char *) 0);
	fprintf (stdout, "End program\n");
	return (1);
}

/**
 * In quest'esempio è possibile notare come la system call execl non modifica
 * il pid del processo in esecuzione. Inoltre, dal momento che non ritorna, ma si
 * sostituisce completamente al processo chiamante e considerando che come primo parametro
 * viene passato l'eseguibile stesso, non si ha mai una terminazione.
 * I parametri dell'execl sono, da sinistra a destra:
 * -> argv[0]: eseguibile
 * -> argv[0]: primo parametro per l'eseguibile
 * -> (char*)0: puntatore a NULL, indica la fine dei parametri (poteva essere NULL)
 */