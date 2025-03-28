#include "../inc/maze.h"
#include "../inc/weapon_sprites.h"
#include <SDL2/SDL_image.h>
#include <time.h>
#include <math.h>

/**
 * resize_surface - Resizes an SDL surface
 * @surface: Original surface to resize
 * @width: Target width
 * @height: Target height
 * Return: New resized surface or NULL on failure
 */
SDL_Surface *resize_surface(SDL_Surface *surface, int width, int height)
{
	SDL_Surface *resized = NULL;
	SDL_Rect src_rect = {0, 0, 0, 0};
	SDL_Rect dst_rect = {0, 0, 0, 0};

	if (!surface)
		return (NULL);

	/* Create a new surface with the desired dimensions */
	resized = SDL_CreateRGBSurface(0, width, height, 32,
			0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
	if (!resized)
	{
		printf("Error creating resized surface: %s\n", SDL_GetError());
		return (NULL);
	}

	/* Set up source and destination rectangles */
	src_rect.w = surface->w;
	src_rect.h = surface->h;
	dst_rect.w = width;
	dst_rect.h = height;

	/* Set blend mode to NONE to ensure proper scaling */
	SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_NONE);

	/* Scale the surface */
	if (SDL_BlitScaled(surface, &src_rect, resized, &dst_rect) != 0)
	{
		printf("Error scaling surface: %s\n", SDL_GetError());
		SDL_FreeSurface(resized);
		return (NULL);
	}

	return (resized);
}

/**
 * load_weapon_image - Loads a weapon image from a file and resizes it
 * @filename: Path to the weapon image file
 * @width: Desired width for the resized image
 * @height: Desired height for the resized image
 * Return: SDL_Surface containing the resized loaded image or NULL on failure
 */
SDL_Surface *load_weapon_image(const char *filename, int width, int height)
{
	SDL_Surface *loaded_image = NULL;
	SDL_Surface *resized_image = NULL;

	/* Initialize SDL_Image with PNG support */
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		printf("SDL_image could not initialize! Error: %s\n", IMG_GetError());
		return (NULL);
	}

	/* Load the image from file */
	loaded_image = IMG_Load(filename);
	if (loaded_image == NULL)
	{
		printf("Unable to load image %s! Error: %s\n",
				filename, IMG_GetError());
		return (NULL);
	}

	/* Resize the image if dimensions are provided */
	if (width > 0 && height > 0)
	{
		resized_image = resize_surface(loaded_image, width, height);
		SDL_FreeSurface(loaded_image);
		return (resized_image);
	}

	return (loaded_image);
}

/**
 * create_weapon_sprite - Creates a weapon sprite surface with specified size
 * @width: Width of the sprite
 * @height: Height of the sprite
 * Return: SDL_Surface for the weapon or default if loading fails
 */
SDL_Surface *create_weapon_sprite(int width, int height)
{
	SDL_Surface *weapon_surface = NULL;
	const char *weapon_path = "./textures/weapons/gn111.png";
	SDL_Rect weapon_rect, barrel, handle;

	/* Try to load the custom weapon image with specified dimensions */
	weapon_surface = load_weapon_image(weapon_path, width, height);
	/* If loading fails, create a default colored surface */
	if (weapon_surface == NULL)
	{
		printf("Creating fallback weapon sprite\n");
		weapon_surface = SDL_CreateRGBSurface(0, width, height, 32,
				0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);

		if (weapon_surface == NULL)
		{
			printf("Failed to create surface: %s\n", SDL_GetError());
			return (NULL);
		}
		/* Set a default color for the fallback weapon */
		weapon_rect.x = weapon_rect.y = 0;
		weapon_rect.w = width;
		weapon_rect.h = height;
		SDL_FillRect(weapon_surface, &weapon_rect,
				SDL_MapRGBA(weapon_surface->format, 150, 150, 150, 200));
		/* Draw a simple gun shape */
		barrel.x = width / 2 - 15;
		barrel.y = height / 4;
		barrel.w = 30;
		barrel.h = height / 2;
		SDL_FillRect(weapon_surface, &barrel,
				SDL_MapRGBA(weapon_surface->format, 100, 100, 100, 255));

		handle.x = width / 2 - 25;
		handle.y = height / 2;
		handle.w = 50;
		handle.h = height / 3;
		SDL_FillRect(weapon_surface, &handle,
				SDL_MapRGBA(weapon_surface->format, 80, 50, 20, 255));
	}
	return (weapon_surface);
}

/**
 * cleanup_weapon_sprite - Frees memory used by weapon sprite
 * @player: Pointer to the player structure
 */
void cleanup_weapon_sprite(Player *player)
{
	if (player->weapon_sprite != NULL)
	{
		SDL_FreeSurface(player->weapon_sprite);
		player->weapon_sprite = NULL;
	}
}
