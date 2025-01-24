# Snake Game - Enhanced Edition

An upgraded version of the classic Snake game, developed in C. This version introduces new features such as special food items, dynamic speed adjustments, and an invincibility mode for an exciting and challenging gameplay experience.

## Features

### Classic Snake Gameplay
- Control the snake to collect food and grow longer, all while avoiding collisions with walls and the snake's body.

### Special Food Items
- **Normal Food (\*)**: Provides standard points (100).
- **Speed-Up Food (>/)**: Increases the snake's speed.
- **Speed-Down Food (</)**: Slows down the snake.
- **Bonus Points Food (\$)**: Provides a large score boost (500).

### Dynamic Gameplay
- The snake's speed changes dynamically based on food consumption and user input.
- Food items spawn randomly with different point values and effects on speed.

### Invincible Mode
- **Toggle Invincibility**: Press the spacebar to activate invincibility mode.
  - In invincible mode, the snake can pass through walls and itself without dying (but cannot collect food).

### Score Tracking
- The current score and snake speed are displayed in real time on the screen.

### Game Over Condition
- The game ends when the snake collides with itself or a wall unless invincible mode is enabled.

## Requirements
- A C compiler (e.g., GCC, MinGW).
- Windows OS (due to reliance on `<conio.h>` and `<windows.h>`).

## How to Run the Game

1. Clone or download the repository.
2. Compile the program using your C compiler:
   ```bash
   gcc snake_game.c -o snake_game
   ```
3. Run the compiled executable:
   ```bash
   ./snake_game
   ```

## Controls
- **W**: Move Up
- **D**: Move Right
- **S**: Move Down
- **A**: Move Left
- **Spacebar**: Toggle Invincibility Mode

## Game Elements

### Special Foods
Each food type has its unique effects on gameplay:
- **Normal Food (\*)**: 
  - Points: 100
- **Speed-Up Food (>/)**:
  - Points: 150
  - Increases the snake’s speed.
- **Speed-Down Food (</)**:
  - Points: 200
  - Decreases the snake’s speed.
- **Bonus Points Food (\$)**:
  - Points: 500
  - Provides a large score boost.

### The Snake
- The snake grows longer with each food consumed.
- Direction is indicated by:
  - `^` for Up, `>` for Right, `v` for Down, `<` for Left.

### Borders
- Represented by `+`, `|`, and `-`.
- Colliding with the border ends the game unless invincible mode is active.

### Invincible Mode
- This mode allows the snake to pass through walls and itself but prevents it from collecting food.

## Customization
You can modify the following constants in the code to adjust the game's settings:
- **cols** and **rows**: Define the size of the game board.
- **INITIAL_SPEED**: Adjust the starting speed of the snake.
- **MAX_FOODS**: Set the maximum number of food items on the board.

## License
This project is open-source and free to use. You are welcome to modify and distribute it as needed. Attribution is appreciated.

## Credits
Developed by **Mariem Ben Attia**, **Hanine Hamrouni**, and **Balsem Zouabi**.
