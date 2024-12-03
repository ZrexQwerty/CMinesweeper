#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define EASY_SIZE 5
#define MEDIUM_SIZE 10
#define HARD_SIZE 15
#define EASY_BOMBS 5
#define MEDIUM_BOMBS 15
#define HARD_BOMBS 30

int SIZE;
int BOMBS;

char **board; // Player's board
char **bombs; // Bombs location board
int flagsLeft; // Remaining flags

void initializeBoards() {
    board = (char **)malloc(SIZE * sizeof(char *));
    bombs = (char **)malloc(SIZE * sizeof(char *));
    for (int i = 0; i < SIZE; i++) {
        board[i] = (char *)malloc(SIZE * sizeof(char));
        bombs[i] = (char *)malloc(SIZE * sizeof(char));
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = '.'; // All tiles covered
            bombs[i][j] = ' '; // No bombs initially
        }
    }
}

void freeBoards() {
    for (int i = 0; i < SIZE; i++) {
        free(board[i]);
        free(bombs[i]);
    }
    free(board);
    free(bombs);
}

void calculateBombNumbers(int x, int y) {
    // Update numbers around bombs
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int nx = x + i, ny = y + j;
            if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE && bombs[nx][ny] != 'X') {
                if (bombs[nx][ny] == ' ') {
                    bombs[nx][ny] = '1';
                } else {
                    bombs[nx][ny]++;
                }
            }
        }
    }
}

void placeBombs() {
    srand(time(NULL));
    int placed = 0;
    while (placed < BOMBS) {
        int x = rand() % SIZE;
        int y = rand() % SIZE;
        if (bombs[x][y] != 'X') {
            bombs[x][y] = 'X';
            placed++;
            calculateBombNumbers(x, y); // Calculate numbers around bombs
        }
    }
}

void printBoard(char **board) {
    printf("   ");
    for (int i = 0; i < SIZE; i++) printf("%2d", i);
    printf("\n");

    for (int i = 0; i < SIZE; i++) {
        printf("%2d ", i);
        for (int j = 0; j < SIZE; j++) {
            printf("%2c", board[i][j]);
        }
        printf("\n");
    }
}

int openTile(int x, int y) {
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE || board[x][y] != '.') {
        return 0; // No action if the tile is already opened
    }

    if (bombs[x][y] == 'X') {
        return -1; // Bomb found, game over
    }

    board[x][y] = bombs[x][y]; // Reveal tile content

    if (bombs[x][y] == ' ') {
        // Recursively open empty tiles
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                openTile(x + i, y + j);
            }
        }
    }
    return 1; // Safe
}

int checkWin() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == '.' && bombs[i][j] != 'X') {
                return 0; // There are still unopened non-bomb tiles
            }
        }
    }
    return 1; // All non-bomb tiles are opened
}

void tutorial() {
    printf("\n--- TUTORIAL ---\n");
    printf("1. Choose an action: b (open) or f (flag).\n");
    printf("2. Open tiles to find numbers.\n");
    printf("3. Flag tiles you suspect contain bombs.\n");
    printf("4. Avoid bombs to win.\n");
    printf("5. Reveal all non-bomb tiles to win.\n\n");
}

void selectDifficulty() {
    printf("Select difficulty level (1: Easy, 2: Medium, 3: Hard): ");
    int difficulty;
    scanf("%d", &difficulty);

    if (difficulty == 1) {
        SIZE = EASY_SIZE;
        BOMBS = EASY_BOMBS;
    } else if (difficulty == 2) {
        SIZE = MEDIUM_SIZE;
        BOMBS = MEDIUM_BOMBS;
    } else {
        SIZE = HARD_SIZE;
        BOMBS = HARD_BOMBS;
    }

    flagsLeft = BOMBS;
}

int main() {
    selectDifficulty();

    char tutorialChoice;
    printf("Do you want to read the tutorial? (y/n): ");
    scanf(" %c", &tutorialChoice);
    if (tutorialChoice == 'y') {
        tutorial();
    }

    initializeBoards();
    placeBombs();

    int gameOver = 0;
    time_t startTime = time(NULL); // Start game time

    while (!gameOver) {
        printBoard(board);
        printf("\nRemaining bombs to flag: %d\n", flagsLeft);

        printf("\nEnter action (p to open, f to flag) and coordinates (x y): ");
        char action;
        int x, y;
        scanf(" %c %d %d", &action, &x, &y);

        if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
            printf("Invalid coordinates! Try again.\n");
            continue;
        }

        if (action == 'f') {
            if (board[x][y] == '.') {
                board[x][y] = 'F';
                flagsLeft--;
            } else if (board[x][y] == 'F') {
                board[x][y] = '.';
                flagsLeft++;
            }
        } else if (action == 'p') {
            int result = openTile(x, y);
            if (result == -1) {
                printf("\nBOOM! You lost.\n");
                gameOver = 1;
            } else if (checkWin()) {
                printf("\nCongratulations! You won.\n");
                gameOver = 1;
            }
        } else {
            printf("Invalid action! Choose b or f.\n");
        }
    }

    time_t endTime = time(NULL);
    printf("\nGame time: %ld seconds\n", endTime - startTime);

    // Reveal the actual board
    printf("\nActual board:\n");
    printBoard(bombs);

    freeBoards();
    return 0;
}
