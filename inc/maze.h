#ifndef MAZE_H
#define MAZE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "player.h"

#define SCREEN_WIDTH 700
#define SCREEN_HEIGHT 700
#define TILE_SIZE 46
#define MAZE_ROWS 15
#define MAZE_COLS 15
#define TEXTURE_SIZE 64  /* Size of wall and floor textures */

/* Constants for raycasting */
#define FOV 60.0       /* Field of View in degrees */
#define NUM_RAYS 320   /* Number of rays to cast */
#define MAX_DEPTH 10   /* Maximum distance a ray can travel */


/**
 * struct Textures - Stores texture data for different surfaces.
 * @north_south: Pointer to pixel data for north and south-facing walls.
 * @east_west: Pointer to pixel data for east and west-facing walls.
 * @floor: Pointer to pixel data for the floor texture.
 * @width: The width of the texture.
 * @height: The height of the texture.
 */
struct Textures
{
	Uint32 *north_south;
	Uint32 *east_west;
	Uint32 *floor;
	int width;
	int height;
};
typedef struct Textures Textures;
extern const int maze[MAZE_ROWS][MAZE_COLS];
/* extern Textures textures;  Global textures */

int init_sdl(SDL_Window **window, SDL_Renderer **renderer);
int init_textures(Textures *textures);
void cleanup_textures(Textures *textures);
/**
 * struct GameState - Holds the current state of the game.
 * @show_minimap: Flag to determine if the minimap should be displayed
 *
 * This struct stores global game state variables, such as UI toggles.
 */
struct GameState
{
	int show_minimap;
};
typedef struct GameState GameState;

extern GameState game_state;

void render_frame(SDL_Renderer *renderer, Player *player, Textures *textures,
		GameState *game_state);
void handle_events(int *running);
void cast_rays(SDL_Renderer *renderer, Player *player, const int maze[15][15],
	Textures *textures);
void draw_textured_wall(SDL_Renderer *renderer, int x, int wall_height,
	float tex_x, float distance, int is_ns, Textures *textures);
void draw_floor(SDL_Renderer *renderer, int x, int wall_height,
		const Player *player, float ray_angle, Textures *textures);
void draw_minimap(SDL_Renderer *renderer, const Player *player,
		GameState *game_state);
void toggle_minimap(GameState *game_state);
void cleanup(SDL_Window *window, SDL_Renderer *renderer);

#endif
