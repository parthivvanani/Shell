/*
	Name: Parthiv Vanani
	Student ID: 110029375
*/
#include "smallsh.h"
#include <unistd.h>

int timeout = 0;




void alarmHandler(int dummy );

int main()
{
	signal(SIGALRM, alarmHandler);
	alarm(10);



	while (userin() != EOF){
		alarm(0);
		if(timeout == 1) {
			timeout = 0;
			signal(SIGALRM, alarmHandler);
			alarm(10);
			continue;
		}
		procline();
		alarm(10);
	}
		
}


void alarmHandler(int dummy ) {
	timeout = 1;
	fprintf(stderr, "\nPlease enter a command...");
	char *temp;

	scanf("%m", temp);
	fflush(stdin);
}