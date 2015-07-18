#include "signi.h"

#include "EasyInput.h"

#define Print(str) Print((const unsigned char *)(str))

void str_copy(char* from, char* to)
{
if(from!=NULL)
{
while(*from)
{
*from=*to;
from++;
to++;
}
return;
}
}

double atof(char *s)
{
	double a = 0.0;
	int e = 0;
	int c;
	while ((c = *s++) != '\0' && isdigit(c)) {
		a = a*10.0 + (c - '0');
	}
	if (c == '.') {
		while ((c = *s++) != '\0' && isdigit(c)) {
			a = a*10.0 + (c - '0');
			e = e-1;
		}
	}
	if (c == 'e' || c == 'E') {
		int sign = 1;
		int i = 0;
		c = *s++;
		if (c == '+')
			c = *s++;
		else if (c == '-') {
			c = *s++;
			sign = -1;
		}
		while (isdigit(c)) {
			i = i*10 + (c - '0');
			c = *s++;
		}
		e += i*sign;
	}
	while (e > 0) {
		a *= 10.0;
		e--;
	}
	while (e < 0) {
		a *= 0.1;
		e++;
	}
	return a;
} 

int power(int x, unsigned int y)
{
    if( y == 0)
        return 1;
    else if (y%2 == 0)
        return power(x, y/2)*power(x, y/2);
    else
        return x*power(x, y/2)*power(x, y/2);
 
}

int get_nb_signi(char* str, const char* char_not_allowed)
{
short i=0,j=0,str_ind=0;
char length=strlen(str);

for(j=0;j<strlen(char_not_allowed);j++)
	{
	while(*(str+str_ind)==*(char_not_allowed+j)) 
		{
		str_ind++; 
		i++; 
		}
	}
while(*(str+str_ind))
	{
	if(*(str+str_ind)=='.') 
		{
		i++;
		str_ind++;
		}
	str_ind++;
	}
return length-i;
}

Nombres Input_str(int length)
{
unsigned int key = 0;
char *string;
char buffer[50];
char cursor[] = {0xE6,  0xD7, 0};
int i;
int row=2;
char char_add = 0 ; // savoir si on appuie sur la bonne touche

Nombres nombres;

string = (char*)malloc(sizeof(char) * length + 1);

for(i = 0; i <= 20; i++) string[i] = 0;

i=0;
	
	
while(key!=KEY_CTRL_EXE)
	{
	Bdisp_AllClr_DDVRAM();
	locate(1,row);
	Print(string);
	
	sprintf(buffer,"%c",nombres.op);
	locate(1,row);
	Print(buffer);
	Print(cursor);
	
		
	GetKey(&key);

	 switch(key)
		{
		case KEY_CHAR_0 : key='0'; char_add = 1;  break;
		case KEY_CHAR_1 : key='1'; char_add = 1;  break;
		case KEY_CHAR_2 : key='2'; char_add = 1;  break;
		case KEY_CHAR_3 : key='3'; char_add = 1;  break;
		case KEY_CHAR_4 : key='4'; char_add = 1;  break;
		case KEY_CHAR_5 : key='5'; char_add = 1;  break;
		case KEY_CHAR_6 : key='6'; char_add = 1;  break;
		case KEY_CHAR_7 : key='7'; char_add = 1;  break;
		case KEY_CHAR_8 : key='8'; char_add = 1;  break;
		case KEY_CHAR_9 : key='9'; char_add = 1;  break;
		case KEY_CHAR_PLUS : 
			{
			str_copy(string, nombres.str1);
			key = nombres.op = '+'; 
			nombres.op = '+'; 
			char_add = 0; 
			break;
			}
		case KEY_CHAR_MINUS : case KEY_CHAR_PMINUS : 
			{
			str_copy(string, nombres.str1);
			key = nombres.op = '-'; 
			nombres.op = '-'; 
			char_add = 0; 
			break;
			}
		case KEY_CHAR_MULT : 
			{
			str_copy(string, nombres.str1);
			key = nombres.op = '*'; 
			nombres.op = '*'; 
			char_add = 0; 
			break;
			}
		case KEY_CHAR_DIV : 
			{
			str_copy(string, nombres.str1);
			key = nombres.op = '/'; 
			 nombres.op = '/';
			char_add = 0; 
			break;
			}
		case KEY_CHAR_EXP :  key = 'e'; char_add = 1;  break;
		case KEY_CTRL_DEL:
			if(i > 0)
				{
				i--;
				string[i] = 0; 
				}
			break;
			char_add = 0;
		}

		if(char_add==1)
			{
			string[i]=key;
			i++;
			}
		
		char_add = 0; 	
	}

return nombres;

}

void nb_sign()
{
char *str , *p=str;
unsigned int key = 0;
int row=2;
int nb_char;
char buffer[50];
short i=0; // i sert à savoir le nombre de caractères que l'on enlève par rapport à la chaine de départ ('0' et '.')
short op;
char turn=0;
double results[2];
char nb_signi[3];
double result;
Nombres nombres;



while(1)
	{
	
	
	nombres=Input_str(20);
	Bdisp_AllClr_DDVRAM();
	locate(1,2);
	Print(nombres.str1);
	
	sprintf(buffer,"%c",nombres.op);
	locate(1,3);
	Print(buffer);
	
	GetKey(&key);
	
	/* EI_init();
	EI_manage_config(EI_SET_COLUMN, 1);
	EI_manage_config(EI_SET_ROW, row);
	EI_manage_config(EI_SET_START_MODE, EI_NORMAL);
	str=EI_input_string(16,(const char*)"0123456789.-e"); 

	results[turn]=atof(str); //on stoke nos résultats

	nb_signi[turn]=get_nb_signi(str, "-.e0"); // on stoke le nombre de chiffres significatifs

	sprintf(buffer,"[%d]",get_nb_signi(str, "-.e0"));
	locate(get_nb_signi(str, "-.e0")+2,row);
	Print(buffer);
	row++;

	/* on re initialise 
	i=0;
	nb_char=0;

	
	
	if(turn==0) 
		{
		while(1)
			{
			
			
			switch(key)
				{
				case KEY_CHAR_PLUS : results[2]=1; sprintf(buffer,"+"); break;
				case KEY_CHAR_MINUS : results[2]=2; sprintf(buffer,"-"); break;
				case KEY_CHAR_MULT : results[2]=3; sprintf(buffer,"*"); break;
				case KEY_CHAR_DIV : results[2]=4; sprintf(buffer,"/"); break;
				}
			if(key==KEY_CHAR_PLUS || key==KEY_CHAR_MINUS || key==KEY_CHAR_MULT || key==KEY_CHAR_DIV) break;
			}
		locate(1,row);
		Print(buffer);
		row++;
		turn++;
		}
	else 
		{
		/*  switch(atoi(results[2]))
		{
		case 1 : result=results[0]+results[1]; break;
		case 2 : result=results[0]-results[1]; break;
		case 3 : result=results[0]*results[1]; break;
		case 4 : result=results[0]/results[1]; break;
		}  
		
		sprintf(buffer,"nombre %s",results);
		locate(1,row);
		Print(buffer);
		row++;
		GetKey(&key);
		
		switch(key)
			{
			case KEY_CTRL_EXIT :free(p); return;
			case KEY_CTRL_F1 : turn=0; row=2; Bdisp_AllClr_DDVRAM(); break;
			}
		} */
	}
	
}
