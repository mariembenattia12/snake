﻿# snake
This project is an enhanced version of the classic Snake game, developed in C. It introduces special food items, dynamic speed adjustments, and an invincible mode to add new levels of excitement and challenge to the gameplay.

Features
Classic Snake Gameplay:

Control the snake to collect food and grow longer while avoiding collisions.
Special Food Items:

Normal Food (*): Provides standard points.
Speed-Up Food (>/ ): Increases snake speed.
Speed-Down Food (</ ): Decreases snake speed.
Bonus Points Food ($): Provides a large score boost.
Dynamic Gameplay:

Speed changes based on food consumption and user input.
Randomly spawned food items with varied point values.
Invincible Mode:

Toggle invincibility using the spacebar (Space key). In this mode, the snake can pass through walls and itself without dying.
Score Tracking:

Displays the current score and snake speed dynamically.
Game Over Condition:

The game ends if the snake collides with itself or a wall (unless invincible).
Requirements
A C compiler (e.g., GCC, MinGW).
A Windows operating system (due to reliance on <conio.h> and <windows.h>).
How to Run the Game
Clone or download the repository.
Compile the program using a C compiler. For example:
bash
Copier le code
gcc snake_game.c -o snake_game
Run the compiled executable:
bash
Copier le code
./snake_game
Controls
W: Move up.
D: Move right.
S: Move down.
A: Move left.
Spacebar: Toggle invincible mode.
Game Elements
Special Foods
Each type of food has distinct effects on the game:

Normal Food (*):
Points: 100
Speed-Up Food (>/ ):
Points: 150
Increases game speed.
Speed-Down Food (</ ):
Points: 200
Decreases game speed.
Bonus Points Food ($):
Points: 500
Snake
The snake grows longer with each food consumed.
The direction of movement is displayed using:
^ (up), > (right), v (down), < (left).
Gameplay Notes
Borders: Represented by +, |, and -. Colliding with borders ends the game unless invincible mode is active.
Invincible Mode: Allows passing through walls and the snake's body but disables the ability to collect food.
Customization
You can modify game settings by adjusting the following constants in the code:

cols and rows: Control the size of the game board.
INITIAL_SPEED: Adjust the initial speed of the game.
MAX_FOODS: Define the maximum number of food items on the board.
License
This project is open-source and free to use. You may modify and distribute it as needed. Attribution is appreciated.

Credits
Developed by [Mariem ben attia and hanine hamrouni and balsem zouabi].


