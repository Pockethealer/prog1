#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

typedef struct Osszetevo
{
	char nev[50];
	int sorszam, ar;
	char tipus[10];
} Osszetevo;

void menu_kiir(void);
int recept_beolvas(Osszetevo *osszetevok);

int main(int argc, char **argv)
{
	bool vege;
	int a;
	Osszetevo osszetevok[20];
	recept_beolvas(osszetevok);
	printf("%s, %s", osszetevok[0].nev, osszetevok[1].nev);
	// main menu
	do
	{
		menu_kiir();
		scanf("%d", &a);
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
int recept_beolvas(Osszetevo *osszetevok)
{
	FILE *file = fopen("osszetevok.txt", "r");
	if (file == NULL)
	{
		perror("Nem sikerült megnyitni az összetevők listáját");
		return 1;
	}
	Osszetevo *p_osszetevo = osszetevok;
	while (fscanf(file, "%s;%d", p_osszetevo->nev, &(p_osszetevo->sorszam)) == 2)
	{
		p_osszetevo++;
	}

	fclose(file);
	return 0;
}
