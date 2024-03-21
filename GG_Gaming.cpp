#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dos.h> 
#include<windows.h>
#include<conio.h>
#include<unistd.h>

#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define RESET   "\033[0m"
#define MAX_DATA 52
#define MAX_ARR 40000

void blink();
void splash();
void loadingAnimation();
void menuLoading();

//Data structure -> Implementing Hash Table Chaining
enum Game{
	SNAKE = 0,
	BLACKJACK = 1
};

struct User{
	char username[21];
	char password[21];
	long long int score;
	enum Game gameType;
	struct User* next;
	struct User* prev;
}*head[MAX_DATA], *tail[MAX_DATA], *temp, *curr;


int hashing(char username[]){
	return username[7] - 'A';
}
struct User dataPrint[MAX_ARR];

void insertUserData(char username[], char password[], long long int score, enum Game type){
	int idx = hashing(username);
	
	temp = (struct User*)malloc(sizeof(struct User));
	strcpy(temp->username, username);
	strcpy(temp->password, password);
	temp->score = score;
	temp->gameType = type;
	temp->next = temp->prev = NULL;

	if(!head[idx]) head[idx] = tail[idx] = temp;
	else {
		tail[idx]->next = temp;
		temp->prev = tail[idx];
		tail[idx] = temp;
	}
}

//Admin Data Structure function
void printScoreBoard(int page) {
    system("cls");
    int counter = 1;
    printf(GREEN);
    printf("==========================================================================\n");
    printf("|| " YELLOW "No " GREEN " |" YELLOW " Username\t\t" GREEN "| " YELLOW "Game Played \t\t" GREEN "|"
           YELLOW " Score \t" GREEN "||\n");
    printf("==========================================================================\n");
    printf(RESET);
    for (int i = page-9; i<page; i++) {
        if (dataPrint[i].gameType == 0) {
            printf("|| %-4d | %-20s | SNAKE \t\t| %-7lld \t\t||\n", counter, dataPrint[i].username, dataPrint[i].score);
            usleep(20000);
        } else {
            printf("|| %-4d | %-20s | BLACKJACK \t\t| %-7lld \t\t||\n", counter, dataPrint[i].username, dataPrint[i].score);
            usleep(20000);
        }
        counter++;
    }
    printf(GREEN);
    printf("==========================================================================\n");
    printf("Pages: [%d]\n", page/10);
    puts("");
    printf("input [ a | d ] to move pages\n");
    printf(RESET);
    printf("Press enter to exit...");

    char ipt;
    ipt = getch();
    switch (ipt) {
        case 'a':
            if (page > 0) {
                printScoreBoard(page - 10);
            } else {
                printScoreBoard(page);
            }
            break;
        case 'd':
            printScoreBoard(page + 10);
            break;
        case '\r':
            break;
    }
}



void printUser(){
	system("cls");
	for(int i=0; i<MAX_DATA; i++){
		if(head[i]){
			curr = head[i];
			while(curr){
				printf("%s\n", curr->username);
				curr = curr->next;
			}
		}
	}
	printf("Press enter to continue...\n");
	getch();
}

void deleteUser(char username[]) {
    int idx = hashing(username);

    if (!head[idx]) {
        printf(RED "User not found\n" RESET);
        return;
    }

    curr = head[idx];
    while (curr) {
        if (strcmp(curr->username, username) == 0) {
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
	int idx = hashing(username);

	if(!head[idx]){
		printf(RED);
		printf("No account found\n");
		puts("Enter to continue...");
		getch();
		return;
	} else{
		curr = head[idx];
		while(curr){
			if(strcmp(curr->username, username) == 0){
				strcpy(curr->password, password);
				break;
			}
			curr =  curr->next;
		}
	}

}

void insertData(){
    char username[21];
    char password[21];
    long long int score;
    int type;

    FILE* file = fopen("userData.csv", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    while (fscanf(file, "%20[^,],%20[^,],%lld,%d\n", username, password, &score, &type) == 4) {
        if (type == 0) {
            insertUserData(username, password, score, SNAKE);
        } else {
            insertUserData(username, password, score, BLACKJACK);
        }
    }
    fclose(file);
}

void insertPrintData(){
	int i = 0;
	FILE* file = fopen("userdata.csv", "r");
	fclose(file);
	while (fscanf(file, "%20[^,],%20[^,],%lld,%d\n", dataPrint[i].username, dataPrint[i].password, &dataPrint[i].score, &dataPrint[i].gameType) == 4){
		i++;
	}
}

bool searchingUser(char username[], char password[]){
	int idx = hashing(username);
	if(!head[idx]){
		return false;
	}
	curr = head[idx];
	while(curr){
		if(strcmp(curr->username, username) == 0 && strcmp(curr->password, password) == 0){
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
			printScoreBoard(10);
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

void passwordEnter(char pass[]){
	int i=0;
	char ps;
	while((ps = getch()) != '\r'){
			printf("*");
			pass[i++] = ps;
	}
	pass[i] = '\0';
	getchar();
}

bool userRegis(char username[]){
	system("cls");
	while(true){
		printf(BLUE);
		printf("Enter your username [1-20 characters]:");
		printf(YELLOW);
		scanf("%[^\n]", username);
		getchar();
	
		if(isAgent(username) && userLength(username)) return true;
		else {
			printf(RED);
			printf("Must between 1-20 characters\n");
			printf("String input must be 'Agent [name]'\n");
		}
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
		if(isSame(pass, passConf) && check(passConf) && check(pass) && isSpace(passConf) && isSpace(pass)) {
			return true;
		} else {
			printf(RED);
			printf("Criteria didn't met!\n");
		}
	}
	return false;
}

bool registerAcc(){
	char username[21];
	char password[21];
	char passwordConfirm[21];

	if(userRegis(username) && passRegis(password, passwordConfirm)){
		insertUser(username, password);
	}else{
		return false;
	}

	return true;
}

bool loginUser(char username[]){
		system("cls");
	while(true){
		printf(BLUE);
		printf("Enter username: ");
		printf(YELLOW);
		scanf("%[^\n]", username);
		getchar();
		if(isAdmin(username)) return true;
		if(userLength(username)){
			if(isAgent(username)){
				return true;
			} else {
				printf(RED);
				printf("String input must be 'Agent [name]'\n");
			}
		}
	}
	return false;
}

bool loginPass(char password[]){
		system("cls");
	while(true){
		printf(BLUE);
		printf("Enter yout password: ");
		printf(YELLOW);
		passwordEnter(password);
		if(isSpace(password) && adminConfirm(password)) return true;
		if(check(password) && isSpace(password)) return true;
		else {
			printf(RED);
			printf("Need to be alphanumeric & cannot contain space!\n");
		}
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
			system("cls");
			printf(RED);
			printf("Agent not found! Register it first!\n");
		}
	}
	return false;
}

bool accountCenter(){
    char hold;
	system("cls");
    printf(YELLOW);
    printf("Welcome Agent!\n");
    printf(RESET);
    usleep(2000000);
    printf("Press any key to continue...");
    hold = getch(); 

    char input;
    do{
    	system("cls");
        printf(YELLOW);
        printf("1. Login\n");
        printf("2. Register\n");
        input = getch();
        switch(input){
            case '1':
				if(login()) return true;
				else return false;
                break;
            case '2':
				if(registerAcc()) return true;
				else return false;
                break;
			default :
				printf(RED);
				printf("Invalid input\n");
        }
    }while(true);
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
	insertPrintData();
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