
// Giuseppe Raffa && Umberto Reale

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
#define BUFFSIZE 512

void cp_r(char *, char*);

int main (int argc, char *argv[]) { // Copiare il I path nel II path, assumo che il II non esista
	if(argc!=3) {
		fprintf(stderr,"Arguments error\n");
		exit(-1);
	}

	DIR *dirp1 = opendir(argv[1]);
	DIR *dirp2 = opendir(argv[2]);
	if (dirp1==NULL) {
		fprintf(stderr, "Path 1 error\n");
		exit(1);
	}
	if (dirp2!=NULL) {
		fprintf(stderr, "Path 2 exist\n");
		exit(1);
	}
	
	cp_r(argv[1],argv[2]);

	return(0);
}

void cp_r(char *path1,char *path2) {
	int fp1,fp2,buff[BUFFSIZE];
	struct stat info;
	struct dirent *dp;
	char ptr[1000];
	char ptr2[1000];
	DIR *dirp1=opendir(path1); //apro la directory sorgente
	stat(path1,&info);
	if(S_ISREG(info.st_mode)) { //usare read e write per copiare file
		fp1=open(path1,O_RDONLY);
		fp2=open(path2,O_WRONLY | O_CREAT, info.st_mode); // info.st_mode mi permette di copiare i file
		while(read(fp1,buff,BUFFSIZE)>0) {		  // nel nuovo direttorio mantenendo i permessi
			write(fp2,buff,BUFFSIZE);
		}
		close(fp1); close(fp2);
		return;
	}
	else {
		mkdir(path2,S_IRWXU | S_IRWXG | S_IRWXO);
		while((dp=readdir(dirp1))!=NULL) {
			if(dp->d_name[0]!='.') {
				sprintf(ptr,"%s/%s",path1,dp->d_name);
				sprintf(ptr2,"%s/%s",path2,dp->d_name);
				cp_r(ptr,ptr2);
			}
		}
	}		
	closedir(dirp1);
}
