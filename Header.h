#ifndef HEADER_H
	#define HEADER_H
	#include <stdio.h>
	#include <stdlib.h>
	#include <windows.h>
	#include <time.h>
	#include <conio.h>
	#include <string.h>
	#include <math.h>
	#include <dos.h>
	
	void dashboard(char id[10]);
	void rentPlaceandStuffMenu();
	void memberValidation();
	void rentPlace(char id[10]);
	void parsePlace(char*name,char*availability,char*fasility,int price);
	void parseDrink(int price,char minuman[20]);
	void parseMember(char nama[30],char id[10],char ttl[10],char time[20]);
	void placeDisplay(char type[15], char id[10]);
	const char *checkAvailable(char *name, char *availability);
	void batalSewa(char id[10]);
	
	struct member{
		char nama[30];
		char id[10];
		char ttl[10];
		char time[24];
		struct member *next;
	};
	
	struct renthistory{
		char jamMasuk[25];
		char namaTempat[50];
		char jamKeluar[25];
		char id[10];
		struct renthistory *next;
	};
	
	struct place{
		char name[50];
		char availability[50];
		char fasility[65];
		int price;
		struct place *next;
	};
	
	struct drink{
		char minuman[20];
		int price;
		struct drink *next;
	};
	void buyDrink(struct drink *temp);
	
	int hargaTotal = 0;
	int count = 0;
	char items[100][100];
	int priceItems[100];
	int mounts[100];
	time_t time_choosen1 = 0;
	time_t time_choosen2 = 0;
	
	COORD setCoord={};
	struct place *head = NULL;
	struct drink *heads = NULL;
	struct member *first = NULL;
	struct renthistory *top = NULL;
	
	//FUNGSI UNTUK MENENTUKAN CURSOR PRINT ATAU APAPUN
	void gotoxy(int x , int y){
	    setCoord.X=x;
	    setCoord.Y=y;
	    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), setCoord);
	}
	
	//FUNGSI UNTUK MENGUBAH WARNA TEKS DAN BACKGROUNDNYA
	void textcolor(int color, int BackC){
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color + (BackC<<4));
	}
	
	//FUNGSI MEMBENTUK GARIS SECARA GRAFIS
	void Garis(int n){
		int i;
		for(i=0;i<n;i++){
			printf("-");
		}
	}
	
	//FUNGSI UNTUK MEMBACA 4 FILE DATA PADA PROGRAM INI
	void readFile(){
		char tempat[50],availability[50],fasility[65],minum[20];
		int harga,i,j;
		char buffer[100],nama[30],id[10],ttl[10];
		FILE *fp = fopen("tempat.txt", "r");
		FILE *fp2 = fopen("minum.txt", "r");
		FILE *fp3 = fopen("member.txt", "r");
		FILE *fp4 = fopen("riwayat.txt","r");
		if(fp == NULL)
		    printf("Can't open file\n");
		else {
		    j = 0;
		    while(fgets(buffer,100,fp) != NULL){
		        i = 0;
		        char delimiter[2] = ",";
				char *token = strtok(buffer,delimiter);
				while(token != NULL){
					if(i==0) strcpy(tempat,token);
					else if(i==1) harga = atoi(token);
					else if(i==2) strcpy(availability,"9999999");
					else if(i == 3) strcpy(fasility,token);
					token = strtok(NULL,delimiter);
					i++;
				}
				parsePlace(tempat,availability,fasility,harga);
				j++;
			}
		    fclose(fp);
		}
		
		if(fp2 == NULL)
		    printf("Can't open file\n");
		else {
		    j = 0;
		    while(fgets(buffer,100,fp2) != NULL){
		        i = 0;
		        char delimiter[2] = ",";
				char *token = strtok(buffer,delimiter);
				while(token != NULL){
					if(i==0) strcpy(minum,token);
					else if(i==1) harga = atoi(token);
					token = strtok(NULL,delimiter);
					i++;
				}
				parseDrink(harga,minum);
				j++;
			}
		    fclose(fp2);
		}
		
		if(fp3 == NULL)
		    printf("Can't open file\n");
		else {
		    j = 0;
		    char time[20];
		    while(fgets(buffer,100,fp3) != NULL){
		        i = 0;
		        char delimiter[2] = ",";
				char *token = strtok(buffer,delimiter);
				struct member *t,*temp;
				t = (struct member*)malloc(sizeof(struct member));
				while(token != NULL){
					if(i==0) strcpy(t->nama,token);
					else if(i==1) strcpy(t->ttl,token);
					else if(i==2) strcpy(t->id,token);
					else if(i==3) strcpy(t->time,token);
					token = strtok(NULL,delimiter);
					i++;
				}
				if (first == NULL) {
					first = t;
					first->next = NULL;
				}else{
					temp = first;
					while (temp->next != NULL)temp = temp->next;
					temp->next = t;
					t->next = NULL;
				}
				j++;
			}
		    fclose(fp3);
		}
		
		if(fp4 == NULL)
		    printf("Can't open file\n");
		else {
		    j = 0;
		    char time[20];
		    char take[100];
		    while(fgets(take,100,fp4) != NULL){
		        i = 0;
		        char delimiter[2] = ",";
				char *token = strtok(take,delimiter);
				struct renthistory *t,*tempHist;
				t = (struct renthistory*)malloc(sizeof(struct renthistory));
				while(token != NULL){
					if(i==0) strcpy(t->jamMasuk,token);
					else if(i==1) strcpy(t->jamKeluar,token);
					else if(i==2) strcpy(t->namaTempat,token);
					else if(i==3) strcpy(t->id,token);
					token = strtok(NULL,delimiter);
					i++;
				}
				if (top == NULL) {
					top = t;
					top->next = NULL;
				}else{
					tempHist = top;
					while (tempHist->next != NULL)
						tempHist = tempHist->next;
					tempHist->next = t;
					t->next = NULL;
				}
				j++;
			}
		    fclose(fp4);
		}
	}
	
	//FUNGSI UNTUK MEMASUKKAN DATA DINAMIS DENGAN STRUCT PLACE
	void parsePlace(char*name,char*availability,char*fasility,int price){
		struct place *t, *temp;
		t = (struct place*)malloc(sizeof(struct place));
		strcpy(t->availability,availability);
		strcpy(t->name,name);
		strcpy(t->fasility,fasility);
		t->price = price;
		if (head == NULL) {
			head = t;
			head->next = NULL;
			return;
		}
		temp = head;
		while (temp->next != NULL)
	    	temp = temp->next;
		temp->next = t;
		t->next = NULL;
	}
	
	//FUNGSI UNTUK MEMASUKKAN DATA DINAMIS DENGAN STRUCT DRINK
	void parseDrink(int price,char minuman[20]){
		struct drink *t, *temp;
		t = (struct drink*)malloc(sizeof(struct drink));
		strcpy(t->minuman,minuman);
		t->price = price;
		if (heads == NULL) {
			heads = t;
			heads->next = NULL;
			return;
		}
		temp = heads;
		while (temp->next != NULL)
	    	temp = temp->next;
		temp->next = t;
		t->next = NULL;
	}
	
	//FUNGSI UNTUK MEMBUAT LOGO SPORT CENTER SECARA GRAFIS
	void displayLogo(int *pos){
		textcolor(15,0);
		gotoxy(30,*pos);(*pos)++;printf("  #######    ########      ######     ########   ########### ");
		gotoxy(30,*pos);(*pos)++;printf("#####        ##    ###    ##    ##    ##    ###  ########### ");
		gotoxy(30,*pos);(*pos)++;printf(" ####        ##    ###    ##    ##    ##    ###     #####    ");
		gotoxy(30,*pos);(*pos)++;printf("  #####      ########     ##    ##    ########      #####    ");
		gotoxy(30,*pos);(*pos)++;printf("    ####     ##           ##    ##    ##    ###     #####    ");
		gotoxy(30,*pos);(*pos)++;printf("######       ##            ######     ##    ###     #####    ");
		textcolor(0,15);
	}
	
	//FUNGSI UNTUK MEMBENTUK KOTAK INPUT SECARA GRAFIS
	void kontakInput(int xs,int ys, int length){
		int x= xs;
	    int y= ys;
	    
	    gotoxy(x,y);
	    int i,j;
		for ( i= 0 ; i < length; i++){
	    	printf("-");
		}
		printf("\n");
		y++;
		gotoxy(x,y);
		printf("|");
		x = xs + length - 1;
		gotoxy(x,y);
		printf("|");
		y++;
		x = xs;
		gotoxy(x,y);
		for ( i= 0 ; i < length ; i++){
	    	printf("-");
		}
	}
	
	//FUNGSI UNTUK MENCARI ID MEMBER APABILA TIDAK ADA AKAN RETURN 0
	int searchId(char id[10]){
		int flag = 0,i = 1;
		struct member *temp;
		temp = first;
		while(temp != NULL){
			if(strcmp(temp->id, id) == 0){
				flag = 1;
				return i;
			}
			temp = temp->next;
			i++;
		}
		return flag;
	}
	
	//FUNGSI UNTUK DAFTAR MEMBER PADA SPORT CENTER
	void memberRegister(){
		int i,y = 1, x = 33,count_dashed = 0,switch_fill = 0;
		FILE * fptr;
		fptr = fopen("member.txt", "a");
		struct member *iterator,*temps = first;
		struct tm tm = *localtime(&(time_t){time(NULL)});
		iterator = (struct member*)malloc(sizeof(struct member));
		int tanggal,bulan,tahun,kpress;
		int arr[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		float tb,bb;
		char tanggal_temp[50] = {0}, bulan_temp[50] = {0}, tahun_temp[50] = {0}, tahun_temp2[50] = {0}, temp[50]={0};
		char nama[30], ttl[11], alamat[50], id[10];
		char id_rand[36] = {'1','2','3','4','5','6','7','8','9','0',
						'A','B','C','D','E','F','G','H','I','J',
						'K','L','M','N','O','P','Q','R','S','T',
						'U','V','W','X','Y','Z'};
	
		gotoxy(x+15,y);printf("==== DAFTAR MEMBER ====");
		gotoxy(x,y+3);printf("Nama\n");kontakInput(x,y+4,50);
		gotoxy(x,y+7);printf("TTL (DD-MM-YYYY)\n");kontakInput(x,y+8,50);
		gotoxy(x,y+11);printf("Alamat\n");kontakInput(x,y+12,50);
		gotoxy(x-7,y+2);textcolor(0,14);
		printf("ESC untuk kembali ke menu awal atau tekan apapun untuk melanjutkan");textcolor(0,15);
		kpress = getch();
		
		if(kpress != 27){
			gotoxy(x-7,y+2);
			printf("                                                                  ");
			gotoxy(x+1,y+5);scanf(" %[^\n]s", iterator->nama);
			do {
				count_dashed = 0;
				switch_fill = 0;
				gotoxy(x+1,y+9);scanf(" %[^\n]s", ttl);
				strcpy(iterator->ttl,ttl);
				gotoxy(x+10,y+2);printf("                                     ");
				for(i = 0; ttl[i] != '\0';i++){
					if(ttl[i] == '-'){
						count_dashed++;
						switch_fill++;
						continue;
					}
					if(switch_fill == 0) strcat(tanggal_temp, &ttl[i]);
					else if(switch_fill == 1) strcat(bulan_temp, &ttl[i]);
					else if(switch_fill == 2) strcat(tahun_temp2, &ttl[i]);
				}
				for(i = 0; i < 4;i++){
					tahun_temp[i] = tahun_temp2[i];
				}
				tanggal = atoi(tanggal_temp);
				bulan = atoi(bulan_temp);
				tahun = atoi(tahun_temp);
				if(tahun%4 == 0) arr[1] = 29;
				gotoxy(x+10,y+2);
				textcolor(15,4);
				if(strlen(ttl) != 10 || count_dashed != 2){
					printf("Masukkan TTL dengan benar            ");
				}else if(tanggal > arr[bulan-1] || tanggal < 1){
					printf("Masukkan tanggal 1-%d, input ulang!  ",arr[bulan-1]);
				}else if(bulan > 12 || bulan < 1){
					printf("Bulan masehi hanya 1-12, input ulang!");
				}
				textcolor(0,15);
				strcpy(tanggal_temp,temp);
				strcpy(bulan_temp,temp);
				strcpy(tahun_temp,temp);
				strcpy(tahun_temp2,temp);
			} while(strlen(ttl) != 10 || count_dashed != 2 || tanggal > arr[bulan-1] || tanggal < 1 || bulan > 12 || bulan < 1);
			gotoxy(x+1,y+13);scanf(" %[^\n]s", alamat);
			int results;
			do{
				for(i = 0;i < 11;i++){
					int RandIndex = rand() % 37;
					id[i] = id_rand[RandIndex];
				}
				id[strlen(id)-1] = '\0';
				results = searchId(id);
			}while(results != 0);
			
			gotoxy(x,y+16);printf("ID kamu adalah %s",id);
			strcpy(iterator->id,id);
			iterator->id[10] = '\0';
			tm.tm_mday += 30;
			mktime(&tm);
			strftime(iterator->time,24,"%d-%m-%Y %H:%M", &tm);
			iterator->time[strlen(iterator->time)] = '\0';
			fprintf(fptr, "%s,%s,%s,%s\n", iterator->nama,ttl,iterator->id,iterator->time);
			fclose(fptr);
			
			if (first == NULL) {
				first = iterator;
				first->next = NULL;
			}else{
				while (temps->next != NULL)
			    	temps = temps->next;
				temps->next = iterator;
				iterator->next = NULL;
			}
			gotoxy(x,y+17);system("pause");
		}
	}
	
	//FUNGSI MENDISPLAY MASUK PENYEWAAN DENGAN MEMBER ATAU NON MEMBER
	void rentPlaceandStuffMenu(){
		int y, flag = 1;
		char tried;
		while(flag){
			y = 1;
			system("cls");
			displayLogo(&y);
			y+=5;gotoxy(44,y);printf("[1] Member");
			y+=2;gotoxy(44,y);printf("[2] Non Member");
			y+=2;gotoxy(44,y);printf("[0] Ke Menu Awal");
			y+=2;gotoxy(44,y);printf("Pilihan => ");scanf(" %c", &tried);
			
			switch(tried){
				case 48:
					flag = 0;
					break;
				case 49:
					flag = 1;
					system("cls");
					memberValidation();
					break;
				case 50:
					flag = 1;
					system("cls");
					dashboard("0");
					break;
				default:
					textcolor(15,4);
					gotoxy(40,y+3);printf("PILIHAN TIDAK DIKENALI COBA KETIK ULANG");textcolor(0,15);
					getch();
					break;
			}
		}
	}
	
	//FUNGSI UNTUK MEMPERPANJANG MASA MEMBER
	void perpanjangMember(char type[20]){
		int i,y = 1, x = 33,result;
		int kpress;
		struct tm tm = *localtime(&(time_t){time(NULL)});
		char id[10];
		FILE *member;
    	FILE *tempfile;
		displayLogo(&y);y++;
		gotoxy(x+15,y);
		if(!strcmp(type,"Lanjut")) printf("==== PERPANJANG MEMBER ====");
		else printf("==== BERHENTI LANGGANAN ====");
		gotoxy(x,y+7);printf("No. Id\n");kontakInput(x,y+8,50);
		gotoxy(x-7,y+2);textcolor(0,14);
		printf("ESC untuk kembali ke menu awal atau tekan apapun untuk melanjutkan");textcolor(0,15);
		kpress = getch();
		
		if(kpress != 27){
			gotoxy(x-7,y+2);
			printf("                                                                  ");
			gotoxy(x+1,y+9);scanf(" %[^\n]s", id);
			result = searchId(id);
			if(result != 0){
				tm.tm_mday += 30;
				mktime(&tm);
				
				if(strcmp(type,"Lanjut") == 0){
					member = fopen("member.txt", "r");
					tempfile = fopen("tempfile.txt", "w");
					char buffer[100];
					int j = 0,tempFlag = 0;
					char time[24];
					strftime(time,24,"%d-%m-%Y %H:%M", &tm);
					while(fgets(buffer,100,member) != NULL){
				        i = 0;
				        char delimiter[2] = ",";
						char *token = strtok(buffer,delimiter);
						while(token != NULL){
							if(i==0)fprintf(tempfile, "%s,",token);
							else if(i==1)fprintf(tempfile, "%s,",token);
							else if(i==2){
								fprintf(tempfile, "%s,",token);
								if(strcmp(token,id) == 0) tempFlag = 1;
								else tempFlag = 0;
							}
							else if(i==3){
								if(tempFlag == 1) fprintf(tempfile, "%s\n",time);
								else fprintf(tempfile, "%s",token);
							}
							token = strtok(NULL,delimiter);
							i++;
						}
						j++;
					}
				    fclose(member);fclose(tempfile);
				    member = fopen("member.txt","w");
					tempfile = fopen("tempfile.txt","r");
					while(fgets(buffer,100,tempfile) != NULL){
						fprintf(member, "%s",buffer);
					}
					fclose(member);fclose(tempfile);
					gotoxy(x-3,y+17);
					printf("Akunmu telah diperpanjang hingga: %s",time);
				}else {
					struct member *temps = first, *prev;
				    if (temps != NULL && strcmp(temps->id,id) == 0) {
				        first = temps->next; // Changed head
				        free(temps); // free old head
				    }else{
				    	while (temps != NULL && strcmp(temps->id,id) != 0) {
					        prev = temps;
					        temps = temps->next;
					    }
					    if (temps == NULL)return;
					    prev->next = temps->next;
					    free(temps);
					}
			
					member = fopen("member.txt", "r");
					tempfile = fopen("tempfile.txt", "w");
					char buffer[100];
					int j = 0;
					while(fgets(buffer,100,member) != NULL){
				        i = 0;
				        char delimiter[2] = ",";
						char *token = strtok(buffer,delimiter);
						if(j != result-1){
							while(token != NULL){
								if(i==0)fprintf(tempfile, "%s,",token);
								else if(i==1)fprintf(tempfile, "%s,",token);
								else if(i==2) fprintf(tempfile, "%s,",token);
								else if(i==3)fprintf(tempfile, "%s",token);
								token = strtok(NULL,delimiter);
								i++;
							}
						}
						j++;
					}
				    fclose(member);fclose(tempfile);
				    member = fopen("member.txt","w");
					tempfile = fopen("tempfile.txt","r");
					while(fgets(buffer,100,tempfile) != NULL){
						fprintf(member, "%s",buffer);
					}
					fclose(member);fclose(tempfile);
					gotoxy(x+6,y+17);
					printf("Akun membermu telah berhenti layanan!");
				}
				gotoxy(x+7,y+18);system("pause");
			}else{
				gotoxy(x-7,y+2);textcolor(0,14);
				printf("Tidak ditemukan, tekan apapun untuk melanjutkan");textcolor(0,15);
				getch();	
			}
		}
	}
	
	//FUNGSI UNTUK MENENTUKAN APAKAH BENAR TERDAPAT ID MEMBER YANG DIINPUTKAN
	void memberValidation(){
		int i,result,y = 1, x = 33, flag = 0,kpress = 0,j;
		char name[30];
		char id[10];
		
		gotoxy(x+15,y);
		printf("==== MASUK AKUN MEMBER ====");
		gotoxy(x,y+7);printf("No. Id\n");kontakInput(x,y+8,50);
		gotoxy(x-7,y+2);textcolor(0,14);
		printf("ESC untuk kembali ke menu awal atau tekan apapun untuk melanjutkan");textcolor(0,15);
		kpress = getch();
		
		while(kpress != 27){
			gotoxy(x+15,y);
			printf("==== MASUK AKUN MEMBER ====");
			gotoxy(x,y+7);printf("No. Id\n");kontakInput(x,y+8,50);
			gotoxy(x-7,y+2);
			printf("                                                                      ");
			gotoxy(x+1,y+9);scanf(" %s", id);
			result = searchId(id);
			if(result != 0){
				flag = 1;
				break;
			}else{
				gotoxy(x-7,y+2);textcolor(0,14);
				flag = 0;
				printf("Tidak ditemukan, ESC untuk kembali atau tekan apapun untuk melanjutkan");textcolor(0,15);
				kpress = getch();	
			}
			system("cls");
		}
		system("cls");
		if(flag){
			id[10] = '\0';
			dashboard(id);
		}
	}
	
	//FUNGSI MENDISPLAY MENU MENYEWA TEMPAT, BELI MINUMAN, ATAU BERHENTI SEWA
	void dashboard(char id[10]){
		int i,y = 1, x = 33,flag = 1;
		hargaTotal = 0;
		char tried;
		while(flag){
			y = 1;
			if(strlen(id) == 10){
				gotoxy(4,y);printf("%s", id);
			}
			gotoxy(x+20,y);printf("==== MENU ====");
			y+=5;gotoxy(44,y);printf("[1] Sewa Tempat");
			y+=2;gotoxy(44,y);printf("[2] Beli Minum");
			y+=2;gotoxy(44,y);printf("[3] Batal Sewa Tempat");
			y+=2;gotoxy(44,y);printf("[0] Checkout");
			y+=2;gotoxy(44,y);printf("Pilihan => ");scanf(" %c", &tried);
			switch(tried){
				case 48:
					flag = 0;
					system("cls");
					if(hargaTotal != 0){
						int a = 0,b = 1;
						gotoxy(53,b);printf("==== STRUK ====");b+=3;
						gotoxy(43,b);Garis(49);b++;
						gotoxy(43,b);printf("|%2s|%30s|%6s|%6s|","No","Item","Harga","Banyak");b++;
						gotoxy(43,b);Garis(49);b++;
						for(a = 0;a < count;a++){
							gotoxy(43,b);printf("|%2d|%30s|%6d|%6d|",a+1,items[a],priceItems[a],mounts[a]);b++;
						}
						gotoxy(43,b);Garis(49);b++;
						gotoxy(43,b);
						if(strlen(id)>1){
							hargaTotal = hargaTotal*0.45;
							printf("|Total Harga dengan diskon 45%% %17d|",hargaTotal);
						}else{
							printf("|Total Harga %35d|",hargaTotal);
						}
						b++;
						gotoxy(43,b);Garis(49);b++;
						hargaTotal = 0;
						count = 0;
						memset(items, 0, sizeof(items[0][0]) *100*100);
						memset(priceItems, 0, sizeof(priceItems));
						gotoxy(43,b);
						printf("Jangan hilangkan struk ini hingga waktu sewamu habis!");
						b++;
						getch();
					}
					break;
				case 49:
					flag = 1;
					system("cls");
					rentPlace(id);
					break;
				case 50:
					flag = 1;
					system("cls");
					buyDrink(heads);
					break;
				case 51:
					flag = 1;
					system("cls");
					batalSewa(id);
					break;
				default:
					textcolor(15,4);
					gotoxy(x+7,y+3);printf("PILIHAN TIDAK DIKENALI COBA KETIK ULANG");textcolor(0,15);
					getch();
					break;
			}
		}
	};
	
	//FUNGSI TUKAR UNTUK MEMBANTU DALAM SORTING
	void swapPlace(struct place *a, struct place *b){
		char name[50];
		char availability[50];
		char fasility[65];
		int price;
		strcpy(name,a->name);
		strcpy(a->name,b->name);
		strcpy(b->name,name);
		strcpy(availability,a->availability);
		strcpy(a->availability,b->availability);
		strcpy(b->availability,availability);
		strcpy(fasility,a->fasility);
		strcpy(a->fasility,b->fasility);
		strcpy(b->fasility,fasility);
		price = a->price;
		a->price = b->price;
		b->price = price;
	}
	
	//FUNGSI SORTING UNTUK SEWA TEMPAT
	void bubbleSortPlace(struct place *start, char type[15]){
	    int swapped, i;
	    struct place *ptr1;
	    struct place *lptr = NULL;
	  
	    if (start == NULL)
	        return;
	    do{
	        swapped = 0;
	        ptr1 = start;
	        while (ptr1->next != lptr){
	        	const char *res = checkAvailable(ptr1->name, ptr1->fasility);
	        	double f1 = strtod(res,NULL);
	        	const char *res2 = checkAvailable(ptr1->next->name, ptr1->next->fasility);
	        	double f2 = strtod(res2,NULL);
	            if(f1 > f2 && strcmp(type,"ascending")){ 
	                swapPlace(ptr1, ptr1->next);
	                swapped = 1;
	            }else if(f1 < f2 && strcmp(type,"descending")){
	            	swapPlace(ptr1, ptr1->next);
	                swapped = 1;
				}
	            ptr1 = ptr1->next;
	        }
	        lptr = ptr1;
	    } while (swapped);
	}
	
	//FUNGSI UNTUK MENDISPLAY BELI MINUMAN
	void buyDrink(struct drink *temp){
		int y = 1, x = 50,i = 1,flag = 1,pilihan = 0;
		struct drink *temp2 = heads;
		gotoxy(45,22);printf("                                       ");
		gotoxy(x+7,y);printf("==== MENU ====");y+=2;
		gotoxy(x,y);Garis(32);y++;
		gotoxy(x,y);printf("|%2s|%20s|%6s|\n","No","Minuman","Harga");y++;
		gotoxy(x,y);Garis(32);y++;
		while(temp != NULL){
			gotoxy(x,y);
			printf("|%2d|%20s|%6d|\n",i,temp->minuman,temp->price);
			y++;i++;
			temp = temp->next;
		}
		gotoxy(x,y);Garis(32);y++;
		flag = 2;
		while(flag == 2){
			pilihan = 0;
			gotoxy(40,22);printf("                                       ");
			gotoxy(x,y+1);printf("Pilih minuman (0 untuk keluar):");
		    gotoxy(x,y+2);scanf("%d",&pilihan);
		    if(pilihan > i){
		    	flag = 2;
		    	textcolor(15,4);
				gotoxy(40,22);printf("PILIHAN TIDAK DIKENALI COBA KETIK ULANG");textcolor(0,15);
				getch();
			}else if(pilihan == 0){
				flag = 1;
			}else {
				flag = 0;
			}
		}
		if(pilihan != 0){
			for(i = 1;i<pilihan;i++) temp2 = temp2->next;
			int mount;
			gotoxy(x,y+3);printf("Banyak minuman: ");scanf("%d",&mount);
			hargaTotal += temp2->price*mount;
			strcpy(items[count],temp2->minuman);
			priceItems[count] = temp2->price*mount;
			mounts[count] = mount;
			count++;
			gotoxy(x,y+4);
			printf("Anda sudah membeli %s", temp2->minuman);
			gotoxy(x,y+5);system("pause");
		}
		system("cls");
	};
	
	//FUNGSI UNTUK MEMILIH TEMPAT YANG AKAN DI SEWA
	void placeDisplay(char type[15], char id[10]){
		int y = 1, x = 0,i = 1,flag = 1,pilihan = 0,switch_fill,count_dashed;
		char tried;
		int tanggal,bulan,tahun;
		int arr[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		char tanggal_temp[50] = {0}, bulan_temp[50] = {0}, tahun_temp[50] = {0}, tahun_temp2[50] = {0}, temp[50]={0}, ttl[10];
		struct place *temp2 = head;
		while(flag == 1){
			system("cls");
			gotoxy(40,22);printf("                                       ");
			struct place *temp = head;
			if(strcmp(type,"ascending") == 0 || strcmp(type,"descending") == 0) 
				bubbleSortPlace(temp,type);
			i=1;y=1;
			gotoxy(x+52,y);printf("==== MENU ====");y+=3;
			gotoxy(x,y);Garis(119);y++;
		    gotoxy(x,y);printf("|%2s|%15s|%6s|%25s|%65s|\n","No","Fasilitas","Harga","Ketersediaan","Fitur");y++;
		    gotoxy(x,y);Garis(119);y++;
			while(temp != NULL){
				gotoxy(x,y);
				const char *res = checkAvailable(temp->name, temp->fasility);
				double f1 = strtod(res,NULL);
				if(strcmp(res,"9999999") == 0)
					printf("|%2d|%15s|%6d|%25s|%65s|\n",i,temp->name,temp->price,"Fasilitas masih tersedia",temp->fasility);
				else if(strcmp(res,"-1") == 0)
					printf("|%2d|%15s|%6d|%25s|%65s|\n",i,temp->name,temp->price,"Fasilitas sedang dipakai",temp->fasility);
				else if(f1 > 24){
					f1 = f1/24;
					char times[7];
					snprintf(times, 7, "%f", f1);
					printf("|%2d|%15s|%6d|Sedia hingga %7s Hari|%65s|\n",i,temp->name,temp->price,times,temp->fasility);
				}
				else
					printf("|%2d|%15s|%6d|Sedia hingga %8s Jam|%65s|\n",i,temp->name,temp->price,res,temp->fasility);
				y++;i++;
				temp = temp->next;
			}
			gotoxy(x,y);Garis(119);
		    gotoxy(x+32,y+1);printf("[1] Pilih Tempat");
		    gotoxy(x+32,y+2);printf("[0] Kembali");
		    gotoxy(x+32,y+3);printf("Pilihan => ");scanf(" %c", &tried);
		    switch(tried){
		    	case 48:
		    		flag = 0;
		    		break;
		    	case 49:
		    		flag = 2;
		    		break;
		    	default:
		    		textcolor(15,4);
					gotoxy(40,y+4);printf("PILIHAN TIDAK DIKENALI COBA KETIK ULANG");textcolor(0,15);
					getch();
		    		break;	
			}
		}
		
		while(flag == 2){
			pilihan = 0;
			gotoxy(40,y+4);printf("                                       ");
			gotoxy(x+32,y+1);printf("Pilih berdasarkan nomor di atas: ");
		    gotoxy(x+32,y+2);printf("           ");gotoxy(x+32,y+3);printf("            ");
		    gotoxy(x+35,y+2);scanf("%d",&pilihan);
		    if(pilihan >= i){
		    	flag = 2;
		    	textcolor(15,4);
				gotoxy(40,y+4);printf("PILIHAN TIDAK DIKENALI COBA KETIK ULANG");textcolor(0,15);
				getch();
			}else{
				flag = 0;
			}
		}
		for(i = 1;i<pilihan;i++) temp2 = temp2->next;
		const char *rex = checkAvailable(temp2->name, temp2->fasility);
		int cancel = 0,esp=0;
		if(pilihan != 0){
			if(strcmp(rex,"-1") == 0){
				textcolor(15,4);
				gotoxy(47,3);printf("TIDAK TERSEDIA!");textcolor(0,15);
				getch();
			}
			else{
				struct renthistory *iterator,*temps;
				iterator = (struct renthistory*)malloc(sizeof(struct renthistory));
				double seconds = -1,seconds2 = -1;
				do{
					int jam,menit;
					int hours,minutes;
			  		struct tm timeinfo = *localtime(&(time_t){time(NULL)});
					gotoxy(x+32,y+3);printf("Lama sewa (HH:MM) = ");scanf("%d:%d",&jam,&menit);
					hargaTotal += temp2->price*jam;
					hargaTotal += temp2->price*menit/60;
					priceItems[count] = temp2->price*jam + temp2->price*menit/60;
					do {
						count_dashed = 0;
						switch_fill = 0;
						gotoxy(x+32,y+4);printf("Tanggal (DD-MM-YYYY)= ");scanf(" %[^\n]s", ttl);
						gotoxy(x+40,2);printf("                                     ");
						for(i = 0; ttl[i] != '\0';i++){
							if(ttl[i] == '-'){
								count_dashed++;
								switch_fill++;
								continue;
							}
							if(switch_fill == 0) strcat(tanggal_temp, &ttl[i]);
							else if(switch_fill == 1) strcat(bulan_temp, &ttl[i]);
							else if(switch_fill == 2) strcat(tahun_temp2, &ttl[i]);
						}
						for(i = 0; i < 4;i++){
							tahun_temp[i] = tahun_temp2[i];
						}
						tanggal = atoi(tanggal_temp);
						bulan = atoi(bulan_temp);
						tahun = atoi(tahun_temp);
						if(tahun%4 == 0) arr[1] = 29;
						gotoxy(x+40,2);
						textcolor(15,4);
						if(strlen(ttl) != 10 || count_dashed != 2){
							printf("Masukkan tanggal dengan benar        ");
						}else if(tanggal > arr[bulan-1] || tanggal < 1){
							printf("Masukkan tanggal 1-%d, input ulang!  ",arr[bulan-1]);
						}else if(bulan > 12 || bulan < 1){
							printf("Bulan masehi hanya 1-12, input ulang!");
						}
						textcolor(0,15);
						strcpy(tanggal_temp,temp);
						strcpy(bulan_temp,temp);
						strcpy(tahun_temp,temp);
						strcpy(tahun_temp2,temp);
					} while(strlen(ttl) != 10 || count_dashed != 2 || tanggal > arr[bulan-1] || tanggal < 1 || bulan > 12 || bulan < 1);
					gotoxy(x+40,y+5);printf(":");
					gotoxy(x+32,y+5);printf("Pukul ");scanf("%d",&hours);
					gotoxy(x+41,y+5);scanf("%d",&minutes);
					timeinfo.tm_year = tahun - 1900;
					timeinfo.tm_mon = bulan - 1;
					timeinfo.tm_mday = tanggal;
					timeinfo.tm_min = minutes;
					timeinfo.tm_hour = hours;
					timeinfo.tm_sec = 0;
					time_t start = mktime(&timeinfo);
					strftime(iterator->jamMasuk,24,"%d-%m-%Y %H:%M", &timeinfo);
					timeinfo.tm_min = minutes + menit;
					timeinfo.tm_hour = hours + jam;
					time_t stop = mktime(&timeinfo);
					strftime(iterator->jamKeluar,24,"%d-%m-%Y %H:%M", &timeinfo);
					struct renthistory *test = top;
					struct tm breakdown = {0};
					struct tm breakdown2 = {0};
					int year = 0, month = 0, day = 0, hour = 0, min = 0;
					int year2 = 0, month2 = 0, day2 = 0, hour2 = 0, min2 = 0;
					test= top;
					while(test != NULL){
						if(strcmp(temp2->name,test->namaTempat) == 0){
							if (sscanf(test->jamMasuk, "%2d-%2d-%4d %2d:%2d", &day,&month,&year, &hour, &min) == 5) {
							    breakdown.tm_year = year - 1900;
							    breakdown.tm_mon = month - 1;
							    breakdown.tm_mday = day;
							    breakdown.tm_hour = hour;
							    breakdown.tm_min = min;
							}
							if (sscanf(test->jamKeluar, "%2d-%2d-%4d %2d:%2d", &day2, &month2, &year2, &hour2, &min2) == 5) {
								breakdown2.tm_year = year2 - 1900;
								breakdown2.tm_mon = month2 - 1;
								breakdown2.tm_mday = day2;
								breakdown2.tm_hour = hour2;
							    breakdown2.tm_min = min2;
							}
							time_choosen1 = mktime(&breakdown);
							time_choosen2 = mktime(&breakdown2);
							seconds = difftime(start, time_choosen1);
							seconds2 = difftime(stop, time_choosen2);
						}
						test = test->next;
					}
					if((seconds <= 0 && seconds2 >= 0) || (seconds >= 0 && seconds2 <= 0)){
						cancel = 1;
				    	textcolor(15,4);
						gotoxy(40,y+7);printf("JADWAL TIDAK BISA DISEWA, TEKAN APAPUN UNTUK KELUAR");textcolor(0,15);
						esp = getch();
						break;
					}else{
						cancel = 0;
						break;
					}
				}while(((seconds <= 0 && seconds2 >= 0) || (seconds >= 0 && seconds2 <= 0) || cancel == 1) && esp != 27);
				if(cancel == 0){
					char atasnama[10],*Tempat = temp2->name;
					strcpy(items[count],temp2->name);
					if(strcmp(id,"0") == 0){
						gotoxy(x+32,y+6);printf("Atas nama (max 10 char): ");
						scanf(" %[^\n]s",atasnama);
						strcpy(iterator->id,atasnama);
					}else{
						char *tempId = id;
						gotoxy(x+32,y+6);printf("Dengan ID user: %s", tempId);
						strcpy(iterator->id,id);
					}
					strcpy(iterator->namaTempat,temp2->name);
					mounts[count] = 1;
					count++;
					FILE * fptr;
					fptr = fopen("riwayat.txt", "a");
					fprintf(fptr, "%s,%s,%s,%s\n", iterator->jamMasuk,iterator->jamKeluar,temp2->name,id);
					fclose(fptr);
					
					if(top == NULL){
						top = iterator;
						top->next = NULL;
					}else{
						temps = top;
						while (temps->next != NULL)
					    	temps = temps->next;
						temps->next = iterator;
						iterator->next = NULL;
					}
					
					gotoxy(x+32,y+7);printf("Anda sudah menyewa %s", temp2->name);
					gotoxy(x+32,y+8);system("pause");	
				}else{
					hargaTotal -= 0;
					free(iterator);
				}
			}
		}
		system("cls");
	}
	
	//FUNGSI UNTUK MENGECEK KETERSEDIAAN TEMPAT AKAN MERETURN STRING WAKTU KETIKA TERSEDIA
	const char *checkAvailable(char *name, char *availability){
		struct renthistory *temp;
		double seconds[100],seconds2[100];
		time_t result = 0;
		time_t result2= 0;
		time_t now = 0;
		temp = top;
		char buf[7],amount[100][7];
		int year = 0, month = 0, day = 0, hour = 0, min = 0,amountInt = 0;
		int year2 = 0, month2 = 0, day2 = 0, hour2 = 0, min2 = 0;
		struct tm breakdown = {0};
		struct tm breakdown2 = {0};
		struct tm tm = *localtime(&(time_t){time(NULL)});
		while(temp != NULL){
			now = mktime(&tm);
			if(strcmp(name,temp->namaTempat) == 0){
				if (sscanf(temp->jamMasuk, "%2d-%2d-%4d %2d:%2d", &day,&month,&year, &hour, &min) == 5) {
				    breakdown.tm_year = year - 1900;
				    breakdown.tm_mon = month - 1;
				    breakdown.tm_mday = day;
				    breakdown.tm_hour = hour;
				    breakdown.tm_min = min;
				}
			   	result = mktime(&breakdown);
			   	seconds[amountInt] = difftime(now, result);
			   	if(seconds[amountInt] >= 0){
			   		if (sscanf(temp->jamKeluar, "%2d-%2d-%4d %2d:%2d", &day2, &month2, &year2, &hour2, &min2) == 5) {
						breakdown2.tm_year = year2 - 1900;
						breakdown2.tm_mon = month2 - 1;
						breakdown2.tm_mday = day2;
						breakdown2.tm_hour = hour2;
					    breakdown2.tm_min = min2;
					}
				   	result2 = mktime(&breakdown2);
				   	seconds2[amountInt] = difftime(now, result2);
				   	if(seconds2[amountInt] < 0) strcpy(amount[amountInt],"-1");
				   	else strcpy(amount[amountInt],"9999999");
				}else{
					snprintf(buf, 7, "%f", fabs(seconds[amountInt]/3600));
					buf[7] = '\0';
					char buf2[7];
					strcpy(buf2,buf);
					if(fabs(seconds[amountInt]/3600) >= 9999999) strcpy(amount[amountInt],"9999999");
					else strcpy(amount[amountInt],buf2);
				}
				amountInt++;
			}
			temp=temp->next;
		}
		if(amountInt != 0){
			if(amountInt == 1){
				char *re = amount[amountInt-1];
				return re;
			}
			char buf3[7];int m;
			for(m = 0;m < amountInt-1;m++){
				strcpy(buf3,amount[m]);
				if(strcmp(amount[m],"-1") == 0 || strcmp(amount[m+1],"-1") == 0) return "-1";
				if(strcmp(amount[m],amount[m+1]) > 0) strcpy(buf3,amount[m+1]);
				buf3[7] = '\0';
			}
			char *ret = buf3;
			return ret;
		}
		return "9999999";
	}
	
	//FUNGSI UNTUK MENDISPLAY TEMPAT DAN MEMILIH UNTUK SORTING ATAU TIDAK
	void rentPlace(char id[10]){
		int y = 1, x = 0,i = 1,flag = 1;
		char tried;
		
		while(flag){
			system("cls");
			gotoxy(40,25);printf("                                       ");
			struct place *temp = head;
			i=1;y=1;
			gotoxy(x+52,y);printf("==== MENU ====");y+=3;
			gotoxy(x,y);Garis(119);y++;
		    gotoxy(x,y);printf("|%2s|%15s|%6s|%25s|%65s|\n","No","Fasilitas","Harga","Ketersediaan","Fitur");y++;
		    gotoxy(x,y);Garis(119);y++;
			while(temp != NULL){
				gotoxy(x,y);
				const char *res = checkAvailable(temp->name, temp->fasility);
				double f1 = strtod(res,NULL);
				if(strcmp(res,"9999999") == 0)
					printf("|%2d|%15s|%6d|%25s|%65s|\n",i,temp->name,temp->price,"Fasilitas masih tersedia",temp->fasility);
				else if(strcmp(res,"-1") == 0)
					printf("|%2d|%15s|%6d|%25s|%65s|\n",i,temp->name,temp->price,"Fasilitas sedang dipakai",temp->fasility);
				else if(f1 > 24){
					f1 = f1/24;
					char times[7];
					snprintf(times, 7, "%f", f1);
					printf("|%2d|%15s|%6d|Sedia hingga %7s Hari|%65s|\n",i,temp->name,temp->price,times,temp->fasility);
				}
				else
					printf("|%2d|%15s|%6d|Sedia hingga %8s Jam|%65s|\n",i,temp->name,temp->price,res,temp->fasility);
				y++;i++;
				temp = temp->next;
			}
			gotoxy(x,y);Garis(119);y+=3;
		    gotoxy(x+38,y);printf("[1] Urutkan berdasarkan ketersediaan secara menurun");y++;
		    gotoxy(x+38,y);printf("[2] Urutkan berdasarkan ketersediaan secara menaik");y++;
		    gotoxy(x+38,y);printf("[3] Data normal");y++;
		    gotoxy(x+38,y);printf("[0] Ke menu awal");y++;
		    gotoxy(x+38,y);printf("Pilihan => ");scanf(" %c", &tried);y++;
		    switch(tried){
		    	case 48:
		    		flag = 0;
		    		system("cls");
		    		break;
		    	case 49:
		    		flag = 0;system("cls");
		    		placeDisplay("ascending",id);
		    		break;
		    	case 50:
		    		flag = 0;
		    		placeDisplay("descending",id);
		    		break;
		    	case 51:
		    		flag = 0;
		    		placeDisplay("non",id);
		    		break;
		    	default:
		    		textcolor(15,4);
					gotoxy(40,25);printf("PILIHAN TIDAK DIKENALI COBA KETIK ULANG");textcolor(0,15);
					getch();
		    		break;
			}
		}
	}
	
	//FUNGSI UNTUK MEMBATALKAN SEWA
	void batalSewa(char id[10]){
		int i = 0,y = 1, x = 33,l;
		int year = 0, month = 0, day = 0, hour = 0, min = 0;
		double seconds,seconds2;
		char nama[10],jamMasuk[25],namaTempat[50];
		time_t now,result;
		struct tm breakdown = {0};
		struct renthistory *temp = top;
		struct tm tm = *localtime(&(time_t){time(NULL)});
		FILE *rent;
    	FILE *tempfile;
		gotoxy(x+15,y);printf("==== BATAL SEWA ====");y+=3;
		if(strlen(id) == 1){
			gotoxy(x+3,y);printf("Atas nama: ");scanf(" %[^\n]s", nama);y++;
		}
		gotoxy(x+3,y);Garis(70);y++;
		gotoxy(x+3,y);printf("|%2s|%15s|%24s|%24s|","No","Nama Tempat","Mulai Sewa","Akhir Sewa");y++;
		gotoxy(x+3,y);Garis(70);y++;i=0;
		while(temp != NULL){
			if (sscanf(temp->jamMasuk, "%2d-%2d-%4d %2d:%2d", &day,&month,&year, &hour, &min) == 5) {
				breakdown.tm_year = year - 1900;
				breakdown.tm_mon = month - 1;
				breakdown.tm_mday = day;
				breakdown.tm_hour = hour;
				breakdown.tm_min = min;
			}
			now = mktime(&tm);
			result = mktime(&breakdown);
			seconds = difftime(now, result);
			char get_id[10];
			strcpy(get_id,temp->id);
			if(get_id[strlen(get_id)-1] == '\n') get_id[strlen(get_id)-1] = '\0';
			if((strcmp(get_id,id) == 0 || strcasecmp(get_id,nama) == 0) && seconds < 0){
				gotoxy(x+3,y);printf("|%2d|%15s|%24s|%24s|",i+1,temp->namaTempat,temp->jamMasuk,temp->jamKeluar);y++;
				i++;
			}
			temp = temp->next;
		}
		if(i == 0){
			gotoxy(x+3,y);printf("|%-68s|","Belum pernah sewa");y++;
			gotoxy(x+3,y);Garis(70);y++;
			gotoxy(x+3,y);system("pause");system("cls");
		}else{
			gotoxy(x+3,y);Garis(70);y++;
			do{
				gotoxy(x+3,y);printf("Penyewaan yang akan dibatalkan (nomor di atas, 0 untuk keluar): ");scanf("%d",&l);
				if(l > i || l<0){
					gotoxy(x+3,y+1);printf("MASUKKAN NOMOR DENGAN BENAR!");
				}
			}while(l > i || l<0);i=0;
			if(l != 0){
				int n=0,p=0;
				struct renthistory *tempa = top;
				while(tempa != NULL){
					if (sscanf(tempa->jamMasuk, "%2d-%2d-%4d %2d:%2d", &day,&month,&year, &hour, &min) == 5) {
						breakdown.tm_year = year - 1900;
						breakdown.tm_mon = month - 1;
						breakdown.tm_mday = day;
						breakdown.tm_hour = hour;
						breakdown.tm_min = min;
					}
					result = mktime(&breakdown);
					seconds = difftime(now, result);
					char get_id[10];
					strcpy(get_id,tempa->id);
					if(get_id[strlen(get_id)-1] == '\n') get_id[strlen(get_id)-1] = '\0';
					if((strcmp(get_id,id) == 0 || strcasecmp(get_id,nama) == 0) && seconds < 0){
						if(l-1 == n){
							strcpy(namaTempat,tempa->namaTempat);
							strcpy(jamMasuk,tempa->jamMasuk);
							break;
						}
						n++;
					}
					p++;
					tempa = tempa->next;
				}
				struct renthistory *temps = top, *prev;
				char get_id[10];
				strcpy(get_id,temps->id);
				if(get_id[strlen(get_id)-1] == '\n') get_id[strlen(get_id)-1] = '\0';
				if (temps != NULL && strcmp(get_id,id) == 0 && strlen(id) > 1) {
				    top = temps->next; // Changed head
				    free(temps);
				}else if(temps != NULL && strcasecmp(get_id,nama) == 0 && strlen(id) == 1){
					top = temps->next; // Changed head
				    free(temps);
				}else{
					while (temps != NULL && (strcasecmp(temps->id,nama) != 0 || strcmp(get_id,id) != 0) && strcmp(temps->jamMasuk,jamMasuk) != 0 && strcmp(temps->namaTempat,namaTempat) != 0) {
					   	prev = temps;
					    temps = temps->next;
					}
				    if (temps != NULL){
				    	prev->next = temps->next;
				    	free(temps);
					}else{
						gotoxy(x+3,y+1);printf("Key tidak ditemukan");getch();
						system("cls");
						return;
					}
				}
				rent = fopen("riwayat.txt", "w");
				struct renthistory *t = top;
			    while(t != NULL){
					strcpy(get_id,t->id);
					if(get_id[strlen(get_id)-1] == '\n') get_id[strlen(get_id)-1] = '\0';
			        fprintf(rent, "%s,%s,%s,%s\n", t->jamMasuk,t->jamKeluar,t->namaTempat,get_id);
			        t = t->next;
				}
				fclose(rent);
				gotoxy(x+3,y+1);system("pause");
			}else{
				gotoxy(x+3,y+1);printf("Anda membatalkan menu ini!");getch();
			}
		}
		system("cls");
	}
	
	//FUNGSI TENTANG PROGRAM INI
	void rules(){
		int y, flag = 1;
		y = 1;
		system("cls");
		gotoxy(53,y);printf("==== RULES ====");
		y+=5;gotoxy(10,y);printf("Selamat datang di sport center! di sini user akan dapat menyewa tempat olahraga beserta minumannya");
		y++;gotoxy(10,y);printf("untuk member akan mendapatkan potongan harga sebesar 45% dari harga total.");
		y++;gotoxy(10,y);printf("Menu perpanjang akun dan berhenti layanan hanya dapat dilakukan oleh member.");
		y++;gotoxy(10,y);printf("Ketika menyewa tempat, apabila waktu mengiris waktu yang dapat disewa, penyewaan tidak akan terjadi.");
		y++;gotoxy(10,y);printf("Struk akan ditampilkan ketika sudah menyewa atau membeli minuman!");
		y++;gotoxy(10,y);system("pause");
			
	}
	
	//FUNGSI MENDISPLAY MAIN MENU AWAL
	void mainMenu(int *y){
		int flag = 1;
		char tried;
		while(flag){
			*y = 1;
			system("cls");
			displayLogo(y);
			(*y)+=5;gotoxy(44,(*y));printf("[1] Menyewa Tempat atau beli minuman");
			(*y)+=2;gotoxy(44,(*y));printf("[2] Daftar Member");
			(*y)+=2;gotoxy(44,(*y));printf("[3] Perpanjang Member");
			(*y)+=2;gotoxy(44,(*y));printf("[4] Berhenti Layanan Member");
			(*y)+=2;gotoxy(44,(*y));printf("[5] Peraturan Sport Centre");
			(*y)+=2;gotoxy(44,(*y));printf("[0] Keluar");
			(*y)+=2;gotoxy(44,(*y));printf("Pilihan => ");scanf(" %c", &tried);
			
			switch(tried){
				case 48:
					flag = 0;
					break;
				case 49:
					flag = 1;
					system("cls");
					rentPlaceandStuffMenu();
					break;
				case 50:
					flag = 1;
					system("cls");
					memberRegister();
					break;
				case 51:
					flag = 1;
					system("cls");
					perpanjangMember("Lanjut");
					break;
				case 52:
					flag = 1;
					system("cls");
					perpanjangMember("Berhenti");
					break;
				case 53:
					flag = 1;
					system("cls");
					rules();
					break;
				default:
					textcolor(15,4);
					gotoxy(40,(*y)+3);printf("PILIHAN TIDAK DIKENALI COBA KETIK ULANG");textcolor(0,15);
					getch();
					break;
			}
		}
	}
#endif