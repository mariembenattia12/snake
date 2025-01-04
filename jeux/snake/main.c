#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#define cols 30
#define rows 20
#define MAX_FOODS 10
#define INITIAL_SPEED 150

char *board;
int score = 0;
int speed = INITIAL_SPEED;
int foodCount = 0;
int isGameOver = 0;

// Special food types
enum FoodType {
    NORMAL = 0,
    SPEED_UP,
    SPEED_DOWN,
    BONUS_POINTS
};

struct Food {
    int x, y;
    int consumed;
    enum FoodType type;
    int points;
};

struct Food food[MAX_FOODS];

struct SnakePart {
    int x, y;
};

struct Snake {
    int length;
    int direction;  // 0=up, 1=right, 2=down, 3=left
    int invincible;
    struct SnakePart part[256];
} snake;

void set_color(enum FoodType type) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    switch(type) {
        case NORMAL: SetConsoleTextAttribute(hConsole, 13); break;      // Red
        case SPEED_UP: SetConsoleTextAttribute(hConsole, 14); break;    // Green
        case SPEED_DOWN: SetConsoleTextAttribute(hConsole, 14); break;  // Yellow
        case BONUS_POINTS: SetConsoleTextAttribute(hConsole, 13);       // Magenta
        default: SetConsoleTextAttribute(hConsole, 15);                 // White
    }
}

// Draw blue borders
void draw_borders() {
    int x, y;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 9);  // Blue border color

    for (y = 0; y < rows; y++) {
        for (x = 0; x < cols; x++) {
            if ((x == 0 || x == cols-1) && (y == 0 || y == rows-1)) {
                board[y * cols + x] = '+';  // Corners
            } else if (x == 0 || x == cols-1) {
                board[y * cols + x] = '|';  // Vertical borders
            } else if (y == 0 || y == rows-1) {
                board[y * cols + x] = '-';  // Horizontal borders
            } else {
                board[y * cols + x] = ' ';  // Empty space
            }
        }
    }
}

// Spawn a random type of food
void spawn_food() {
    if (foodCount >= MAX_FOODS) return;

    struct Food newFood;
    newFood.x = 1 + rand() % (cols - 2);
    newFood.y = 1 + rand() % (rows - 2);
    newFood.consumed = 0;

    // Randomly choose a food type and points
    int r = rand() % 100;
    if (r < 60) {
        newFood.type = NORMAL;
        newFood.points = 100;
    } else if (r < 80) {
        newFood.type = SPEED_UP;
        newFood.points = 150;
    } else if (r < 90) {
        newFood.type = SPEED_DOWN;
        newFood.points = 200;
    } else {
        newFood.type = BONUS_POINTS;
        newFood.points = 500;
    }

    food[foodCount++] = newFood;
}

// Draw the game (borders, food, snake)
void draw_game() {
    draw_borders();

    // Draw food
    for (int i = 0; i < foodCount; i++) {
        if (!food[i].consumed) {
            char foodSymbol;
            switch(food[i].type) {
                case NORMAL: foodSymbol = '*'; break;
                case SPEED_UP: foodSymbol = '�'; break;
                case SPEED_DOWN: foodSymbol = '�'; break;
                case BONUS_POINTS: foodSymbol = '$'; break;
            }
            board[food[i].y * cols + food[i].x] = foodSymbol;
        }
    }

    // Draw snake
    for (int i = snake.length - 1; i > 0; i--) {
        board[snake.part[i].y * cols + snake.part[i].x] = 'o';  // Snake body
    }

    // Snake head direction indicator
    char headChar;
    switch(snake.direction) {
        case 0: headChar = '^'; break;
        case 1: headChar = '>'; break;
        case 2: headChar = 'v'; break;
        case 3: headChar = '<'; break;
    }
    board[snake.part[0].y * cols + snake.part[0].x] = headChar;
}

void move_snake() {
    for (int i = snake.length - 1; i > 0; i--) {
        snake.part[i] = snake.part[i - 1];
    }

    switch(snake.direction) {
        case 0: snake.part[0].y--; break;
        case 1: snake.part[0].x++; break;
        case 2: snake.part[0].y++; break;
        case 3: snake.part[0].x--; break;
    }
}

void process_input(int* movementRequested) {
    if (_kbhit()) {
        switch(_getch()) {
            case 'w': if (snake.direction != 2) { snake.direction = 0; *movementRequested = 1; } break;
            case 'd': if (snake.direction != 3) { snake.direction = 1; *movementRequested = 1; } break;
            case 's': if (snake.direction != 0) { snake.direction = 2; *movementRequested = 1; } break;
            case 'a': if (snake.direction != 1) { snake.direction = 3; *movementRequested = 1; } break;
            case ' ': snake.invincible = !snake.invincible; break;
        }
    }
}

void check_collisions() {
    // Wall collision
    if (!snake.invincible && (snake.part[0].x <= 0 || snake.part[0].x >= cols-1 ||
        snake.part[0].y <= 0 || snake.part[0].y >= rows-1)) {
        isGameOver = 1;
        return;
    }

    // Food collision
    for (int i = 0; i < foodCount; i++) {
        if (!food[i].consumed && snake.part[0].x == food[i].x &&
            snake.part[0].y == food[i].y) {
            score += food[i].points;
            food[i].consumed = 1;
            snake.length++;

            // Spawn new food after consumption
            spawn_food();
        }
    }

    // Self collision
    if (!snake.invincible) {
        for (int i = 1; i < snake.length; i++) {
            if (snake.part[0].x == snake.part[i].x &&
                snake.part[0].y == snake.part[i].y) {
                isGameOver = 1;
                return;
            }
        }
    }
}

void display_game() {
    system("cls");
    printf("Score: %d | Speed: %d | %s\n",
           score,
           INITIAL_SPEED - speed + 150,
           snake.invincible ? "INVINCIBLE MODE" : "Normal Mode");

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            char current = board[y * cols + x];
            if (current == '*' || current == '>' ||
                current == '<' || current == '$') {
                enum FoodType type;
                switch(current) {
                    case '>': type = SPEED_UP; break;
                    case '<': type = SPEED_DOWN; break;
                    case '$': type = BONUS_POINTS; break;
                    default: type = NORMAL;
                }
                set_color(type);
            } else {
                set_color(NORMAL);
            }
            printf("%c", current);
        }
        printf("\n");
    }
}

int main() {
    srand(time(NULL));
    board = malloc(cols * rows * sizeof(char));

    // Initialize snake
    snake.length = 1;
    snake.direction = 1;
    snake.invincible = 0;
    snake.part[0].x = cols / 4;
    snake.part[0].y = rows / 2;

    // Initialize 10 random foods
    for (int i = 0; i < 10; i++) spawn_food();

    int movementRequested = 0;  // Flag to indicate if movement is requested by the user

    while (!isGameOver) {
        if (movementRequested) {
            move_snake();  // Move the snake only if a key was pressed
            movementRequested = 0;  // Reset the flag
        }

        draw_game();
        display_game();
        process_input(&movementRequested);
        check_collisions();
        Sleep(speed);
    }

    // Game over, show final score
    system("cls");  // Clear the screen
    printf("Game Over! Final Score: %d\n", score);
    printf("Press any key to exit...");
    _getch();

    free(board);
    return 0;
}
