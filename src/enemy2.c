#include "../inc/maze.h"
#include "../inc/weapon_sprites.h"

/**
 * check_collision - Checks if a position collides with a wall
 * @maze: 2D maze array
 * @x: X position to check
 * @y: Y position to check
 * Return: 1 if collision, 0 if no collision
 */
int check_collision(const int maze[15][15], float x, float y)
{
	const float buffer = 0.08; /* Buffer for wall collision */

	return (maze[(int)(y + buffer)][(int)(x + buffer)] ||
		maze[(int)(y - buffer)][(int)(x - buffer)] ||
		maze[(int)(y + buffer)][(int)(x - buffer)] ||
		maze[(int)(y - buffer)][(int)(x + buffer)]);
}


/**
 * has_line_of_sight - Check if there's clear line of sight betwn 2 points
 * @start_x: Starting X position
 * @start_y: Starting Y position
 * @end_x: Ending X position
 * @end_y: Ending Y position
 * Return: 1 if clear LOS, 0 if blocked by a wall
 */
int has_line_of_sight(float start_x, float start_y, float end_x, float end_y)
{
float dx = end_x - start_x;
float dy = end_y - start_y;
/* Number of steps to check */
float steps = fabsf(dx) > fabsf(dy) ? fabsf(dx) : fabsf(dy);
float x_increment = dx / (steps > 0 ? steps : 1);
float y_increment = dy / (steps > 0 ? steps : 1);
float x = start_x;
float y = start_y;

for (int i = 0; i <= (int)steps; i++)
{
	if (check_collision(maze, x, y))
		return (0); /* Wall detected, no LOS */
	x += x_increment;
	y += y_increment;
}
return (1); /* Clear LOS */
}

/**
 * draw_minimap_enemies - Draws enemy dots on the minimap.
 * @renderer: SDL renderer.
 * @map_x: X position of the minimap.
 * @map_y: Y position of the minimap.
 * @cell_size: Size of each cell in the minimap.
 * @weapon_system: Pointer to weapon system.
 */
void draw_minimap_enemies(SDL_Renderer *renderer, int map_x, int map_y,
	int cell_size, WeaponSystem *weapon_system)
{
	int i;

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

	for (i = 0; i < MAX_ENEMIES; i++)
	{
		if (weapon_system->enemies[i].alive)
		{
			SDL_Rect enemy_dot = {
				map_x + (weapon_system->enemies[i].x * cell_size) - 1,
				map_y + (weapon_system->enemies[i].y * cell_size) - 1,
				3, 3
			};
			SDL_RenderFillRect(renderer, &enemy_dot);
		}
	}
}
