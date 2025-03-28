#include "../inc/maze.h"
#include "../inc/weapon_sprites.h"

/**
 * handle_events - Handles SDL events (e.g., quitting, key presses)
 * @running: Pointer to the running state of the game
 * @game_state: Pointer to the GameState structure
 */
void handle_events(int *running, GameState *game_state)
{
SDL_Event event;

while (SDL_PollEvent(&event))
	{
	if (event.type == SDL_QUIT)
		*running = 0;
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_m)
		toggle_minimap(game_state);
	}
}

/**
 * render_frame - Renders a single frame of the game
 * @renderer: SDL renderer
 * @player: Pointer to the player object
 * @textures: Pointer to the Textures structure
 * @game_state: Pointer to the GameState structure
 * @weapon_system: Pointer to the WeaponSystem structure
 */
void render_frame(SDL_Renderer *renderer, Player *player,
Textures *textures, GameState *game_state, WeaponSystem *weapon_system)
{
const Uint8 *keyboard = SDL_GetKeyboardState(NULL);

SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
SDL_RenderClear(renderer);

update_player(player, keyboard, maze);
update_weapon_system(weapon_system, player, keyboard, maze);

cast_rays(renderer, player, maze, textures);

/* Render weapon system elements */
render_weapon_system(renderer, player, weapon_system);

/* Draw minimap with player and entities */
draw_minimap(renderer, player, game_state, weapon_system);
SDL_RenderPresent(renderer);
}

/**
 * main - Entry point of the Maze Game
 * Return: 0 on success, 1 on failure
 */
int main(void)
{
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
Player player;
Textures textures;
GameState game_state = {0};
WeaponSystem weapon_system = {0};
int running = 1;
SDL_Surface *resized = NULL;

if (init_sdl(&window, &renderer) != 0 || init_textures(&textures) != 0)
{
	printf("Initialization failed\n");
	cleanup(window, renderer);
	return (1);
}

init_player(&player, 1.5, 1.5, 0);
if (player.weapon_sprite->w > 200 || player.weapon_sprite->h > 200)
{
	resized = resize_surface(player.weapon_sprite, 200, 200);
	if (resized)
	{
		SDL_FreeSurface(player.weapon_sprite);
		player.weapon_sprite = resized;
	}
}

while (running)
{
	handle_events(&running, &game_state);
	render_frame(renderer, &player, &textures, &game_state, &weapon_system);

	SDL_Delay(16);
}

cleanup_weapon_sprite(&player);
cleanup_textures(&textures);
cleanup(window, renderer);
return (0);
}
