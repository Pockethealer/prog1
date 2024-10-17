#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

int main(int argc, char **argv){
	bool vege; int a,b,c;
	//main menu
	do{
		printf("Mit szeretnel csinalni?\n");
		printf("1. receptet felvenni\n");
		printf("2.receptet keresni\n");
		printf("3. receptet torolni\n");
		printf("4.kilepni\n");
	scanf("%d",&a);
	switch(a){
		case 1:
			printf("ide jonnek majd a receptek");
			break;
		case 2:
			printf("itt lehe majd keresni");
			break;
		case 3:
			printf("itt lesz majd a recept torles");
			break;
		case 4:
			printf("Kilepes");
			vege=true;
			break;
	}}while(!vege);	
	return 0;
}
