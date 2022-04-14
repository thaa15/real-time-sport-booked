#include "Header.h"

int main(void){
	int y;
	SetConsoleTitle("Sport Centre");
	system("color F0");
	srand(time(NULL));
	readFile();
	
	mainMenu(&y);
	
	gotoxy(40,y+7);printf("PROGRAM BY THARIQ AND RAYHAN RIZKY MANDA");
	return 0;
}