#ifndef _SIGNI
    #define _SIGNI
	
#include "fxlib.h"
#include "stdio.h"
//#include "string.h"
	
	
	double atof(char *s);
	int power(int x, unsigned int y);
	void nb_sign(void);
	int get_nb_signi(char* str, const char* char_not_allowed);

typedef struct 
	{
	char* str1;
	char op;
	//char* str2;
	} Nombres;



	
	
#endif
