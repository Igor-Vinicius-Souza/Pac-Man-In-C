# Pac-Man SDL2 Game

This project is a simple implementation of a Pac-Man-like game using SDL2 (Simple DirectMedia Layer). The game features a playable Pac-Man character and randomly moving ghosts on a tile-based map.

## Table of Contents

- [Features]()
- [Installation]()
- [Usage]()
- [Controls]()
- [License]()

## Features

- **Tile-based map:** The game uses a 28x31 grid for the game environment.
- **Pac-Man character:** Move Pac-Man around the map while avoiding ghosts.
- **Randomly moving ghosts:** Ghosts move randomly on the map, creating a challenge for the player.
- **Collision detection:** The game detects collisions between Pac-Man and ghosts.

## Installation
### Prerequisites

Before running the game, ensure you have the following installed:

- [SDL2](https://wiki.libsdl.org/SDL2/Installation) - The Simple DirectMedia Layer library.

### Build Instructions

1. ***Clone the repository:***

```bash
git clone https://github.com/Igor-Vinicius-Souza/Pac-Man-In-C.git

cd Pac-Man-In-C
```

2. **Compile the project:** Make sure you have a C compiler (like gcc) installed. Run the following command:

```bash
gcc pacman_xorg.c -o pacman -lSDL2
```
3. **Run the game:**

```bash
./pacman
```

### Usage

Upon launching the game, a window will appear displaying the map, Pac-Man, and the ghosts. Use the arrow keys to control Pac-Man's movement.

### Controls

- **Up Arrow:** Move Pac-Man up.
- **Down Arrow:** Move Pac-Man down.
- **Left Arrow:** Move Pac-Man left.
- **Right Arrow:** Move Pac-Man right.

### Game Over

If Pac-Man collides with a ghost, a message will be printed in the console indicating that the game is over. You can reset the game by restarting the application.

### License

This project is licensed under the MIT License. See the LICENSE file for more details.