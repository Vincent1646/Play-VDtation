#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define COLS 60
#define ROWS 30

// Function to get user input without echo
char getch() {
    char c;
    system("stty raw");
    c = getchar();
    system("stty sane");
    return c;
}

int main() {
    srand(time(NULL)); // Seed for random number generation

    // Hide cursor
    printf("\e[?25l");

    int x[1000], y[1000];
    int quit = 0;
    while (!quit) {
        // Clear screen
        system("clear");

        // Render table
        printf("+");
        for (int i = 0; i < COLS; i++)
            printf("-");
        printf("+\n");

        for (int j = 0; j < ROWS; j++) {
            printf("¦");
            for (int i = 0; i < COLS; i++)
                printf("·");
            printf("¦\n");
        }

        printf("+");
        for (int i = 0; i < COLS; i++)
            printf("-");
        printf("+\n");

        // Move cursor back to top
        printf("\e[%iA", ROWS + 2);

        int head = 0, tail = 0;
        x[head] = COLS / 2;
        y[head] = ROWS / 2;
        int gameover = 0;
        int xdir = 1, ydir = 0;
        int applex = -1, appley;

        while (!quit && !gameover) {
            if (applex < 0) {
                // Create new apple
                applex = rand() % COLS;
                appley = rand() % ROWS;

                for (int i = tail; i != head; i = (i + 1) % 1000)
                    if (x[i] == applex && y[i] == appley)
                        applex = -1;

                if (applex >= 0) {
                    // Draw apple
                    printf("\e[%iB\e[%iC?", appley + 1, applex + 1);
                    printf("\e[%iF", appley + 1);
                }
            }

            // Clear snake tail
            printf("\e[%iB\e[%iC·", y[tail] + 1, x[tail] + 1);
            printf("\e[%iF", y[tail] + 1);

            if (x[head] == applex && y[head] == appley) {
                applex = -1;
                printf("\a"); // Bell
            } else
                tail = (tail + 1) % 1000;

            int newhead = (head + 1) % 1000;
            x[newhead] = (x[head] + xdir + COLS) % COLS;
            y[newhead] = (y[head] + ydir + ROWS) % ROWS;
            head = newhead;

            for (int i = tail; i != head; i = (i + 1) % 1000)
                if (x[i] == x[head] && y[i] == y[head])
                    gameover = 1;

            // Draw head
            printf("\e[%iB\e[%iC¦", y[head] + 1, x[head] + 1);
            printf("\e[%iF", y[head] + 1);
            fflush(stdout);

            usleep(5 * 1000000 / 60);

            // Read keyboard
            char ch = getch();
            if (ch == 27 || ch == 'q') {
                quit = 1;
            } else if (ch == 'h' && xdir != 1) {
                xdir = -1;
                ydir = 0;
            } else if (ch == 'l' && xdir != -1) {
                xdir = 1;
                ydir = 0;
            } else if (ch == 'j' && ydir != -1) {
                xdir = 0;
                ydir = 1;
            } else if (ch == 'k' && ydir != 1) {
                xdir = 0;
                ydir = -1;
            }
        }

        if (!quit) {
            // Show game over
            printf("\e[%iB\e[%iC Game Over! ", ROWS / 2, COLS / 2 - 5);
            printf("\e[%iF", ROWS / 2);
            fflush(stdout);
            getchar();
        }
    }

    // Show cursor
    printf("\e[?25h");

    return 0;
}

