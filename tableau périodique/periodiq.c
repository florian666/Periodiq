/*****************************************************************/
/*                                                               */
/*   CASIO fx-9860G SDK Library                                  */
/*                                                               */
/*   File name : [ProjectName].c                                 */
/*                                                               */
/*   Copyright (c) 2006 CASIO COMPUTER CO., LTD.                 */
/*                                                               */
/*****************************************************************/
#include "fxlib.h"
#include "SH4comp.c"
#include "periodiq.h"
#include "MonochromeLib.h"

//#include <stdlib.h>
#include <stdio.h>
#include <math.h>
//#include <ctype.h>
#include <keybios.h>
#include "SPRITE.h"
#include "EasyInput.h"

#define PrintMini(x,y,str,m) PrintMini(x,y,(const unsigned char *)(str),m)

//#include <stdlib.h>
//#include <ctype.h>

int atoi(const char *str)
{
        // Variables declaration.
        int n=0, sign=1;

        // Parsing string until the first glyph.
        while(isspace(*str)) str++;

        // Checking sign.
        if(*str=='-') sign=-1, str++;
        else if(*str=='+') sign=+1, str++;

        // Reading digits.
        while(isdigit(*str))
        {
                n += *str - '0';
                if(*++str) n *= 10;
        }

        // Returning the final value.
        return n*sign;
}

//****************************************************************************
//  AddIn_main (Sample program main function)
//
//  param   :   isAppli   : 1 = This application is launched by MAIN MENU.
//                        : 0 = This application is launched by a strip in eACT application.
//
//              OptionNum : Strip number (0~3)
//                         (This parameter is only used when isAppli parameter is 0.)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************

