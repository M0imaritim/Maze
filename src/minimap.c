#include "../inc/maze.h"

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
 * draw_minimap_background - Draws the minimap background.
 * @renderer: SDL renderer.
 * @map_x: X position of the minimap.
 * @map_y: Y position of the minimap.
 * @map_size: Size of the minimap.
 */
void draw_minimap_background(SDL_Renderer *renderer, int map_x,
int map_y, int map_size)
{
SDL_Rect background = {map_x - 5, map_y - 5, map_size + 10, map_size + 10};

SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
SDL_RenderFillRect(renderer, &background);
}

/**
 * draw_minimap_cells - Renders the maze cells on the minimap.
 * @renderer: SDL renderer.
 * @map_x: X position of the minimap.
 * @map_y: Y position of the minimap.
 * @cell_size: Size of each cell in the minimap.
 */
void draw_minimap_cells(SDL_Renderer *renderer, int map_x,
int map_y, int cell_size)
{
int row, col;

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
}

/**
 * draw_minimap - Main function to draw the minimap.
 * @renderer: SDL renderer.
 * @player: Pointer to player structure.
 * @game_state: Pointer to game state structure.
 * @weapon_system: Pointer to weapon system.
 */
void draw_minimap(SDL_Renderer *renderer, const Player *player,
GameState *game_state, WeaponSystem *weapon_system)
{
const int map_size = 100, map_y = 10, cell_size = map_size / MAZE_ROWS;
const int map_x = SCREEN_WIDTH - map_size - 10;

if (!game_state->show_minimap)
return;

draw_minimap_background(renderer, map_x, map_y, map_size);
draw_minimap_cells(renderer, map_x, map_y, cell_size);
draw_minimap_enemies(renderer, map_x, map_y, cell_size, weapon_system);
draw_minimap_player(renderer, map_x, map_y, cell_size, player);
}
