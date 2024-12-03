# Minesweeper Game

## Overview

This is a simple console-based implementation of the classic Minesweeper game. The game allows players to select different difficulty levels and provides functionalities such as flagging suspected bomb locations and timing the gameplay.

## Features

- **Dynamic Board Sizes**: Board size and the number of bombs adjust based on the selected difficulty level.
  - Easy: 5x5 board with 5 bombs
  - Medium: 10x10 board with 15 bombs
  - Hard: 15x15 board with 30 bombs
- **Flagging System**: Players can mark tiles as suspected bomb locations.
- **Game Timer**: The game records and displays the time taken to complete.
- **Tutorial Mode**: Provides instructions for new players.
- **Win and Lose Conditions**: The game ends with a win if all non-bomb tiles are revealed, or with a loss if a bomb is uncovered.

## How to Play

1. Start the game and choose a difficulty level.
2. Optionally, read the tutorial for instructions.
3. Use the following actions during gameplay:
   - `b x y`: Open a tile at position `(x, y)`.
   - `f x y`: Flag a tile at position `(x, y)` as a suspected bomb.
4. The objective is to open all non-bomb tiles without triggering a bomb.

## Build and Run

### Prerequisites

- A C compiler (e.g., GCC)
- Make sure the development environment supports standard I/O

### Compilation

To compile the game, use the following command:

```bash
gcc -o minesweeper CMinesweeper.c
```

### Execution

Run the compiled game with:

```bash
./minesweeper
```

## File Structure

- `CMinesweeper.c`: Main source code for the Minesweeper game.
- `README.md`: Documentation for the project.

## Example Gameplay

```
Select difficulty level (1: Easy, 2: Medium, 3: Hard): 2
Do you want to read the tutorial? (y/n): y
--- TUTORIAL ---
1. Choose an action: b (open) or f (flag).
2. Open tiles to find numbers.
3. Flag tiles you suspect contain bombs.
4. Avoid bombs to win.
5. Reveal all non-bomb tiles to win.

   0 1 2 3 4 5 6 7 8 9
 0 . . . . . . . . . .
 1 . . . . . . . . . .
 2 . . . . . . . . . .
...
Remaining bombs to flag: 15
Enter action (b to open, f to flag) and coordinates (x y): b 0 0
```

## Additional Notes

### Strategies
- Always start by opening tiles in the corners or edges to reveal large areas.
- Use flags wisely; only flag tiles when you are certain of a bomb's location.
- Look for patterns among the numbers to deduce bomb positions.

### Debugging
If you encounter issues while running the game:
- Verify that your compiler supports ANSI C.
- Use debugging tools such as `gdb` to trace any runtime errors.
- Ensure the game files are in the correct directory and accessible for compilation.

## License

This project is licensed under the MIT License. See `LICENSE` for more details.

## Contribution

Feel free to submit issues and pull requests. Contributions are welcome!

When contributing, please adhere to the following guidelines:
1. Provide clear descriptions of changes.
2. Test your code to ensure it does not break existing functionality.
3. Format your code consistently with the existing style.

Happy Coding!
