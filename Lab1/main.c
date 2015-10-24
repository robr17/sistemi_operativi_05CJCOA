#include <stdlib.h>
#include <stdio.h>

int main ( int argc, char *argv[] ){
	char c;
	FILE *fr,*fw;
	if(argc!=3) {
		fprintf(stderr,"Error arguments\n");
		exit(1);
	}
	fr=fopen(argv[1],"r");
	fw=fopen(argv[2],"w");
	if (fr==NULL || fw==NULL) {
		fprintf(stderr,"Error file\n");
		exit(2);
	}	
	c=fgetc(fr);
	while(c!=EOF) {
		fputc(c,fw);
		c=fgetc(fr);
	}
	fclose(fr); fclose(fw);
	return 0;
}				



