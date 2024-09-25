#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define TILE_SIZE 24
#define SCREEN_WIDTH 28 * TILE_SIZE
#define SCREEN_HEIGHT 31 * TILE_SIZE

const int MAP_WIDTH = 28;
const int MAP_HEIGHT = 31;

const char map[31][28] = {
    "############################",
    "#............##............#",
    "#.####.#####.##.#####.####.#",
    "#*####.#####.##.#####.####*#",
    "#.####.#####.##.#####.####.#",
    "#..........................#",
    "#.####.##.########.##.####.#",
    "#.####.##.########.##.####.#",
    "#......##....##....##......#",
    "######.##### ## #####.######",
    "######.##### ## #####.######",
    "######.##          ##.######",
    "######.## ######## ##.######",
    "######.## ######## ##.######",
    "#......  ########    ......#",  // Adjusted this row to be 28 characters
    "######.## ######## ##.######",
    "######.## ######## ##.######",
    "######.##          ##.######",
    "######.## ######## ##.######",
    "######.## ######## ##.######",
    "#............##............#",
    "#.####.#####.##.#####.####.#",
    "#.####.#####.##.#####.####.#",
    "#*..##................##..*#",
    "###.##.##.########.##.##.###",
    "###.##.##.########.##.##.###",
    "#......##....##....##......#",
    "#.##########.##.##########.#",
    "#.##########.##.##########.#",
    "#..........................#",
    "############################"
};

typedef struct {
    int x, y;       // Position of Pac-Man or Ghost on the map
    int direction;  // Movement direction
} Entity;

Entity pacman;
Entity ghosts[4];

void initializePacman() {
    pacman.x = 13;
    pacman.y = 23;  // Starting position for Pac-Man
}

void initializeGhosts() {
    ghosts[0] = (Entity){13, 14, 0}; // Ghost 1
    ghosts[1] = (Entity){14, 14, 1}; // Ghost 2
    ghosts[2] = (Entity){13, 15, 2}; // Ghost 3
    ghosts[3] = (Entity){14, 15, 3}; // Ghost 4
}

void moveEntity(Entity* entity, int direction) {
    switch (direction) {
        case 0: // Up
            if (map[entity->y - 1][entity->x] != '#') {
                entity->y--;
            }
            break;
        case 1: // Down
            if (map[entity->y + 1][entity->x] != '#') {
                entity->y++;
            }
            break;
        case 2: // Left
            if (map[entity->y][entity->x - 1] != '#') {
                entity->x--;
            }
            break;
        case 3: // Right
            if (map[entity->y][entity->x + 1] != '#') {
                entity->x++;
            }
            break;
    }
}

void updateGhosts() {
    for (int i = 0; i < 4; i++) {
        int randomDirection = rand() % 4; // Random movement
        moveEntity(&ghosts[i], randomDirection);
    }
}

void checkCollisionWithGhosts() {
    for (int i = 0; i < 4; i++) {
        if (pacman.x == ghosts[i].x && pacman.y == ghosts[i].y) {
            printf("Pac-Man caught by ghost! Game Over!\n");
            // You can implement game over logic here, like resetting the game
        }
    }
}

void renderMap(SDL_Renderer* renderer) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            SDL_Rect tileRect = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
            if (map[y][x] == '#') {
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);  // Blue walls
            } else if (map[y][x] == '*') {
                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);  // Yellow dots
            } else {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Empty spaces
            }
            SDL_RenderFillRect(renderer, &tileRect);
        }
    }
}

void renderPacman(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);  // Yellow Pac-Man
    SDL_Rect pacmanRect = { pacman.x * TILE_SIZE, pacman.y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
    SDL_RenderFillRect(renderer, &pacmanRect);
}

void renderGhosts(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Red ghosts
    for (int i = 0; i < 4; i++) {
        SDL_Rect ghostRect = { ghosts[i].x * TILE_SIZE, ghosts[i].y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
        SDL_RenderFillRect(renderer, &ghostRect);
    }
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Pac-Man Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    initializePacman();
    initializeGhosts();

    SDL_Event e;
    int quit = 0;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP: moveEntity(&pacman, 0); break;
                    case SDLK_DOWN: moveEntity(&pacman, 1); break;
                    case SDLK_LEFT: moveEntity(&pacman, 2); break;
                    case SDLK_RIGHT: moveEntity(&pacman, 3); break;
                }
            }
        }

        // Update game state
        updateGhosts();
        checkCollisionWithGhosts();

        // Render everything
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        renderMap(renderer);
        renderPacman(renderer);
        renderGhosts(renderer);

        SDL_RenderPresent(renderer);

        SDL_Delay(100); // Slow down the game loop
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
