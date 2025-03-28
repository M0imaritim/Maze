#include "../inc/maze.h"
#include "../inc/weapon_sprites.h"
#include <SDL2/SDL_image.h>
#include <math.h>

/**
 * init_weapon_system - Initialize the weapon system
 * @weapon_system: Pointer to weapon system
 * @maze: The maze array
 * Return: 1 on success, 0 on failure
 */
int init_weapon_system(WeaponSystem *weapon_system, const int maze[15][15])
{
	int i;

	/* Initialize SDL_image for loading PNG, JPG, etc. */
	int img_flags = IMG_INIT_PNG;

	if (!weapon_system)
		return (0);

	if (!(IMG_Init(img_flags) & img_flags))
	{
		printf("SDL_image could not initialize! Error: %s\n", IMG_GetError());
		return (0);
	}

	/* Initialize weapon system state */
	weapon_system->enemy_count = 0;
	weapon_system->score = 0;
	weapon_system->player_health = 100;
	weapon_system->last_shot_time = 0;

	/* Initialize bullets */
	for (i = 0; i < MAX_BULLETS; i++)
		weapon_system->bullets[i].active = 0;

	/* Initialize enemies */
	init_enemies(weapon_system, maze);

	return (1);
}

/**
 * handle_shooting - Handle player shooting
 * @weapon_system: Pointer to weapon system
 * @player: Pointer to player struct
 * @keyboard: Keyboard state
 */
void handle_shooting(WeaponSystem *weapon_system, Player *player,
		   const Uint8 *keyboard)
{
	if (keyboard[SDL_SCANCODE_SPACE])
		create_bullet(weapon_system, player);
}

/**
 * update_weapon_system - Update all weapon system elements
 * @weapon_system: Pointer to weapon system
 * @player: Pointer to player struct
 * @keyboard: SDL keyboard state
 * @maze: The maze array
 */
void update_weapon_system(WeaponSystem *weapon_system, Player *player,
			const Uint8 *keyboard, const int maze[15][15])
{
	/* Handle player shooting */
	handle_shooting(weapon_system, player, keyboard);

	/* Update bullets */
	update_bullets(weapon_system);

	/* Update enemies */
	update_enemies(weapon_system, player);

	/* Check for game over or level complete conditions */
	if (weapon_system->enemy_count <= 0)
	{
		/* All enemies defeated - level complete */
		init_enemies(weapon_system, maze);
	}

	if (weapon_system->player_health <= 0)
	{
		/* Player defeated - game over */
		weapon_system->player_health = 100;  /* Reset for demo purposes */
	}
}

/**
 * render_weapon_system - Render all weapon system elements
 * @renderer: SDL renderer
 * @player: Pointer to player struct
 * @weapon_system: Pointer to weapon system
 */
void render_weapon_system(SDL_Renderer *renderer, Player *player,
			WeaponSystem *weapon_system)
{
	SDL_Rect weapon_rect;
	SDL_Texture *weapon_texture;
	const Uint8 *keyboard = SDL_GetKeyboardState(NULL);

	/* Draw enemies in 3D view */
	draw_enemies_3d(renderer, player, weapon_system);

	/* Draw weapon */
	weapon_rect.x = (SCREEN_WIDTH / 2) - (player->weapon_sprite->w / 2);
	weapon_rect.y = (SCREEN_HEIGHT - player->weapon_sprite->h);
	weapon_rect.w = player->weapon_sprite->w;
	weapon_rect.h = player->weapon_sprite->h;

	/* Add bobbing effect when moving */
	if (keyboard[SDL_SCANCODE_W] || keyboard[SDL_SCANCODE_S] ||
		keyboard[SDL_SCANCODE_A] || keyboard[SDL_SCANCODE_D])
	{
		static float bob;

		bob += 0.2;
		weapon_rect.y += sin(bob) * 5;
	}

	/* Draw the weapon */
	weapon_texture = SDL_CreateTextureFromSurface
		(renderer, player->weapon_sprite);
	SDL_RenderCopy(renderer, weapon_texture, NULL, &weapon_rect);
	SDL_DestroyTexture(weapon_texture);

	/* Draw HUD */
	draw_hud(renderer, weapon_system);
}

/**
 * draw_hud - Draw heads-up display with health and score
 * @renderer: SDL renderer
 * @weapon_system: Pointer to weapon system
 */
void draw_hud(SDL_Renderer *renderer, WeaponSystem *weapon_system)
{
	SDL_Rect health_bg, health_fill;

	/* Draw health bar */
	health_bg.x = 20;
	health_bg.y = SCREEN_HEIGHT - 30;
	health_bg.w = 200;
	health_bg.h = 20;

	health_fill.x = 20;
	health_fill.y = SCREEN_HEIGHT - 30;
	health_fill.w = weapon_system->player_health * 2;
	health_fill.h = 20;

	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 200);
	SDL_RenderFillRect(renderer, &health_bg);

	/* Color changes with health level */
	if (weapon_system->player_health > 70)
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	else if (weapon_system->player_health > 30)
		SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	else
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

	SDL_RenderFillRect(renderer, &health_fill);
}
