#include "../inc/maze.h"
#include "../inc/weapon_sprites.h" /* Include for WeaponSystem */

/* Define the Maze Grid */
const int maze[MAZE_ROWS][MAZE_COLS] = {
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 3, 0, 1, 0, 1},
{1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1},
{1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1},
{1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1},
{1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
{1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1},
{1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
{1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1},
{1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1},
{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

/**
 * init_sdl - Initializes SDL and creates window and renderer
 * @window: Pointer to SDL_Window
 * @renderer: Pointer to SDL_Renderer
 * Return: 0 on success, 1 on failure
 */
int init_sdl(SDL_Window **window, SDL_Renderer **renderer)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("SDL Initialization failed: %s\n", SDL_GetError());
		return (1);
	}
	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		printf("IMG_Init failed: %s\n", IMG_GetError());
		SDL_Quit();
		return (1);
	}

	*window = SDL_CreateWindow("Maze Game", SDL_WINDOWPOS_CENTERED,
							SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);

	if (!*window || !*renderer)
	{
		printf("Window/Renderer creation failed: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}

	return (0);
}

/**
 * toggle_minimap - Toggle minimap visibility
 * @game_state: Pointer to the GameState structure
 */
void toggle_minimap(GameState *game_state)
{
	game_state->show_minimap = !game_state->show_minimap;
}


/**
 * cleanup - Frees resources and quits SDL
 * @window: Pointer to SDL_Window
 * @renderer: Pointer to SDL_Renderer
 */
void cleanup(SDL_Window *window, SDL_Renderer *renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}