struct Element elements[] =
{
		{ /*1, */"Hydrogene","H",1.008,"1",1,1,1,2.20,0,2},
		{ /*2, */"Helium","He",4.003,"2",18,1,0,0,1,9},
		{ /*3, */"Lithium","Li",6.940,"2-1",1,2,1,0,0,10},
		{ /*4, */"Beryllium","Be",9.012,"2-2",2,2,2,1.57,0,11},
		{ /*5, */"Bore","B",10.810,"2-3",13,2,2,2.04,1,12},
		{ /*6, */"Carbone","C",12.011,"2-4",14,2,3,2.55,1,13},
		{ /*7, */"Azote","N",14.007,"2-5",15,2,4,3.04,1,14},
		{ /*8, */"Oxygene","O",15.999,"2-6",16,2,5,3.44,1,15},
		{ /*9, */"Fluor","F",18.998,"2-7",17,2,2,3.98,1,16},
		{/*10, */"Neon","Ne",20.178,"2-8",18,2,0,0,1,17},
		{/*11, */"Sodium","Na",22.990,"2-8-1",1,3,1,0.93,2,18},
		{/*12, */"Magnesium","Mg",24.305,"2-8-2",2,3,2,1.31,3,19},
		{/*13, */"Aluminium","Al",26.982,"2-8-3",13,3,3,1.61,4,30},
		{/*14, */"Silicium","Si",28.085,"2-8-4",14,3,4,1.90,5,31},
		{/*15, */"Phosphore","P",30.974,"2-8-5",15,3,5,2.19,6,32},
		{/*16, */"Soufre","S",32.060,"2-8-6",16,3,6,2.58,7,33},
		{/*17, */"Chlore","Cl",35.450,"2-8-7",17,3,7,3.16,8,34},
		{/*18, */"Argon","Ar",39.948,"2-8-8",18,3,2,0,9,35},
		{/*19, */"Potassium","K",39.098,"2-8-8-1",1,4,1,0.82,10,36},
		{/*20, */"Calcium","Ca",40.078,"2-8-8-2",2,4,2,1.0,11,37},
		{/*21, */"Scandium","Sc",44.956,"2-8-9-2",3,4,3,1.36,20,38},
		{/*22, */"Titane","Ti",47.867,"2-8-10-2",4,4,4,1.54,21,39},
		{/*23, */"Vanadium","Va",50.941,"2-8-11-2",5,4,5,1.63,22,40},
		{/*24, */"Chrome","Cr",51.996,"2-8-13-1",6,4,6,1.66,23,41},
		{/*25, */"Manganese","Mn",54.380,"2-8-13-2",7,4,7,1.55,24,42},
		{/*26, */"Fer","Fe",55.845,"2-8-14-2",8,4,6,1.83,25,43},
		{/*27, */"Cobalt","Co",58.933,"2-8-15-2",9,4,5,1.88,26,44},
		{/*28, */"Nickel","Ni",58.693,"2-8-16-2",10,4,4,1.91,27,45},
		{/*29, */"Cuivre","Cu",63.546,"2-8-18-1",11,4,4,1.90,28,46},
		{/*30, */"Zinc","Zn",65.380,"2-8-18-2",12,4,2,1.65,29,47},
		{/*31, */"Gallium","Ga",69.723,"2-8-18-3",13,4,3,1.81,12,48},
		{/*32, */"Germanium","Gr",72.630,"2-8-18-4",14,4,4,2.01,13,49},
		{/*33, */"Arsenic","As",74.921,"2-8-18-5",15,4,5,2.18,14,50},
		{/*34, */"Selenium","Se",78.971,"2-8-18-6",16,4,6,2.55,15,51},
		{/*35, */"Brome","Br",79.904,"2-8-18-7",17,4,7,2.96,16,52},
		{/*36, */"Krypton","Kr",83.798,"2-8-18-8",18,4,2,3.00,17,53},
		{/*37, */"Rubidium","Rb",85.468,"2-8-18-8-1",1,5,1,0.82,18,54},
		{/*38, */"Strontium","Sr",87.620,"2-8-18-8-2",2,5,2,0.95,19,55},
		{/*39, */"Yttrium","Y",88.906,"2-8-18-9-2",3,5,3,1.22,20,56},
		{/*40, */"Zirconium","Zr",91.224,"2-8-18-10-2",4,5,4,1.33,21,71},
		{/*41, */"Niobium","Nb",92.906,"2-8-18-12-1",5,5,5,1.6,22,72},
		{/*42, */"Molybdene","Mo",95.950,"2-8-18-13-1",6,5,6,2.16,23,73},
		{/*43, */"Technetium","Tc",98.000,"2-8-18-13-2",7,5,7,1.9,24,74},
		{/*44, */"Ruthenium","Ru",101.070,"2-8-18-15-1",8,5,8,2.2,25,75},
		{/*45, */"Rhodium","Rh",102.906,"2-8-18-16-1",9,5,6,2.28,26,76},
		{/*46, */"Palladium","Pd",106.420,"2-8-18-18",10,5,4,2.20,27,77},
		{/*47, */"Argent","Ag",107.869,"2-8-18-18-1",11,5,4,1.93,28,78},
		{/*48, */"Cadmium","Cd",112.414,"2-8-18-18-2",12,5,2,1.69,29,79},
		{/*49, */"Indium","In",114.818,"2-8-18-18-3",13,5,3,1.78,30,80},
		{/*50, */"Etain","Sn",118.710,"2-8-18-18-4",14,5,4,1.96,31,81},
		{/*51, */"Antimoine","Sb",121.760,"2-8-18-18-5",15,5,5,2.05,32,82},
		{/*52, */"Tellure","Te",127.600,"2-8-18-18-6",16,5,6,2.55,33,83},
		{/*53, */"Iode","I",126.904,"2-8-18-18-7",17,5,7,2.66,34,84},
		{/*54, */"Xenon","Xe",130.293,"2-8-18-18-8",18,5,8,2.6,35,85},
		{/*55, */"Cesium","Cs",132.905,"2-8-18-18-8-1",1,6,1,0.79,36,86},
		{/*56, */"Baryum","Ba",137.327,"2-8-18-18-8-2",2,6,2,0.89,37,87},
		{/*57, */"Lanthane","La",138.910,"2-8-18-18-9-2",4,6,3,1.10,103,88}, // lanthanides
		{/*58, */"Cerium","Ce",140.116,"2-8-18-19-9-2",5,6,4,1.12,104,89},
		{/*59, */"Praseodyme","Pr",140.907,"2-8-18-21-8-2",6,6,4,1.13,105,90},
		{/*60, */"Neodyme","Nd",144.242,"2-8-18-22-8-2",7,6,3,1.14,106,91},
		{/*61, */"Promethium","Pm",145.000,"2-8-18-23-8-2",8,6,3,0,107,92},
		{/*62, */"Samarium","Sm",150.360,"2-8-18-24-8-2",9,6,3,1.17,108,93},
		{/*63, */"Europium","Eu",151.964,"2-8-18-25-8-2",10,6,3,0,109,94},
		{/*64, */"Gadolinium","Gd",157.250,"2-8-18-25-9-2",11,6,3,1.20,110,95},
		{/*65, */"Terbium","Tb",158.925,"2-8-18-27-8-2",12,6,4,0,111,96},
		{/*66, */"Dysprosium","Dy",162.500,"2-8-18-28-8-2",13,6,3,1.22,112,97},
		{/*67, */"Holmium","Ho",164.930,"2-8-18-29-8-2",14,6,3,1.23,113,98},
		{/*68, */"Erbium","Er",167.259,"2-8-18-30-8-2",15,6,3,1.24,114,99},
		{/*69, */"Thulium","Tm",168.934,"2-8-18-31-8-2",16,6,3,1.25,115,100},
		{/*70, */"Yttrebium","Yb",173.054,"2-8-18-32-8-2",17,6,3,0,116,101},
		{/*71, */"Lutecium","Lu",174.967,"2-8-18-32-9-2",18,6,3,1.27,117,102},//fin des lanthanides
		{/*72, */"Hafnium","Hf",178.490,"2-8-18-32-10-2",4,6,4,1.3,39,103},
		{/*73, */"Tantale","Ta",180.948,"2-8-18-32-11-2",5,6,5,1.5,40,104},
		{/*74, */"Tungstene","W",183.840,"2-8-18-32-12-2",6,6,6,2.36,41,105},
		{/*75, */"Rhenium","Re",186.207,"2-8-18-32-13-2",7,6,7,1.9,42,106},
		{/*76, */"Osmium","Os",190.230,"2-8-18-32-14-2",8,6,8,2.2,43,107},
		{/*77, */"Iridium","Ir",192.217,"2-8-18-32-15-2",9,6,8,2.20,44,108},
		{/*78, */"Platine","Pt",195.084,"2-8-18-32-17-1",10,6,6,2.28,45,109},
		{/*79, */"Or","Au",196.967,"2-8-18-32-18-1",11,6,5,2.54,46,110},
		{/*80, */"Mercure","Hg",200.590,"2-8-18-32-18-2",12,6,4,2.0,47,111},
		{/*81, */"Thallium","Tl",204.380,"2-8-18-32-18-3",13,6,3,1.62,48,112},
		{/*82, */"Plomb","Pb",207.200,"2-8-18-32-18-4",14,6,4,2.33,49,113},
		{/*83, */"Bismuth","Bi",208.980,"2-8-18-32-18-5",15,6,5,2.02,50,114},
		{/*84, */"Polonium","Po",209.000,"2-8-18-32-18-6",16,6,6,2.0,51,115},
		{/*85, */"Astate","At",210.000,"2-8-18-32-18-7",17,6,7,2.2,52,116},
		{/*86, */"Radon","Rn",212.000,"2-8-18-32-18-8",18,6,6,0,53,117},
		{/*87, */"Francium","Fr",223.000,"2-8-18-32-18-8-1",1,7,1,0.7,54,86},
		{/*88, */"Radium","Ra",226.000,"2-8-18-32-18-8-2",2,7,2,0.9,55,87},
		{/*89, */"Actinium","Ac",227.000,"2-8-18-32-18-9-2",4,7,3,1.1,56,88}, // actinide
		{/*90, */"Thorium","Th",232.038,"2-8-18-32-18-10-2",5,7,4,1.3,57,89},
		{/*91, */"Protactinium","Pa",231.036,"2-8-18-32-20-9-2",6,7,5,1.5,58,90},
		{/*92, */"Uranium","U",238.029,"2-8-18-32-21-9-2",7,7,6,1.38,59,91},
		{/*93, */"Neptunium","Np",237.000,"2-8-18-32-22-9-2",8,7,7,1.36,60,92},
		{/*94, */"Plutonium","Pu",244.000,"2-8-18-32-24-8-2",9,7,8,1.28,61,93},
		{/*95, */"Americum","Am",243.000,"2-8-18-32-25-8-2",10,7,6,1.3,62,94},
		{/*96, */"Curium","Cm",247.000,"2-8-18-32-25-9-2",11,7,4,1.3,63,95},
		{/*97, */"Berkelium","Bk",247.000,"2-8-18-32-27-8-2",12,7,4,1.3,64,96},
		{/*98, */"Californium","Cf",251.000,"2-8-18-32-28-8-2",13,7,4,1.3,65,97},
		{/*99, */"Einsteinium","Es",252.000,"2-8-18-32-29-8-2",14,7,3,1.3,66,98},
		{/*100,*/"Fermium","Fm",257.000,"2-8-18-32-30-8-2",15,7,3,1.3,67,99},
		{/*101,*/"Mendelevium","Md",258.000,"2-8-18-32-31-8-2",16,7,3,1.3,68,100},
		{/*102,*/"Nobelium","No",259.000,"2-8-18-32-32-8-2",17,7,3,1.3,69,101},
		{/*103,*/"Lawrencium","Lr",262.000,"2-8-18-32-32-8-3",18,7,3,0,70,102},// fin des actinides
		{/*104,*/"Rutherfordium","Rf",267.000,"2-8-18-32-32-10-2",4,7,4,0,71,56},
		{/*105,*/"Dubnium","Db",268.000,"2-8-18-32-32-11-2",5,7,5,0,72,57},
		{/*106,*/"Seaborg","Sg",271.000,"2-8-18-32-32-12-2",6,7,6,0,73,58},
		{/*107,*/"Bohrium","Bh",272.000,"2-8-18-32-32-13-2",7,7,7,0,74,59},
		{/*108,*/"Hassium","Hs",270.000,"2-8-18-32-32-14-2",8,7,8,0,75,60},
		{/*109,*/"Meitnerium","Mt",276.000,"2-8-18-32-32-15-2",9,7,-1,0,76,61}, // -1 corespond à "inconnu"
		{/*110,*/"Darmstadium","Ds",281.000,"2-8-18-32-32-17-1",10,7,-1,0,77,62},
		{/*111,*/"Roengenium","Rg",280.000,"2-8-18-32-32-18-1",11,7,-1,0,78,63},
		{/*112,*/"Copernicium","Cn",285.000,"2-8-18-32-32-18-2",12,7,-1,0,79,64},
		{/*113,*/"Ununtrium","Uut",284.000,"2-8-18-32-32-18-3",13,7,-1,0,80,65},
		{/*114,*/"Flerovium","Fl",289.000,"2-8-18-32-32-18-4",14,7,-1,0,81,66},
		{/*115,*/"Ununpentium","Uup",288.000,"2-8-18-32-32-18-5",15,7,-1,0,82,67},
		{/*116,*/"Livermorium","Lv",288.000,"2-8-18-32-32-18-6",16,7,-1,0,83,68},
		{/*117,*/"Ununseptium","Uus",294.000,"2-8-18-32-32-18-7",17,7,-1,0,84,69},
		{/*118,*/"Ununoctium","Uun",294.000,"2-8-18-32-32-18-8",18,7,-1,0,85,70}
};

