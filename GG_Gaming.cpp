#include<windows.h>
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
#define RESET   "\033[0m"
#define MAX_ARR 52
#define SIZE 26

typedef long long int ll;

int welcoming = 0;

void blink();
void splash();
void loadingAnimation();
void menuLoading();

struct GameData{
	int snakeScore;
	int blackJackScore;
	int bubbleScore;
	int rpgScore;
};

struct Account{
	char username[MAX_ARR];
	char password[MAX_ARR];
};

struct Data{
	GameData* gameData;
	Account* accountData;
	Data* next;
	Data* prev;
}*head[SIZE], *tail[SIZE];


//Hash Function
int hashFunction(char username[]){
	for(int i=0; i<strlen(username); i++)
		if(username[i] >= 'a' && username[i] <= 'z')
			username[i] -= 32;
	int temp = 0;
	for(int i=0; i<strlen(username); i++) temp += username[i];
	return temp % SIZE;
}


//Data structure -> Implementing Hash Table Chaining
void insertUserData(const char username[], const char password[], const int snakeScore, const int blackJackScore, const int bubbleScore, const int rpgStore){
	Account* account = (Account*)malloc(sizeof(Account));
	strcpy(account->username, username);
	strcpy(account->password, password);

	GameData* gameData = (GameData*)malloc(sizeof(GameData));
	gameData->blackJackScore = blackJackScore;
	gameData->bubbleScore = bubbleScore;
	gameData->rpgScore = rpgStore;
	gameData->snakeScore = snakeScore;

	Data* data = (Data*)malloc(sizeof(Data));
	data->accountData = account;
	data->gameData = gameData;
	data->next = data->prev = NULL;


	int idx = hashFunction(account->username);
	if(!head[idx]) head[idx] = tail[idx] = data;
	else {
		tail[idx]->next = data;
		data->prev = tail[idx];
		tail[idx] = data;
	}
}

//Admin Data Structure function
void printUser(){
	system("cls");
	for(int i=0; i<MAX_ARR; i++){
		Data* curr = head[i];
		if(head[i]){
			curr = head[i];
			while(curr){
				printf("%s\n", curr->accountData->username);
				curr = curr->next;
			}
		}
	}
	printf("Press enter to continue...\n");
	getch();
}

void deleteUser(char username[]) {
    const int idx = hashFunction(username);

    if (!head[idx]) {
        printf(RED "User not found\n" RESET);
        return;
    }

    Data* curr = head[idx];
    while (curr) {
        if (strcmp(curr->accountData->username, username) == 0) {
            if (curr == head[idx]) {
                head[idx] = head[idx]->next;
            }
            if (curr == tail[idx]) {
                tail[idx] = tail[idx]->prev;
            }

            if (curr->prev) {
                curr->prev->next = curr->next;
            }
            if (curr->next) {
                curr->next->prev = curr->prev;
            }

            free(curr);
            return;
        }
        curr = curr->next;
    }
    printf(RED "User not found\n" RESET);
}



//User Data Structure Function
void changePassword(char username[], char password[]){
	int idx = hashFunction(username);
	if(!head[idx]){
		printf(RED);
		printf("No account found\n");
		puts("Enter to continue...");
		getch();
		return;
	} else{
		Data* curr = head[idx];
		while(curr){
			if(strcmp(curr->accountData->username, username) == 0){
				strcpy(curr->accountData->password, password);
				break;
			}
			curr =  curr->next;
		}
	}
}

