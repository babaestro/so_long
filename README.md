# so_long


So_long is a 2D game project that challenges us to create a simple game using the MinilibX graphics library. The project focuses on basic game development concepts and graphical programming.

## Key Features

- 2D game with a top-down or side view
- Player movement in four directions
- Collectible items
- Exit condition
- Simple enemy (bonus part)
- Score tracking

## Technical Aspects

- Uses MinilibX for graphical rendering
- Map parsing from a .ber file
- Collision detection
- Sprite management
- Event handling for keyboard inputs
- Memory management

## Compilation

To compile the project, use the provided Makefile:

```bash
make
```

This will generate the executable `so_long`.

## Usage

Run the game with a map file:

```bash
./so_long maps/map.ber
```

## Map Format

The game map should be provided as a .ber file with the following elements:
- '1' for walls
- '0' for empty spaces
- 'P' for the player's starting position
- 'C' for collectibles
- 'E' for the exit

Example map:
```
1111111111111
10010000000C1
1000011111001
1P0011E000001
1111111111111
```

## Controls

- ↑: Move up
- ↓: Move down
- ←: Move left
- →: Move right
- ESC: Quit the game

## Skills Developed

- Basic game development concepts
- Graphics programming with MinilibX
- File parsing and map generation
- Event-driven programming
- Memory management in C
- Algorithm design for game logic

So_long provides an engaging introduction to game development and graphics programming, allowing students to apply their C programming skills in a creative and interactive project.
