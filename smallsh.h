/*
	Name: Parthiv Vanani
	Student ID: 110029375
*/

#include <sys/wait.h>
#include <stdio.h>



//#include <sys/wait.h>

#define EOL 1 
#define ARG 2 

#define AMPERSAND 3 
#define SEMICOLON 4 
#define MAXARG 512 
#define MAXBUF 512 

#define FOREGROUND 0 
#define BACKGROUND 1

int userin();
void procline(void);