void insertData(){
    char username[MAX_ARR];
	char password[MAX_ARR];
    int snakeScore;
    int blackJackScore;
	int bubbleScore;
	int rpgScore;
    FILE* file = fopen("userData.csv", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    while (fscanf(file, "%20[^,],%20[^,],%d,%d,%d,%d\n", username, password, &snakeScore, &blackJackScore, &bubbleScore, &rpgScore) == 6) {
        insertUserData(username, password, snakeScore, blackJackScore, bubbleScore, rpgScore);
    }
    fclose(file);
}


bool searchingUser(char username[], char password[]){
	int idx = hashFunction(username);
	if(!head[idx]){
		return false;
	}
	Data* curr = head[idx];
	while(curr){
		if(strcmp(curr->accountData->username, username) == 0 && strcmp(curr->accountData->password, password) == 0){
			return true;
			break;
		}
		curr = curr->next;
	}
	return false;
}

bool adminConfirm(char password[]){
	return (strcmp(password, "admin123") == 0);
}

//Animation
void blink(){
	for(int i=0; i<5; i++){
		system("cls");
		puts("");
		printf(BLUE);
		printf("$$$$$$$$\\ $$\\                           $$\\             $$\\     $$\\                   \n");
	    printf("\\__$$  __|$$ |                          $$ |            \\$$\\   $$  |                  \n");
	    printf("   $$ |   $$$$$$$\\   $$$$$$\\  $$$$$$$\\  $$ |  $$\\        \\$$\\ $$  /$$$$$$\\  $$\\   $$\\ \n");
	    printf("   $$ |   $$  __$$\\  \\____$$\\ $$  __$$\\ $$ | $$  |        \\$$$$  /$$  __$$\\ $$ |  $$ |\n");
	    printf("   $$ |   $$ |  $$ | $$$$$$$ |$$ |  $$ |$$$$$$  /          \\$$  / $$ /  $$ |$$ |  $$ |\n");
	    printf("   $$ |   $$ |  $$ |$$  __$$ |$$ |  $$ |$$  _$$<            $$ |  $$ |  $$ |$$ |  $$ |\n");
	    printf("   $$ |   $$ |  $$ |\\$$$$$$$ |$$ |  $$ |$$ | \\$$\\           $$ |  \\$$$$$$  |\\$$$$$$  |\n");
	    printf("   \\__|   \\__|  \\__| \\_______|\\__|  \\__|\\__|  \\__|          \\__|   \\______/  \\______/ \n");
	    printf(RESET);
	    usleep(500000);
	    system("cls");
	    puts("");
	    printf(GREEN);
	    printf(" /$$$$$$$$ /$$                           /$$             /$$     /$$                 \n");
	    printf("|__  $$__/| $$                          | $$            |  $$   /$$/                 \n");
	    printf("   | $$   | $$$$$$$   /$$$$$$  /$$$$$$$ | $$   /$$       \\  $$ /$$//$$$$$$  /$$   /$$\n");
	    printf("   | $$   | $$__  $$ |____  $$| $$__  $$| $$  /$$/        \\  $$$$//$$__  $$| $$  | $$\n");
	    printf("   | $$   | $$  \\ $$  /$$$$$$$| $$  \\ $$| $$$$$$/          \\  $$/| $$  \\ $$| $$  | $$\n");
	    printf("   | $$   | $$  | $$ /$$__  $$| $$  | $$| $$_  $$           | $$ | $$  | $$| $$  | $$\n");
	    printf("   | $$   | $$  | $$|  $$$$$$$| $$  | $$| $$ \\  $$          | $$ |  $$$$$$/|  $$$$$$/\n");
	    printf("   |__/   |__/  |__/ \\_______/|__/  |__/|__/  \\__/          |__/  \\______/  \\______/ \n");
	    printf(RESET);
	    usleep(500000);
	}
}

void splash(){
    printf(BLUE);
    printf("  ____  _              __     ______  _        _   _             \n");
	usleep(300000);
    printf(" |  _ \\| | __ _ _   _  \\ \\   / /  _ \\| |_ __ _| |_(_) ___  _ __  \n");
	usleep(300000);
    printf(" | |_) | |/ _` | | | |  \\ \\ / /| | | | __/ _` | __| |/ _ \\| '_ \\ \n");
	usleep(300000);
    printf(" |  __/| | (_| | |_| |   \\ V / | |_| | || (_| | |_| | (_) | | | |\n");
	usleep(300000);
    printf(" |_|   |_|\\__,_|\\__, |    \\_/  |____/ \\__\\__,_|\\__|_|\\___/|_| |_|\n");
	usleep(300000);
    printf("                |___/                                             \n");
	usleep(300000);
    printf(RESET);
}

void loadingAnimation(){
	printf(GREEN);
	printf("Press enter to skip boot up animation...\n");
	printf("Loading /");
	puts("");
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 219,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176);
	usleep(100000);
	system("cls");
	printf("Press enter to skip boot up animation...\n");
	printf("Loading -");
	puts("");
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 219,219,176,176,176,176,176,176,176,176,176,176,176,176,176,176);
	usleep(100000);
	system("cls");
	printf("Press enter to skip boot up animation...\n");
	printf("Loading \\");
	puts("");
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 219,219,219,176,176,176,176,176,176,176,176,176,176,176,176,176);
	usleep(100000);
	system("cls");
	printf("Press enter to skip boot up animation...\n");
	printf("Loading -");
	puts("");
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 219,219,219,219,176,176,176,176,176,176,176,176,176,176,176,176);
	usleep(100000);
	system("cls");
	printf("Press enter to skip boot up animation...\n");
	printf("Loading /");
	puts("");
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 219,219,219,219,219,176,176,176,176,176,176,176,176,176,176,176);
	usleep(100000);
	system("cls");
	printf("Press enter to skip boot up animation...\n");
	printf("Loading -");
	puts("");
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 219,219,219,219,219,219,176,176,176,176,176,176,176,176,176,176);
	usleep(100000);
	system("cls");
	printf("Press enter to skip boot up animation...\n");
	printf("Loading \\");
	puts("");
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 219,219,219,219,219,219,219,176,176,176,176,176,176,176,176,176);
	usleep(100000);
	system("cls");
	printf("Press enter to skip boot up animation...\n");
	printf("Loading -");
	puts("");
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 219,219,219,219,219,219,219,219,176,176,176,176,176,176,176,176);
	usleep(100000);
	system("cls");
	printf("Press enter to skip boot up animation...\n");
	printf("Loading /");
	puts("");
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 219,219,219,219,219,219,219,219,219,176,176,176,176,176,176,176);
	usleep(100000);
	system("cls");
	printf("Press enter to skip boot up animation...\n");
	printf("Loading -");
	puts("");
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 219,219,219,219,219,219,219,219,219,219,176,176,176,176,176,176);
	usleep(100000);
	system("cls");
	printf("Press enter to skip boot up animation...\n");
	printf("Loading \\");
	puts("");
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 219,219,219,219,219,219,219,219,219,219,219,176,176,176,176,176);
	usleep(100000);
	system("cls");
	printf("Press enter to skip boot up animation...\n");
	printf("Loading -");
	puts("");
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 219,219,219,219,219,219,219,219,219,219,219,219,176,176,176,176);
	usleep(100000);
	system("cls");
	printf("Press enter to skip boot up animation...\n");
	printf("Loading /");
	puts("");
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 219,219,219,219,219,219,219,219,219,219,219,219,219,176,176,176);
	usleep(100000);
	system("cls");
	printf("Press enter to skip boot up animation...\n");
	printf("Loading -");
	puts("");
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 219,219,219,219,219,219,219,219,219,219,219,219,219,219,176,176);
	usleep(100000);
	system("cls");
	printf("Press enter to skip boot up animation...\n");
	printf("Loading \\");
	puts("");
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,176);
	usleep(100000);
	system("cls");
	printf("Press enter to skip boot up animation...\n");
	printf("Loading /");
	puts("");
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	usleep(100000);
	system("cls");
    printf("Done!\n");
   	printf(RESET);
    sleep(1);
}

