#include "../inc/maze.h"
#include "../inc/weapon_sprites.h"

/**
 * init_player - Initialize player position and angle
 * @player: Pointer to the player structure
 * @start_x: Initial X position
 * @start_y: Initial Y position
 * @start_angle: Initial angle (radians)
 */
void init_player(Player *player, float start_x, float start_y,
			float start_angle)
{
	player->x = start_x;
	player->y = start_y;
	player->angle = start_angle;
	player->dx = cos(start_angle);
	player->dy = sin(start_angle);
	player->weapon_sprite = create_weapon_sprite(200, 150);
}

/**
 * move_player - Moves the player with wall sliding
 * @player: Pointer to the player structure
 * @maze: 2D maze array
 * @forward: Forward/backward movement (-1.0 to 1.0)
 * @strafe: Strafe movement (-1.0 to 1.0)
 */
void move_player(Player *player, const int maze[15][15],
			float forward, float strafe)
{
	const float move_speed = 0.05;
	float new_x, new_y;
	float strafe_dx, strafe_dy;

	/* Handle forward/backward movement */
	if (forward != 0)
	{
		new_x = player->x + player->dx * forward * move_speed;
		new_y = player->y + player->dy * forward * move_speed;

		/* Try to slide along walls */
		if (!check_collision(maze, new_x, player->y))
			player->x = new_x;
		if (!check_collision(maze, player->x, new_y))
			player->y = new_y;
	}

	/* Handle strafing */
	if (strafe != 0)
	{
		/* Calculate perpendicular movement vector */
		strafe_dx = -player->dy;
		strafe_dy = player->dx;

		new_x = player->x + strafe_dx * strafe * move_speed;
		new_y = player->y + strafe_dy * strafe * move_speed;

		/* Try to slide along walls */
		if (!check_collision(maze, new_x, player->y))
			player->x = new_x;
		if (!check_collision(maze, player->x, new_y))
			player->y = new_y;
	}
}

/**
 * rotate_player - Rotates the player
 * @player: Pointer to the player structure
 * @angle: Angle to rotate by (in radians)
 */
static void rotate_player(Player *player, float angle)
{
	player->angle += angle;
	player->dx = cos(player->angle);
	player->dy = sin(player->angle);
}

/**
 * update_player - Updates player position and rotation based on keyboard state
 * @player: Pointer to the player structure
 * @keyboard: SDL keyboard state array
 * @maze: 2D array representing the maze layout
 */
void update_player(Player *player, const Uint8 *keyboard,
			const int maze[15][15])
{
	const float turn_speed = 0.05;
	float forward = 0.0f;
	float strafe = 0.0f;

	/* Handle continuous movement */
	if (keyboard[SDL_SCANCODE_W])
		forward += 1.0f;
	if (keyboard[SDL_SCANCODE_S])
		forward -= 1.0f;
	if (keyboard[SDL_SCANCODE_A])
		strafe -= 1.0f;
	if (keyboard[SDL_SCANCODE_D])
		strafe += 1.0f;

	/* Apply movement if any keys are pressed */
	if (forward != 0.0f || strafe != 0.0f)
		move_player(player, maze, forward, strafe);

	/* Handle rotation with arrow keys */
	if (keyboard[SDL_SCANCODE_LEFT])
		rotate_player(player, -turn_speed);
	if (keyboard[SDL_SCANCODE_RIGHT])
		rotate_player(player, turn_speed);
}

/**
 * draw_minimap_player - Draws player dot and direction line on minimap.
 * @renderer: SDL renderer.
 * @map_x: X position of the minimap.
 * @map_y: Y position of the minimap.
 * @cell_size: Size of each cell in the minimap.
 * @player: Pointer to player structure.
 */
void draw_minimap_player(SDL_Renderer *renderer, int map_x, int map_y,
			 int cell_size, const Player *player)
{
	SDL_Rect player_dot = {
		map_x + (player->x * cell_size) - 1,
		map_y + (player->y * cell_size) - 1,
		3, 3
	};

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &player_dot);

	SDL_RenderDrawLine(renderer, player_dot.x + 1, player_dot.y + 1,
			   player_dot.x + 1 + (cos(player->angle) * (cell_size - 2)),
			   player_dot.y + 1 + (sin(player->angle) * (cell_size - 2)));
}
