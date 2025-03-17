#include "../inc/maze.h"

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
 * draw_minimap_cell - Draws a single cell of the minimap
 * @renderer: Pointer to SDL_Renderer
 * @cell: SDL_Rect representing the cell
 * @is_wall: Whether the cell is a wall
 */
void draw_minimap_cell(SDL_Renderer *renderer, SDL_Rect cell, int is_wall)
{
	const int wall_margin = 2;

	if (is_wall)
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_Rect wall = {
			cell.x + wall_margin,
			cell.y + wall_margin,
			cell.w - (wall_margin * 2),
			cell.h - (wall_margin * 2)
		};
		SDL_RenderFillRect(renderer, &wall);
	}
	else
	{
		SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
		SDL_RenderFillRect(renderer, &cell);
	}
}

/**
 * draw_minimap - Draws a small 2D map overlay with player position
 * @renderer: Pointer to SDL_Renderer
 * @player: Pointer to player structure
 * @game_state: Pointer to the GameState structure
 */
void draw_minimap(SDL_Renderer *renderer, const Player *player,
			GameState *game_state)
{
	const int map_size = 100, map_y = 10, player_size = 3;
	const int cell_size = map_size / MAZE_ROWS;
	const int map_x = SCREEN_WIDTH - map_size - 10;
	SDL_Rect background = {map_x - 5, map_y - 5, map_size + 10, map_size + 10};
	int row, col;

	if (!game_state->show_minimap)
		return;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
	SDL_RenderFillRect(renderer, &background);

	for (row = 0; row < MAZE_ROWS; row++)
	{
		for (col = 0; col < MAZE_COLS; col++)
		{
			SDL_Rect cell = {
				map_x + (col * cell_size),
				map_y + (row * cell_size),
				cell_size, cell_size
			};
			draw_minimap_cell(renderer, cell, maze[row][col]);
		}
	}

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_Rect player_dot = {
		map_x + (player->x * cell_size) - player_size / 2,
		map_y + (player->y * cell_size) - player_size / 2,
		player_size, player_size
	};
	SDL_RenderFillRect(renderer, &player_dot);

	int line_end_x = player_dot.x + player_size / 2 +
		(cos(player->angle) * (cell_size - 2));
	int line_end_y = player_dot.y + player_size / 2 +
		(sin(player->angle) * (cell_size - 2));
	SDL_RenderDrawLine(renderer,
		player_dot.x + player_size / 2, player_dot.y + player_size / 2,
		line_end_x, line_end_y);
}

/**
 * cleanup - Destroys SDL window and renderer, then quits SDL
 * @window: Pointer to SDL_Window
 * @renderer: Pointer to SDL_Renderer
 */
void cleanup(SDL_Window *window, SDL_Renderer *renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