void menuLoading() {
    system("cls");
    int i;
    const char frames[] = {'/', '-', '\\', '|'};
    const int numFrames = sizeof(frames) / sizeof(frames[0]);
    printf(YELLOW);
    printf("Working on it ");
    fflush(stdout); 
    for (i = 0; i < 10; i++) {
        printf("%c\b", frames[i % numFrames]);
        fflush(stdout);
        usleep(100000); 
    }
    printf(RESET);
}

void adminArt() {
	printf(RED);
    printf("                                                                                                   \n");
	usleep(300000);
    printf("                                          dddddddd                                                 \n");
	usleep(300000);
    printf("               AAA                        d::::::d                          iiii                   \n");
	usleep(300000);
    printf("              A:::A                       d::::::d                         i::::i                  \n");
	usleep(300000);
    printf("             A:::::A                      d::::::d                          iiii                   \n");
	usleep(300000);
    printf("            A:::::::A                     d:::::d                                                 \n");
	usleep(300000);
    printf("           A:::::::::A            ddddddddd:::::d    mmmmmmm    mmmmmmm   iiiiiiinnnn  nnnnnnnn    \n");
	usleep(300000);
    printf("          A:::::A:::::A         dd::::::::::::::d  mm:::::::m  m:::::::mm i:::::in:::nn::::::::nn  \n");
	usleep(300000);
    printf("         A:::::A A:::::A       d::::::::::::::::d m::::::::::mm::::::::::m i::::in::::::::::::::nn \n");
	usleep(300000);
    printf("        A:::::A   A:::::A     d:::::::ddddd:::::d m::::::::::::::::::::::m i::::inn:::::::::::::::n\n");
	usleep(300000);
    printf("       A:::::A     A:::::A    d::::::d    d:::::d m:::::mmm::::::mmm:::::m i::::i  n:::::nnnn:::::n\n");
	usleep(300000);
    printf("      A:::::AAAAAAAAA:::::A   d:::::d     d:::::d m::::m   m::::m   m::::m i::::i  n::::n    n::::n\n");
	usleep(300000);
    printf("     A:::::::::::::::::::::A  d:::::d     d:::::d m::::m   m::::m   m::::m i::::i  n::::n    n::::n\n");
	usleep(300000);
    printf("    A:::::AAAAAAAAAAAAA:::::A d:::::d     d:::::d m::::m   m::::m   m::::m i::::i  n::::n    n::::n\n");
	usleep(300000);
    printf("   A:::::A             A:::::Ad::::::ddddd::::::ddm::::m   m::::m   m::::mi::::::i n::::n    n::::n\n");
	usleep(300000);
    printf("  A:::::A               A:::::Ad:::::::::::::::::dm::::m   m::::m   m::::mi::::::i n::::n    n::::n\n");
	usleep(300000);
    printf(" A:::::A                 A:::::Ad:::::::::ddd::::dm::::m   m::::m   m::::mi::::::i n::::n    n::::n\n");
	usleep(300000);
    printf("AAAAAAA                   AAAAAAAddddddddd   dddddmmmmmm   mmmmmm   mmmmmmiiiiiiii nnnnnn    nnnnnn\n");
	usleep(300000);
	printf(RESET);
	usleep(300000);
	puts("");
	printf("Press enter to continue...");
	getch();
}

