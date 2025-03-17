#include "../inc/maze.h"
#include "../inc/weapon_sprites.h"

/**
 * handle_events - Handles SDL events (e.g., quitting, key presses)
 * @running: Pointer to the running state of the game
 */
void handle_events(int *running)
{
	SDL_Event event;
	GameState game_state;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			*running = 0;
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_m)
			toggle_minimap(&game_state);
	}
}

/**
 * render_frame - Renders a single frame of the game
 * @renderer: SDL renderer
 * @player: Pointer to the player object
 * @textures: Pointer to the Textures structure
 * @game_state: Pointer to the GameState structure
 */
void render_frame(SDL_Renderer *renderer, Player *player,
	Textures *textures, GameState *game_state)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	update_player(player, SDL_GetKeyboardState(NULL), maze);
	cast_rays(renderer, player, maze, textures);
	draw_minimap(renderer, player, game_state);

	SDL_Rect weapon_rect = {
		(SCREEN_WIDTH / 2) - (player->weapon_sprite->w / 2),
		(SCREEN_HEIGHT - player->weapon_sprite->h),
		player->weapon_sprite->w, player->weapon_sprite->h
	};
	SDL_Texture *weapon_texture = SDL_CreateTextureFromSurface(
		renderer, player->weapon_sprite);
	SDL_RenderCopy(renderer, weapon_texture, NULL, &weapon_rect);
	SDL_DestroyTexture(weapon_texture);
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
	GameState game_state;
	int running = 1;

	if (init_sdl(&window, &renderer) != 0 || init_textures(&textures) != 0)
	{
		printf("Initialization failed\n");
		cleanup(window, renderer);
		return (1);
	}

	init_player(&player, 1.5, 1.5, 0);

	while (running)
	{
		handle_events(&running);
		render_frame(renderer, &player, &textures, &game_state);
	}

	cleanup_textures(&textures);
	cleanup(window, renderer);
	return (0);
}