struct Detail ajout[] = {
{1766,0,1},
{1895,2,1},
{1817,4,0},
{1797,5,0},
{1808,3,0},
{-3750,0,0},
{1772,0,1},
{1774,0,1},
{1886,1,1},
{1898,2,1},//10
{1807,4,0},
{1755,5,0},
{1825,9,0},
{1824,3,0},
{1669,0,0},
{-500,0,0},
{1774,1,1},
{1894,2,1},
{1807,4,0},
{1808,5,0},//20
{1879,8,0},
{1791,8,0},
{1801,8,0},
{1797,8,0},
{1774,8,0},
{-2000,8,0},
{1735,8,0},
{1751,8,0},
{-8000,8,0},
{1500,8,0},//30
{1875,9,0},
{1886,3,0},
{1250,3,0},
{1817,0,0},
{1826,1,2},
{1898,2,1},
{1861,4,0},
{1790,5,0},
{1794,8,0},
{1789,8,0},//40
{1801,8,0},
{1781,8,0},
{1937,8,0},
{1844,8,0},
{1803,8,0},
{1803,8,0},
{-3000,8,0},
{1817,8,0},
{1863,9,0},
{-3000,9,0},//50
{-3000,3,0},
{1783,3,0},
{1811,1,0},
{1898,2,1},
{1860,4,0},
{1808,5,0},
{1839,6,0},
{1803,6,0},
{1885,6,0},
{1885,6,0},//60
{1945,6,0},
{1879,6,0},
{1901,6,0},
{1880,6,0},
{1843,6,0},
{1886,6,0},
{1878,6,0},
{1842,6,0},
{1879,6,0},
{1878,6,0},//70
{1907,6,0},
{1923,8,0},
{1802,8,0},
{1783,8,0},
{1925,8,0},
{1803,8,0},
{1803,8,0},
{1735,8,0},
{-2500,8,0},
{-1500,8,2},//80
{1861,9,0},
{-4000,9,0},
{1400,9,0},
{1898,3,0},
{1940,1,0},
{1900,2,1},
{1939,4,0},
{1898,5,0},
{1899,7,0},
{1829,7,0},//90
{1913,7,0},
{1789,7,0},
{1940,7,0},
{1940,7,0},
{1944,7,0},
{1944,7,0},
{1949,7,0},
{1950,7,0},
{1952,7,0},
{1950,7,0},//100
{1955,7,0},
{1958,7,0},
{1961,7,0},
{1964,8,3},
{1967,8,3},
{1974,8,3},
{1981,8,3},
{1984,8,3},
{1982,8,3},
{1994,8,3},//110
{1994,8,3},
{1996,8,3},
{2004,9,3},
{1998,9,3},
{2004,9,3},
{2000,9,3},
{2010,1,3},
{2006,2,3}
};

