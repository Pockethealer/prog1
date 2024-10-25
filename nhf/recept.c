#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

typedef struct Osszetevo
{
	char nev[50];
	int sorszam;
	char tipus[10];
	int ar;
} Osszetevo;

// fuggvenyek deklaralasa
FILE* file_megnyit(char* mit, char* hogyan);
void menu_kiir(void);
int osszetevo_beolvas(Osszetevo* osszetevok);
void osszetevo_kiir(Osszetevo* osszetevok, int mit, int hanyadik);
int osszetevo_fileba_ir(Osszetevo osszetevo, Osszetevo* osszetevok);

int main(int argc, char** argv)
{
	bool vege;
	int a = 0;
	Osszetevo osszetevok[200];
	// osszetevok file megnyitasa, beolvasasa az oasszetevok tombjebe, es bezarasa
	int osszetevo_db = osszetevo_beolvas(osszetevok);
	// osszetevo kiirasa
	Osszetevo uj = { "Erős pista", osszetevo_db + 1, "g", 700 };
	osszetevo_fileba_ir(uj, osszetevok);
	osszetevo_kiir(osszetevok, 1, 100);

	// main menu
	do
	{
		menu_kiir();
		if (scanf("%d", &a) == 0)
			break;
		switch (a)
		{
		case 1:
			printf("ide jonnek majd a receptek\n");
			break;
		case 2:
			printf("itt lehe majd keresni\n");
			break;
		case 3:
			printf("itt lesz majd a recept torles\n");
			break;
		case 4:
			printf("Kilepes\n");
			vege = true;
			break;
		default:
			printf("Ervenytelen parnacs");
			break;
		}
	} while (!vege);
	return 0;
}

void menu_kiir(void)
{
	printf("Mit szeretnel csinalni?\n");
	printf("1. receptet felvenni\n");
	printf("2.receptet keresni\n");
	printf("3. receptet torolni\n");
	printf("4.kilepni\n");
	return;
}
int osszetevo_beolvas(Osszetevo* osszetevok)
{ /*beolvassa az osszetevok.txt filebol az elemeket,
es eltarolja oket Osszetevok strukturaban, majd visszaadj hany elemet olvasott be*/
	FILE* osszetevo_file = file_megnyit("osszetevok.txt", "r");
	if (osszetevo_file != NULL)
	{
		Osszetevo* p_osszetevo = osszetevok;
		int osszetevo_db = 0;
		while (fscanf(osszetevo_file, " %49[^;];%d;%9[^;];%d",
			p_osszetevo->nev,
			&(p_osszetevo->sorszam),
			p_osszetevo->tipus,
			&(p_osszetevo->ar)) == 4)
		{
			p_osszetevo++;
			osszetevo_db++;
		}
		fclose(osszetevo_file);
		return osszetevo_db;
	}
	else
		return -1;
}
void osszetevo_kiir(Osszetevo* osszetevok, int mit, int hanyadik)
{ // kiirja az adott struktura adott elemet
	switch (mit)
	{
	case 1:
		printf("%s", osszetevok[hanyadik].nev);
		break;
	case 2:
		printf("%d", osszetevok[hanyadik].sorszam);
		break;
	case 3:
		printf("%s", osszetevok[hanyadik].tipus);
		break;
	case 4:
		printf("%d", osszetevok[hanyadik].ar);
		break;
	default:
		break;
	}
	return;
}
int osszetevo_fileba_ir(Osszetevo osszetevo, Osszetevo* osszetevok)
{
	FILE* file = file_megnyit("osszetevok.txt", "a");
	if (file != NULL)
	{
		fprintf(file, " \n%s;%d;%s;%d", osszetevo.nev,
			osszetevo.sorszam, osszetevo.tipus, osszetevo.ar);
		fclose(file);
		osszetevo_beolvas(osszetevok);
		return 0;
	}
	return -1;
}

FILE* file_megnyit(char* mit, char* hogyan)
{
	FILE* file = fopen(mit, hogyan);
	if (file == NULL)
	{
		printf("Nem sikerült megnyitni a %s file-t", mit);
		return NULL;
	}
	return file;
}
