#include<bits/stdc++.h>
#include<windows.h>
#include<iostream>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<dos.h> 

#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define PURPLE	"\x1b[35m"
#define ORANGE	"\033[0;33m"
#define SILVER	"\033[1;30m"
#define PINK 	"\x1b[35;1m"
#define RESET   "\033[0m"
#define MAX_ARR		52
#define SIZE		26
#define sizeR		25
#define sizeC		80
#define startTail	5

#define goxy(x,y) printf("\033[%d;%dH", (y), (x))

typedef long long int ll;
using namespace std;

int welcoming = 0;

int tailX[startTail], tailY[startTail];
int a, b, c, x, y;
int tailLength = 0;
int gameover;
int score;
int fruitX, fruitY;
char flag;


void initialize(){
    a = 30; 
    b = 18;
	gameover = 0;
	x = sizeR / 2;
	y = sizeR / 2;

	label1:
		fruitX =  rand() % 25;
		if(fruitX == 0) goto label1;
		

	label2:
		fruitY =  rand() % 80;
		if(fruitY == 0) goto label2;
		
	score = 0;
}

void printMap(){
	system("cls");

	//Main Screen
    for(int i=0; i<sizeR; i++){
        for(int j=0; j<sizeC; j++){
            if(j == 0 ||  j==sizeC-1){
				if(i == 0 && j == 0){
					printf(BLUE"%c"RESET, 201);
				}else if(i == 0 && j == sizeC-1){
					printf(BLUE"%c"RESET, 187);
				}else if(i == sizeR-1 && j == 0){
					printf(GREEN"%c"RESET, 204);
			}else if(i == sizeR-1 && j == sizeC-1){
					printf(GREEN"%c"RESET, 185);
				} else {
               		printf(BLUE"%c"RESET, 186);
				}
            } else if(i == 0){
				printf(BLUE"%c"RESET, 205); 	
			} else if(i==sizeR-1){
				printf(GREEN"%c"RESET, 205); 	
			} else { 
                printf("%c", 176); 
            }   
        }
		printf("\n");
    }

	//Bottom Screen
	char* username = "Agent Vincentius";
	printf(GREEN"%c   "PURPLE"*Snake Game"GREEN"           %c  "YELLOW"1. How to play   2. Exit"RESET"  "GREEN"%c"RESET"  "ORANGE"%-10s"RESET"     "GREEN"%c"RESET, 186, 186,186, username,186);
	printf("\n");
	printf(GREEN"%c   "YELLOW"Score\t: [ "RESET"%d"YELLOW" ]"GREEN"   %c  "YELLOW"3. Logout"RESET"                 "GREEN"%c"RESET"  "YELLOW">>"RESET"                   "GREEN"%c"RESET, 186, score,186,186,186);
	printf("\n");
	printf(GREEN"%c", 200);
	for(int i=0; i<sizeC-2; i++){
		printf("%c", 205);
	}
	printf("%c"RESET, 188);

    char *startMessage = "To Play Press [Shift]";
    goxy(30, 18);
    printf(startMessage);

    goxy(62,27);
    flag = getch();
    fflush(stdin);
}

void logic(){
    while(true){
        if(kbhit()){
            c = getch();
            if(c == 'q'){ // Jika tombol 'q' ditekan, keluar dari program
                break;
            }

            // Memperbarui posisi kepala berdasarkan input
            if(c == 'a' && a > 1){
                a--;
            }
            if(c == 'd' && a < 80){
                a++;
            }
            if(c == 'w' && b > 1){
                b--;
            }
            if(c == 's' && b < 25){
                b++;
            }

            // Menghapus ekor terlama
            if(tailLength == startTail){
                goxy(tailX[tailLength-1], tailY[tailLength-1]);
                printf("%c", 176);
                for(int i = tailLength - 1; i > 0; i--){
                    tailX[i] = tailX[i - 1];
                    tailY[i] = tailY[i - 1];
                }
            } else {
                for(int i = tailLength; i > 0; i--){
                    tailX[i] = tailX[i - 1];
                    tailY[i] = tailY[i - 1];
                }
                tailLength++;
            }

            // Memperbarui posisi kepala di array ekor
            tailX[0] = a;
            tailY[0] = b;

            // Menggambar kepala dan ekor
            for(int i = 0; i < tailLength; i++){
                goxy(tailX[i], tailY[i]);
                printf(YELLOW"%c"RESET, 219);
            }
        }
    }
}


int main(){
    initialize();
    printMap();
    logic();
    

    return 0;
}