char *family[25] ={
{"non metaux"},//0
{"halogene"},//1
{"gaz rare"},//2
{"metalloide"},//3
{"metal alcalin"},//4
{"metal alcalino terreux"},//5
{"lanthanide"},//6
{"actinide"},//7
{"metal de transition"},//8
{"post transition metal"}//9
};

char *etat[9]={
	{"solide"},//0
	{"gaz"},//1
	{"liquide"},//2
	{"inconnu"},//3
};

int AddIn_main(int isAppli, unsigned short OptionNum)
{
tableauElement(0);
	return 1;
}


void Mini(char* chaine, int n ) // fonc defini le numero de la fonction
{

    int i;
	short j;

    for(i=56 ; i<64 ; i++)
		Bdisp_DrawLineVRAM(n*21+2, i, n*21+20, i);

	while(chaine[j]) j++;  // on calcul la longeur de la chaine

	if(j<4) i=4;
    else i=3;
    PrintMini(n*21+i, 58, chaine, 18);
	//ML_display_vram();
}

int tableauElement(chang)
{

short decalx=0,decaly=0;
short x,y;
short i;

while(1)
	{
	Bdisp_AllClr_DDVRAM();

	chang=(chang>=118 ? 0 : chang<=-1 ? 117 : chang);

	decalx=-(((12*elements[chang].groupe)-13)*108)/240; // on fait un decalage lorsque l'on bouge
	decaly=(elements[chang].periode==5 ? -7 : elements[chang].periode>5 ? -14 : 0);

	for(i=0;i<118;i++)
			{
			x=elements[i].groupe;
			y=(i>55 && i<71 ? 9 : i>87 && i<103 ? 10 : elements[i].periode);


			PrintMini(12*x+decalx-12,7*y+decaly-6,elements[i].symbol,0);

			PrintMini(12*3-11+decalx,7*6-7+decaly,"1",0);
			PrintMini(12*3-11+decalx,7*7-7+decaly,"2",0);

			PrintMini(12*3-11+decalx,7*9+decaly-5,"1",0);
			PrintMini(12*3-11+decalx,7*10+decaly-5,"2",0);
			}

	if (chang>55 && chang<71)
		{
		ML_rectangle(12*elements[chang].groupe-13+decalx,7*9-7+decaly,12*elements[chang].groupe-1+decalx,7*9+decaly,1,1,2);
		}
	else if (chang>87 && chang<103)
		{
		ML_rectangle(12*elements[chang].groupe-13+decalx,7*10-7+decaly,12*elements[chang].groupe-1+decalx,7*10+decaly,1,1,2);
		}
	else
		{
		ML_rectangle(12*elements[chang].groupe-13+decalx,7*elements[chang].periode-7+decaly,12*elements[chang].groupe+decalx,7*elements[chang].periode+decaly,1,1,2);
		}

	ML_rectangle(0,56,128,64,0,0,0); // on fait un rectangle blanc pour qu'il n'y ait rien

	Mini("mini",0);
	Mini("find",1);
	Mini("mol",2);

	Mini("det",5);

	GetKey(&key);

	switch(key)
		{
		case 27 : chang+=1;  break;
		case 38 : chang-=1; break;
		case 37 : chang=elements[chang].dessous; break;
		case 28 : chang=elements[chang].dessus; break;

		case 79 : chang=tableauEleMini(chang); break;
		case 69 : chang=find(chang); break;
		case 59 : calcul_mole(); break;

		case 29 : case 31 : case 78 : chang=detailsElement(chang); break;

		case 47 : return;
		}
	}
}

