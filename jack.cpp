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
#define MAX_ARR		    52
#define SIZE		    26
#define sizeR		    25
#define sizeC		    80
#define startTail	    5

#define goxy(x,y) printf("\033[%d;%dH", (y), (x))

typedef long long int ll;
using namespace std;

int tailX[startTail], tailY[startTail];
int fruitX, fruitY;
int tailLength = 0;
int welcoming = 0;
int a, b, c;
int gameover;
char flag;
int score;

//Snake coordinate
void initializeSnake(){
    a = 30; 
    b = 18;
	gameover = 0;	
	score = 0;
}

//Fruit coordinate
void initializeFruit(){
	label1:
		fruitX =  rand() % (sizeC - 2) + 1;
		if(fruitX <= 2) goto label1;
        if(fruitX == a) goto label1;
        if(fruitX >= sizeC-1) goto label1;
       
		

	label2:
		fruitY =  rand() % (sizeR - 2) + 1;
		if(fruitY <= 2) goto label2;
        if(fruitY == b) goto label2;
        if(fruitY >= sizeR-1) goto label2;
        
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
	printf(GREEN"%c   "YELLOW"Score\t: [ "RESET" "YELLOW" ]"GREEN"   %c  "YELLOW"3. Logout"RESET"                 "GREEN"%c"RESET"  "YELLOW">>"RESET"                   "GREEN"%c"RESET, 186,186,186,186);
	printf("\n");
	printf(GREEN"%c", 200);
	for(int i=0; i<sizeC-2; i++){
		printf("%c", 205);
	}
	printf("%c"RESET, 188);

    char *startMessage = "To Play Press [Space]";
    goxy(30, 18);
    printf(startMessage);

    goxy(62,27);
    flag = getch();
    fflush(stdin);
}

//Snake Movement
void snakeMove(const char c){
    //Non Logic condition
    if(c == 'q'){ 
        printMap();
    }

    // Snake Logic 
    if(c == 'a' && a > 2){
        a--;
    } else if (c == 'a' && a == 2){
        a = sizeC-1;
    }

    if(c == 'd' && a < sizeC-1){
        a++;
    } else if (c == 'd' && a == sizeC-1){
        a = 2;
    }

    if(c == 'w' && b > 2){
        b--;
    } else if (c == 'w' && b == 2){
        b = sizeR-1;
    }

    if(c == 's' && b < sizeR-1){
        b++;
    } else if (c == 's' && b == sizeR-1){
        b = 2;
    }
}

// Snake Body Logic
void snakeBody(){
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

    // Updating Snake Head
    tailX[0] = a;
    tailY[0] = b;
}

// Fruit Draw
void snakeFruitDraw(){
    goxy(fruitX, fruitY);
    printf(PINK"%c"RESET, 254);
}

//Snake Draw
void snakeDraw(){
    for(int i = 0; i < tailLength; i++){
        goxy(tailX[i], tailY[i]);
        printf(YELLOW"%c"RESET, 219);
    }
}

void scoreDraw(){
    goxy(20,27);
    printf(YELLOW"%d"RESET, score);
}

//Snake Fruit Eat
void snakeFruitEat(){
    if(a == fruitX && b == fruitY){
        initializeFruit();
        tailLength++;
        score+=10;
        printMap();
    }
}

void draw(){
    snakeDraw();
    snakeFruitDraw();
}

//Snake Game
void SnakeGame(){
    while(true){
        if(kbhit()){
            c = getch();

            snakeMove(c);
            snakeBody();
            draw();
            snakeFruitEat();
        }
    }
}

//Switch in Menu
void snakeSwitch(){
    switch(flag){
        case ' ':
            SnakeGame();
            break;
        case '1':
            break;
        case '2':
            break;
        case '3':
            break;
        default:
            break;
    }
}

int main(){
    srand(time(0));

    initializeSnake();
    initializeFruit();
    printMap();
    snakeSwitch();

    return 0;
}