void printWithDelay(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        printf("%c", str[i]);
        fflush(stdout);
        usleep(50000);
    }
}


//Mapping
int sizeR = 20;
int sizeC = 20;
char map[20][20];


//Gaming essential
void printMap(){
    for(int i=0; i<sizeR; i++){
        for(int j=0; j<sizeC; j++){
            if(j == 0 || i == 0 || j==sizeR-1 || i==sizeC-1){
                map[i][j] = '#';
            } else {
                map[i][j] = ' ';
            }
        }
    }
    for(int i=0; i<sizeR; i++){
        for(int j=0; j<sizeC; j++){
            printf("%c ", map[i][j]);
        }
        puts("");
    }
}

//Admin essential

void adminMenuSwitch(char input){
	switch(input){
		case '1':
			break;
		case '2':
			// printScoreBoard(10);
			break;
		case '3':
			printUser();
			break;
		case '4':
			break;
		case '5':
			break;
		case '6':
			break;
	}
}

void adminMenu(){
	char input;
	system("cls");
	adminArt();
	system("cls");
    printf(RED);
    printf("Welcome admin\n");
    printf("1. Play\n");
    printf("2. Scoreboard\n");
    printf("3. Agent list\n");
    printf("4. Delete agent\n");
    printf("5. Manage agent\n");
	printf("6. Exit\n");
	printf(">> ");
    printf(RESET);
	input = getch();
	adminMenuSwitch(input);
}


//Login Register
bool check(char str[]){
	int numberTemp = 0;
	int alphaTemp = 0;
	for (int i = 0; str[i] != '\0'; i++) {
        if (((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))) {
            alphaTemp++;
        }
		if((str[i] >= '0' && str[i] <= '9')){
			numberTemp++;
		}
    }
	if(numberTemp > 0 && alphaTemp > 0) return true;
    return false;
}

bool isSpace(char str[]){
	for(int i=0; i<strlen(str); i++){
		if(str[i] == ' '){
			return false;
		}
	}
	return true;
}

bool userLength(char string[]){
	if((strlen(string)) >= 1 && (strlen(string)) <= 26){
		return true;
	}
	return false;
}

bool isAgent(char string[]){
	if(strncmp(string, "Agent ", 6) == 0) return true;
	return false;
}

bool isAdmin(char string[]){
	if(strcmpi(string, "admin") == 0) return true;
	return false;
}

bool isSame(char string1[], char string2[]){
	return (strcmp(string1, string2) == 0);
}

void insertUser(char username[], char password[]){
	FILE* file = fopen("userData.csv", "a");
	if(file){
		fprintf(file,"%s,%s,0,0\n", username, password);
	}
}

bool checkUser(char username[], char password[]){
	return searchingUser(username, password);
}

bool passwordEnter(char pass[]){
	int i=0;
	char ps;
	while((ps = getch()) != '\r'){
		if (ps == '\b') {
            if (i > 0) {
                printf("\b \b");
                i--;
            }
        } else {
            printf("*");
            pass[i++] = ps;
        }
	}
	pass[i] = '\0';
    return true;
}

