// Umberto Reale && Giuseppe Raffa

#include	<stdlib.h>
#include	<stdio.h>
#include	<sys/stat.h>
#include	<sys/types.h>
#include	<fcntl.h>
#include	<unistd.h>
#include	<dirent.h>
#include	<string.h>

void ls_r(char*);

int main ( int argc, char *argv[] ) {
	if (argc != 2) {
		fprintf(stderr, "Error Arguments\n");
		return 1;
	}
	int l = strlen(argv[1]);
	if (argv[1][l-1] == '/' && l>1)
		argv[1][l-1]='\0';
	ls_r(argv[1]);
	return 0;
}

void ls_r (char *path) {
	struct stat mystat;
	char newpath[1000];
	if(lstat(path, &mystat)==EOF) {
		fprintf(stderr, "Error function lstat\n");
		exit(2);
	}
	if (!S_ISDIR(mystat.st_mode)) //sono in un file
		return;
	else {
		fprintf(stdout, "%s: \n", path);
		// per ogni file qui presente stampa e ricorre
		DIR *dp = opendir(path);
		if(dp==NULL) {
			fprintf(stderr, "Error function opendir\n");
			exit(3);
		}
		struct dirent *dirp;
		while ((dirp=readdir(dp))!= NULL){ //stampa dei file contenuti nella directory corrente
			if (dirp->d_name[0] != '.')
				fprintf(stdout, "%s\t", dirp->d_name);
		}
		fprintf(stdout, "\n");
		rewinddir(dp); //ricorsione
		while ((dirp=readdir(dp))!= NULL){
			//printf("[ %s ]\n", dirp->d_name);
			if (dirp->d_name[0] != '.' ){
				if(strcmp(path,"/")==0) sprintf(newpath, "%s%s", path, dirp->d_name);
				else sprintf(newpath, "%s/%s", path, dirp->d_name);
				//fprintf(stderr, "\n[ %s ]\n", newpath);
				ls_r(newpath);				
			}
		}
	}
	return;
}
