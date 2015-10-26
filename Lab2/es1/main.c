/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/26/2015 12:00:24 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Umberto Reale (), 
 *   Organization:  
 *
 * =====================================================================================
 */


#include	<stdlib.h>
#include	<stdio.h>
#include	<sys/stat.h>
#include	<sys/types.h>
#include	<fcntl.h>
#include	<unistd.h>
#include	<dirent.h>
#include	<string.h>

void ls_r(char*);

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	int
main ( int argc, char *argv[] )
{
	if (argc != 2) return -1;
	int l = strlen(argv[1]);
	if (argv[1][l-1] == '/')
		argv[1][l-1]='\0';
	ls_r(argv[1]);
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ls_r
 *  Description:  
 * =====================================================================================
*/
void ls_r ( char *path ){
	struct stat mystat;
	char newpath[1000];
	stat(path, &mystat);
	if (S_ISREG(mystat.st_mode))
		return;
	if (S_ISDIR(mystat.st_mode)){
		fprintf(stdout, "%s: \n", path);
		// per ogni file qui presente stampa e ricorre
		DIR* dp = opendir(path);
		struct dirent *dirp;	
		
		// stampa
		while ( (dirp = readdir (dp)) != NULL){
			if (dirp->d_name[0] != '.')
				fprintf(stdout, "%s\t", dirp->d_name);
		}
		fprintf(stdout, "\n");

		// ricorre
		dp = opendir(path);
		while ( (dirp = readdir (dp)) != NULL){
			if (dirp->d_name[0] != '.' ){
				sprintf(newpath, "%s/%s", path, dirp->d_name);
				ls_r(newpath);				
			}
		}
			}
	return;
}		/* -----  end of function ls_r  ----- */
