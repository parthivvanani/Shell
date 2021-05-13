/*
	Name: Parthiv Vanani
	Student ID: 110029375
*/
#include "smallsh.h"
#include <unistd.h>
#include <limits.h>

// command arg1 arg2 arg3
static char inpbuf[MAXBUF], tokbuf[2 * MAXBUF], *ptr = inpbuf, *tok = tokbuf;

int inarg(char c);

int userin() {
	int c, count;
	ptr = inpbuf;
	tok = tokbuf;


	//requirement 2: Path and dollar printed in the prompt
	char p[PATH_MAX] = "";

	getcwd(p, PATH_MAX);

	printf("%s$ ", p);
	count = 0;

	

	while (1)
	{

		if ((c = getchar()) == EOF)
			return(EOF);
		if (count < MAXBUF)
			inpbuf[count++] = c;
		if (c == '\n' && count < MAXBUF)
		{
			inpbuf[count] = '\0';
			return count;
		}
		
		if (c == '\n') 
		{
			printf("smallsh: input line too long\n");
			count = 0;
			printf("%s$ ", p);
		}

		
	}

//	printf("inpbuf=%s\n", inpbuf);
}

int gettok(char **outptr) {
	int type;
	
	*outptr = tok;
	
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	
	*tok++ = *ptr;
	
	switch (*ptr++) {
	case '\n':
		type = EOL;
		break;
	case '&':
		type = AMPERSAND;
		break;
	case ';':
		type = SEMICOLON;
		break;
	default:
		type = ARG;
		
		while (inarg(*ptr))
			*tok++ = *ptr++;
	}
	*tok++ = '\0';
	return type;
}

//****************************************************************************************
static char special[] = { ' ', '\t', '&', ';', '\n', '\0' };
int inarg(char c) {
	char *wrk;
	for (wrk = special; *wrk; wrk++)
	{
		if (c == *wrk)
			return (0);
	}
	return (1);
}