int tableauEleMini(chang)
{
char buffer[50];
char y;
char menu=0;
char choix=-1;

while(1)
	{
	Bdisp_AllClr_DDVRAM();

	ML_bmp_or(TABLEAU_MINI,0,0,91,48);
	choix_famille(choix); // on met en place le choix sur les familles
	
	chang=(chang>=118 ? 0 : chang<=-1 ? 117 : chang);

	y=(chang>55 && chang<71 ? 9 : chang>87 && chang<103 ? 10 : elements[chang].periode);

	if (chang>55 && chang<71 || chang>87 && chang<103)
		{
		ML_rectangle(5*elements[chang].groupe-4,5*y-7,5*elements[chang].groupe-1,5*y-4,0,1,2);
		}
		else
		{
		ML_rectangle(5*elements[chang].groupe-4,5*y-4,5*elements[chang].groupe-1,5*y-1,0,1,2);
		}


	PrintXY(110-3*strlen(elements[chang].symbol),13,elements[chang].symbol,0);

	sprintf(buffer,"%d",chang+1); // détail des éléments sur la droite
	PrintMini(110-2*strlen(buffer),5,buffer,0);

	sprintf(buffer,"%.3f",elements[chang].masse_mol);
	PrintMini(110-2*strlen(buffer),23,buffer,0);

	

	if(menu==0)
		{

		Mini("maxi",0);
		Mini("find",1);
		Mini("mol",2);
		
		Mini("fami",4);
		Mini("det",5);

		GetKey(&key);

		switch(key)
			{
			case 79 : case 47 : return chang;
			case 69 : chang=find(chang); break;
			case 59 : calcul_mole(); break;
			
			case 39 : menu=1; break;
			case 29 : chang=detailsElement(chang); break;
			}
		}
	else if (menu==1)
		{
		Mini("n-me",0);
		Mini("halo",1);
		Mini("g-ra",2);
		Mini("m-ti",3);
		Mini("m-al",4);
		Mini(" -->",5);

		GetKey(&key);

		switch(key)
			{
			case 47 :  menu=0; choix=-1; break;

			case 79 : choix=0; break;
			case 69 : choix=1; break;
			case 59 : choix=2; break;
			case 49 : choix=3; break;
			case 39 : choix=4; break;
			case 29 : menu=2; break; // on change dans les 2 menus
			}
		}
	else if (menu==2)
		{
		Mini("m-at",0);
		Mini("lant",1);
		Mini("acta",2);
		Mini("m-tr",3);
		Mini("p-tr",4);
		Mini(" -->",5);

		GetKey(&key);

		switch(key)
			{
			case 47 : menu=0; choix=-1;break;

			case 79 : choix=5; break;
			case 69 : choix=6; break;
			case 59 : choix=7; break;
			case 49 : choix=8; break;
			case 39 : choix=9; break;
			case 29 : menu=1; break; // on change dans les 2 menus

			}
		}

	switch(key) // pour les touches principales à chaque fois
		{
		case 27 : chang+=1;  break;
		case 38 : chang-=1; break;
		case 37 : chang=elements[chang].dessous; break;
		case 28 : chang=elements[chang].dessus; break;

		case 31 : case 78 : chang=detailsElement(chang); break;

		}
	}
}

 void choix_famille(choix)
 {
char i=0,y;

  for(i;i<118;++i)
	{
	if (choix==ajout[i].famille)
		{
		y=(i>55 && i<71 ? 9 : i>87 && i<103 ? 10 : elements[i].periode);
		
		(i>55 && i<71 || i>87 && i<103 ? ML_bmp_or(select,5*elements[i].groupe-4,5*y-7,4,4) : ML_bmp_or(select,5*elements[i].groupe-4,5*y-4,4,4));
		
		ML_bmp_or(select,20,50,4,4);
		PrintMini(30,50,family[choix],0);
		}
	}
}

