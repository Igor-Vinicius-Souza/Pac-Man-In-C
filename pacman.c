#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define DELAY 100000
#define GHOST_COUNT 2

// Basic maze with pellets ('.')
char maze[10][20] = {
    "###################",
    "#.   #  .     #   #",
    "# ## # ###### # # #",
    "# #  .    ##     #",
    "### ### ######### #",
    "#   . #     #     #",
    "# #### ### ### ## #",
    "# #.             ##",
    "#  . ######  .    #",
    "###################"
};

// Pac-Man and Ghost positions
int pacman_x = 1, pacman_y = 1;
int ghost_x[GHOST_COUNT] = {15, 7}, ghost_y[GHOST_COUNT] = {7, 1};

// Score tracking
int score = 0;

// Function to draw the maze
void draw_maze() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 20; j++) {
            mvprintw(i, j, "%c", maze[i][j]);
        }
    }
    mvprintw(pacman_y, pacman_x, "P"); // Draw Pac-Man

    // Draw ghosts
    for (int i = 0; i < GHOST_COUNT; i++) {
        mvprintw(ghost_y[i], ghost_x[i], "G");
    }

    // Display score
    mvprintw(12, 0, "Score: %d", score);
}

// Function to move Pac-Man based on input
void move_pacman(int ch) {
    int new_x = pacman_x, new_y = pacman_y;

    switch (ch) {
        case KEY_UP:
            new_y--;
            break;
        case KEY_DOWN:
            new_y++;
            break;
        case KEY_LEFT:
            new_x--;
            break;
        case KEY_RIGHT:
            new_x++;
            break;
    }

    // Check if new position is not a wall ('#')
    if (maze[new_y][new_x] != '#') {
        // Check if Pac-Man eats a pellet ('.')
        if (maze[new_y][new_x] == '.') {
            score++;
            maze[new_y][new_x] = ' '; // Remove the pellet
        }

        pacman_x = new_x;
        pacman_y = new_y;
    }
}

// Function to move ghosts randomly
void move_ghosts() {
    for (int i = 0; i < GHOST_COUNT; i++) {
        int direction = rand() % 4;
        int new_x = ghost_x[i], new_y = ghost_y[i];

        switch (direction) {
            case 0:
                new_y--;
                break;  // Move up
            case 1:
                new_y++;
                break;  // Move down
            case 2:
                new_x--;
                break;  // Move left
            case 3:
                new_x++;
                break;  // Move right
        }

        // Ensure ghosts don't move through walls
        if (maze[new_y][new_x] != '#') {
            ghost_x[i] = new_x;
            ghost_y[i] = new_y;
        }
    }
}

// Check if Pac-Man collides with any ghost
int check_collision() {
    for (int i = 0; i < GHOST_COUNT; i++) {
        if (pacman_x == ghost_x[i] && pacman_y == ghost_y[i]) {
            return 1; // Collision detected
        }
    }
    return 0; // No collision
}

int main() {
    srand(time(NULL)); // Seed random number generator for ghosts

    initscr();               // Initialize ncurses
    noecho();                // Don't echo keypresses
    cbreak();                // Disable line buffering
    curs_set(FALSE);         // Hide the cursor
    keypad(stdscr, TRUE);    // Enable arrow keys
    nodelay(stdscr, TRUE);   // Non-blocking input

    int ch;

    while (1) {
        clear();
        draw_maze();         // Draw the maze, Pac-Man, and ghosts
        refresh();

        ch = getch();
        if (ch == 'q') break; // Press 'q' to quit

        move_pacman(ch);     // Move Pac-Man based on input
        move_ghosts();       // Move the ghosts randomly

        if (check_collision()) {
            mvprintw(14, 0, "Game Over! Final Score: %d", score);
            refresh();
            sleep(2);        // Pause to show the Game Over message
            break;           // End the game
        }

        usleep(DELAY);       // Slow down the game loop
    }

    endwin();                // End ncurses mode
    return 0;
}
