#ifndef _PERIODIQ_H
    #define _PERIODIQ_H
	
	
	unsigned int key;

	struct Element 
	{
        unsigned char nom[14]; // le nom
        unsigned char symbol[4]; // le symbole
		float masse_mol; // la masse molaire // que l'on divise par 1000
		unsigned char config_electro [18]; // la config électronique
		unsigned char groupe; //le groupe //x
		unsigned char periode; // la période // y
		unsigned char valence; // le nombre de valence
		float electro_neg; // electro negativité
		unsigned char dessus; // element au dessus de celui actuel
		unsigned char dessous; // element en dessous de celui actuel
};

//1 : 1
//11 : 3
//111 : 7
//1111 : 15 
//11111 : 31 
//111111 : 63 
//1111111 : 127
//11111111 : 255

struct Detail
{
	short annee ;
	unsigned int famille : 4;
	unsigned int etat : 4;
};

int detailsElement(int); //chang //a
int tableauElement(int); //chang
int tableauEleMini(int); //chang
int find(int);	// int : pour le return
void choix_famille(int);
void Mini(char* c, int n);
void calcul_mole(void);

#endif