int detailsElement(a)
{
	const char buffer[50];
	char descente=-9;

while (1)
	{

	Bdisp_AllClr_DDVRAM();

	PrintXY(20,descente+13,elements[a].symbol,0);
	sprintf(buffer,"%s",elements[a].nom);
	PrintMini(40,descente+13,buffer,0);

	sprintf(buffer,"%d",a+1); // détail des éléments
	PrintMini((10-a/25),descente+15,buffer,0);

	sprintf(buffer,"masse molaire %.3f g/mol",elements[a].masse_mol);
	PrintMini(1,descente+23,buffer,0);

	PrintMini(20,descente+40,"propriete  de base :",0); //

	if (elements[a].groupe>=1)
		{
		sprintf(buffer,"groupe : %d ",elements[a].groupe);
		PrintMini(1,descente+50,buffer,0);
		}

	if ((a>55 && a<71) || (a>87 && a<103))
	PrintMini(1,descente+50,"pas de groupe",0);

	sprintf(buffer,"periode : %d ",elements[a].periode);
	PrintMini(1,descente+60,buffer,0);

	sprintf(buffer,"couch electro %s",elements[a].config_electro);
	PrintMini(1,descente+70,buffer,0);

	sprintf(buffer,"famille %s",family[ajout[a].famille]);
	PrintMini(1,descente+80,buffer,0);

	sprintf(buffer,"decouvert en %d",ajout[a].annee);
	PrintMini(1,descente+90,buffer,0);
	
	sprintf(buffer,"etat a 293.15 K : %s",etat[ajout[a].etat]);
	PrintMini(1,descente+100,buffer,0);

	PrintMini(20,descente+120,"reactivite :",0); //

	if (elements[a].electro_neg==0)
		{
		PrintMini(1,descente+130,"electro neg inconnue",0);
		}
	else
		{
		sprintf(buffer,"electro neg : %f ",elements[a].electro_neg);
		PrintMini(1,descente+130,buffer,0);
		}

	if (elements[a].valence>=0)
		{
		sprintf(buffer,"valence : %d ",elements[a].valence);
		PrintMini(1,descente+140,buffer,0);
		}
	else
		{
	PrintMini(1,descente+140,"valence inconnue",0);
		}

	Mini("ret",5);

	GetKey(&key);

	switch (key)
		{
		case 38 : a-=1,descente=-9; break;
		case 27 : a+=1,descente=-9; break;
		case 37 : descente-=4; break;
		case 28 : descente+=4; break;
		case 29 : case 31 : case 47 : return a;
		}

	a=(a<0 ? 117 : a>117 ? 0 : a);
	descente=(descente>-9 ? -9 : descente<-85 ? -85 : descente); // on fixe les limites de la page
	}
}