bool userRegis(char username[]){
	while(true){
		system("cls");
		printf(BLUE);
		printf("Enter your username [1-20 characters]:");
		printf(YELLOW);
		scanf("%[^\n]", username);
		getchar();

		if(!isAgent(username)){
			printf(RED);
			printf("String input must be 'Agent [name]'\n");
			printf(RESET);
		} else if(userLength(username)){
			return true;
		} else {
			printf(RED);
			printf("Must between 1-20 characters\n");
			printf(RESET);
		}
		printf("Press enter to continue...");
		getch();
	}
	return false;
}

bool passRegis(char pass[], char passConf[]){
	system("cls");
	while(true){
		printf(BLUE);
		printf("Enter your password [must be alphanumeric]: ");
		printf(YELLOW);
		passwordEnter(pass);
		
		printf(BLUE);
		printf("Confirm your password [must be same]: ");
		printf(YELLOW);
		passwordEnter(passConf);

		if(!isSame(pass, passConf)){
			printf("Password must be same!\n");
		} else if(!check(passConf)){
			printf("Password must be alphanumeric!\n");
		} else if(isSpace(passConf)){
			return true;
		} else {
			printf("Cannot contain spaces!\n");
		}
		printf("Press enter to continue...");
		getch();
	}
	return false;
}

bool registerAcc(){
	char username[21];
	char password[21];
	char passwordConfirm[21];
	if(userRegis(username) && passRegis(password, passwordConfirm)){
		insertUser(username, password);
		return true;
	}else{
		printf("Register failed!\n");
	}
	printf("Press enter to continue...");
	getch();
	return false;
}

bool loginUser(char username[]){
	while(true){
		system("cls");
		printf(BLUE);
		printf("Enter username: ");
		printf(YELLOW);
		scanf("%[^\n]", username);
		getchar();
		if(isAdmin(username)) return true;

		if(!userLength(username)){
			printf("Username length not met!\n");
		} else if(isAgent(username)){
			return true;
		} else {
			printf("String input must be 'Agent [name]'!\n");
		}
		printf("Press enter to continue...");
		getch();
	}
	return false;
}

bool loginPass(char password[]){
	while(true){
		system("cls");
		printf(BLUE);
		printf("Enter yout password: ");
		printf(YELLOW);
		passwordEnter(password);
		if(isSpace(password) && adminConfirm(password)) return true;

		if(!check(password)){
			printf("Should only contain alphanumeric!\n");
		} else if(isSpace(password)){
			return true;
		} else {
			printf("Cannot contain spaces!\n");
		}
		printf("Press enter to continue...");
		getch();
	}
	return false;
}

bool login(){
    char username[21];
    char password[21];
	if(loginUser(username) && loginPass(password)){
		system("cls");
		menuLoading();
		if(isAdmin(username) && adminConfirm(password)) adminMenu();
		if(checkUser(username, password)){
			return true;
		} else {
			printf(RED);
			printf("Agent not found! Register it first!\n");
		}
	}
	printf("Press enter to continue...");
	getch();
	return false;
}

bool accountCenter(){
    char hold;
	system("cls");

	if(welcoming == 0){
		welcoming += 1;
		char *txt = YELLOW "Welcome Agent" RESET;
		printWithDelay(txt);
		usleep(2000000);
		printf("Press any key to continue...");
		hold = getch(); 
	}

    char input;
    while(true){
    	system("cls");
        printf(YELLOW);
        printf("1. Login\n");
        printf("2. Register\n");
        input = getch();
        switch(input){
            case '1':
				if(login()) return true;
				else accountCenter();
                break;
            case '2':
				if(registerAcc()) return true;
				else accountCenter();
                break;
			default :
				printf(RED);
				printf("Invalid input\n");
        }
    }
}

//Menu Essential
void playMenu(){
	char input;
	system("cls");
	printf("1. Snake\n");
	printf("2. Black Jack\n");
	printf(">> ");
	input = getch();
	switch(input){
		case '1':

			break;
		case '2':

			break;
	}
}

void menu(){
    system("cls");
    splash();
    puts("");
    printf(GREEN);
    printf("Welcome agent\n");
    printf("1. Play\n");
    printf("2. Scoreboard\n");
    printf("3. Story\n");
    printf("4. How To\n");
    printf("5. Exit\n");
    printf(RESET);
	printf(">> ");
}

void swicthing(char comms){
	switch(comms){
            case '1':
                break;
            case '2':
                break;
            case '3':
                break;
            case '4':
                break;
            case '5':
                blink();
				getch();
				break;
    }
}

int main(){
    char input;
	insertData();
	// insertPrintData();
    if(accountCenter()){
		loadingAnimation();
		do{
			menu();
			input = getch();
			swicthing(input);      
		}while(input != '5');
	}  
    return 0;
}