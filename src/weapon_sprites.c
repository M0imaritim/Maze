#include "../inc/maze.h"

/**
 * create_weapon_sprite - Creates a simple weapon sprite
 * @width: Width of the sprite
 * @height: Height of the sprite
 *
 * Return: SDL_Surface containing the weapon sprite
 */
SDL_Surface *create_weapon_sprite(int width, int height)
{
	SDL_Surface *surface;
	SDL_Rect barrel, grip;

	surface = SDL_CreateRGBSurface(0, width, height, 32,
				    0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);

	if (!surface)
		return (NULL);

	/* Fill with transparency */
	SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, 0, 0, 0, 0));

	barrel.x = width / 2 - 4;
	barrel.y = height / 2;
	barrel.w = 8;
	barrel.h = height / 2;

	grip.x = width / 2 - 6;
	grip.y = (height * 3 / 4) + 5;
	grip.w = 12;
	grip.h = height / 4;

	/* Draw barrel in dark gray */
	SDL_FillRect(surface, &barrel,
		SDL_MapRGBA(surface->format, 100, 100, 100, 255));

	/* Draw grip in brown */
	SDL_FillRect(surface, &grip,
		SDL_MapRGBA(surface->format, 139, 69, 19, 255));

	return (surface);
}