int find(chang)
{
char *numero=NULL;

char i=0,j;

const char buffer[50];

Bdisp_AllClr_DDVRAM();
PrintXY(10,1,"Vous cherchez :",0);
PrintMini(10,15,"1. numero de l'element",0);
PrintMini(10,25,"2. masse molaire",0);
PrintMini(10,35,"3. Symbole de l'element",0);
PrintMini(10,45,"4. Nom de l'element",0);

while (1)
	{
	
	EI_init();

	EI_manage_config(EI_SET_COLUMN, 1);
	EI_manage_config(EI_SET_ROW, 3);
	EI_manage_config(EI_SET_START_MODE, EI_NORMAL);

	GetKey(&key);

		switch(key)
		{
		case 72 : 
			{
			while(1)
				{
				Bdisp_AllClr_DDVRAM();
				PrintMini(1,1,"Vous cherchez l'element n :",0);

				numero=EI_input_string(3,(const char*)"0123456789");
				// ça coupe ici
				if (atoi(numero)>0 && atoi(numero)<119) // ça arrête le curseur
					{
					return atoi(numero)-1;
					}
				}
			}

		case 62 :
			{
			while(1)
				{
				Bdisp_AllClr_DDVRAM();
				PrintMini(1,1,"Vous cherchez une masse",0);
				PrintMini(1,7,"molaire de :",0);

				numero=EI_input_string(3,(const char*)"0123456789");

				for (i=0;i<118;i++)
					{
					if (atoi(numero)==floor(elements[i].masse_mol+0.5))
						{
						return i;
						}
					}
				}
			}

		case 52 :
			{
			while(1)
				{
				Bdisp_AllClr_DDVRAM();
				PrintMini(1,1,"Vous cherchez le symbole ?",0);

				EI_manage_config(EI_SET_START_MODE, EI_ALPHA_LOCKED);

				numero=EI_input_string(3,(const char*)"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
				numero[0]=toupper (numero[0]); // on met le 1er caractère en majuscule
				for (i=0;i<118;i++)
					{
					for (j = 1 ; numero[j] != '\0' ; j++)
						{
						numero[j] = tolower(numero[j]); // on met certains caractères en minuscule pour la recherche
						}

					if (!strcmp(numero,elements[i].symbol))
						{
						return i;
						}
					}
				}
			}

		case 73 :
			{
			while(1)
				{
				Bdisp_AllClr_DDVRAM();
				PrintMini(1,1,"Vous cherchez le nom ?",0);

				EI_manage_config(EI_SET_START_MODE, EI_ALPHA_LOCKED);

				numero=EI_input_string(13,(const char*)"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
				numero[0]=toupper(numero[0]); // on met le 1er caractère en majuscule
			for (i=0;i<118;i++)
					{
					for (j = 1 ; numero[j] != '\0' ; j++)
						{
						numero[j] = tolower(numero[j]);// on met certains caractères en minuscule pour la recherche
						}

					if (!strcmp(numero,elements[i].nom))
						{
						return i;
						}
					}
				}
			}

		case 47 : return chang;

		}
	}
}

void calcul_mole()
{
char *str = NULL, *p=str;
char characts[20]={'\0'};
char i=0;
float result=0, masse;
const char buffer[50]={0};
char cap;

while(1)
{
Bdisp_AllClr_DDVRAM();

PrintMini(1,1,"Entrez votre formule : ",0);

Mini("A  a",0);

EI_init();

EI_manage_config(EI_SET_COLUMN, 1);
EI_manage_config(EI_SET_ROW, 2);
EI_manage_config(EI_SET_START_MODE, EI_NORMAL);

str=EI_input_string(25,(const char*)"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

Bdisp_AllClr_DDVRAM();

sprintf(buffer,"%s",str);
PrintXY(64-3*strlen(str),10,buffer,36);

while(*str) // on va jusqu'a la fin de la chaine
	{
	i=0;

	while(isalpha(*str)) // on prends seulement les lettres
			{
			characts[i]=tolower(*str); // on copie la lettre en minuscule directement dans characts 
			++i;
			++str;
			}

	characts[0]=toupper(characts[0]); // on met le 1er caractère en majuscule

	for(i=0;i<118;i++) // on se déplace dans les éléments de la structure
		{
		if(!strcmp(characts,elements[i].symbol))
			{
			masse=elements[i].masse_mol; // on a la masse molaire
			break;
			}
		}
		
		for(i=0;i<20;++i) // on remet tout à zéro : évite les erreurs
			characts[i]='\0';

	i=0;

	while(isdigit(*str)) // on prends seulement les chiffres
		{
		characts[i]=*str; // on copie la lettre dans characts
		++i;
		++str;
		}

		result += atoi(characts)*masse;
		
		for(i=0;i<4;++i) // on remet tout à zéro : évite les erreurs
			characts[i]='\0';
	}

free(p);

PrintMini(1,30,"la masse molaire est de",0);

sprintf(buffer,"%.3f g/mol",result);
PrintMini(1,40,buffer,0);

Mini("calc",0);
Mini("ret",5);

GetKey(&key);

switch(key)
	{
	case 29 : return;
	}
}
}

//****************************************************************************
//**************                                              ****************
//**************                 Notice!                      ****************
//**************                                              ****************
//**************  Please do not change the following source.  ****************
//**************                                              ****************
//****************************************************************************


#pragma section _BR_Size
unsigned long BR_Size;
#pragma section


#pragma section _TOP

//****************************************************************************
//  InitializeSystem
//
//  param   :   isAppli   : 1 = Application / 0 = eActivity
//              OptionNum : Option Number (only eActivity)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************
int InitializeSystem(int isAppli, unsigned short OptionNum)
{
    return INIT_ADDIN_APPLICATION(isAppli, OptionNum);
}

#pragma section

