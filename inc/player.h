#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <math.h>

/**
 * struct Player - Structure for player data
 * @x: X position in the maze
 * @y: Y position in the maze
 * @angle: Direction player is facing (radians)
 * @dx: X component of direction vector
 * @dy: Y component of direction vector
 * @weapon_sprite: To hold the weapon sprite
 */
struct Player
{
	float x, y;
	float angle;
	float dx, dy;
	SDL_Surface *weapon_sprite; /* To hold the weapon sprite */
};
typedef struct Player Player;

/* Function prototypes */
void init_player(Player *player, float start_x,
	float start_y, float start_angle);
void update_player(Player *player, const Uint8 *keyboard,
		const int maze[15][15]);
void move_player(Player *player, const int maze[15][15],
		float forward, float strafe);


#endif /* PLAYER_H */
