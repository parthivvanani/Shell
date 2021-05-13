/*
	Name: Parthiv Vanani
	Student ID: 110029375
*/
#include "smallsh.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>


int isExit(char**);
int isCD(char**);
int isPiped(char **);
int join(char *[], char*[]);
int isOutputRedirected(char**);
int isCalc(char **);

int runcommand(char **cline, int where)
{
	pid_t pid;
	int status;

	// Requirement 3:
	// Exit/Quit
	if(isExit(cline)) {
		exit(0);
	}

	// Requirement 5:
	// Pipe two command
	if(isPiped(cline) == 1) {
		return -1;
	}			

	// Requirement 1:
	// Chaning the directory with cd command
	if(isCD(cline) == 1) {
		return -1;
	}

	// Requirement 7
	// Calculator 
	if(isCalc(cline) == 1) {
		return -1;
	}

	int fd;
	switch (pid = fork()) {
		case -1:
			perror("smallsh");
			return (-1);
		case 0:
			

			// Requirement 6:
			// Redirection
			if( (fd = isOutputRedirected(cline)) != -1 ) {
				if(!fork()) {
					close(1);
					dup(fd);
				}
				else {
					close(fd);
					wait(NULL);
					exit(1);
				}
			}

			execvp(cline[0], cline);
			perror(*cline);
			exit(1);
	}
	//code for parents
	if (where == BACKGROUND)
	{
		printf("[process id %d]\n", pid);
		return (0);
	}
	
	if (waitpid(pid, &status, 0) == -1)
		return (-1);
	else
		return (status);
}

int isExit(char **cline) {
	if( (strcmp(cline[0], "exit") == 0) || (strcmp(cline[0], "quit") == 0) ) {
		exit(0);
	}
	return 0;
}

int isCD(char **cline) {
	if( strcmp(cline[0], "cd") == 0 ) { 
		//commmand is cd

		if(cline[1] == NULL) {
			char *username = getlogin();
			char path[PATH_MAX] = "/home/";
			strcat(path, username);
			chdir(path);
		}
		else {
			chdir(cline[1]);
		}
		
		return 1;
	}
	return 0;
}

int isPiped(char **cline) {
	
	int found = 0, i = 0, j = 0;

	char *cmd1[MAXBUF], *cmd2[MAXBUF];

	while( cline[i] != NULL)  {
		
		if( strcmp(cline[i], "|") == 0) {
			found = 1;
			cmd1[i++] = (char *)0;
			break;
		}
		cmd1[i] = malloc(MAXBUF * sizeof(char));
		strcpy(cmd1[i], cline[i]);
		i++;

	}


	if( found == 1) {
		printf("Found pipe\n");
		while(cline[i] != NULL) {
			cmd2[j] = malloc(MAXBUF * sizeof(char));
			strcpy(cmd2[j], cline[i]);
			i++; 
			j++;
		}
		join(cmd1, cmd2);
		return 1;
	} else {
		return 0;
	}

}

int join(char *com1[], char *com2[]) {

	int p[2], status;

	switch (fork()) {
		case -1: 
			perror("1st fork call in join");
			exit(3);
		case 0: 
			break;
		default: 
			wait(&status);
			return(status);
	}
	
	//child process's code
	if (pipe(p) == -1){
		perror("pipecall in join ");
		exit(4);
	}

	switch (fork()) {
		case -1:
			perror("2nd fork call failed in join");
			exit(5);
		case 0:  //the writing process (grandchild procss)
			sleep(1);
			printf("Child\n");
			dup2(p[1], 1);  //redirect stdout to the pipe, writing end.
				
			close(p[0]);
			close(p[1]);

			execvp(com1[0], com1);

			perror("1st execvp call failed in join");
			exit(6);
		default: //the "parent" process's code
			printf("parent\n");
			dup2(p[0], 0); //redirect stdin to the pipe, reading end

			close(p[0]);
			close(p[1]);

			execvp(com2[0], com2);

			perror("2nd execvp call failed in join");
			exit(7);
		}
}

int isOutputRedirected(char **cline) {
	int i = 0, found = 0;

	while(cline[i] != NULL ) {
		if ( strcmp(cline[i], ">") == 0) {
			found = 1;
			break;
		}
		i++;
	}

	if(  found = 1) {
		cline[i] = (char *)0;
		int fd = open(cline[i+1], O_WRONLY | O_CREAT , 0777);
		return fd;
	}
	return 0;
}

int isCalc(char **cline) {
	if(strcmp(cline[0], "calculator") == 0) {
		cline[0] = "./calculator";
	}
}