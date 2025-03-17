#include "../inc/maze.h"

/**
 * load_texture - Load a texture from a PNG file
 * @path: Path to the PNG file
 * Return: Uint32 pointer to pixel data on success, NULL on failure
 */
static Uint32 *load_texture(const char *path)
{
	SDL_Surface *surface = IMG_Load(path);
	Uint32 *pixels;

	if (!surface)
		return (NULL);

	/* Convert surface to RGBA format */
	SDL_Surface *optimized = SDL_ConvertSurfaceFormat(surface,
			SDL_PIXELFORMAT_RGBA8888, 0);
	SDL_FreeSurface(surface);

	if (!optimized)
		return (NULL);

	/* Allocate memory for pixel data */
	pixels = malloc(TEXTURE_SIZE * TEXTURE_SIZE * sizeof(Uint32));
	if (!pixels)
	{
		SDL_FreeSurface(optimized);
		return (NULL);
	}

	/* Copy pixel data */
	SDL_LockSurface(optimized);
	Uint32 *src = (Uint32 *)optimized->pixels;

	for (int i = 0; i < TEXTURE_SIZE * TEXTURE_SIZE; i++)
	{
		Uint8 r, g, b, a;

		SDL_GetRGBA(src[i], optimized->format, &r, &g, &b, &a);
		pixels[i] = (a << 24) | (r << 16) | (g << 8) | b;
	}
	SDL_UnlockSurface(optimized);
	SDL_FreeSurface(optimized);

	return (pixels);
}

/**
 * init_textures - Initialize wall and floor textures
 * @textures: Pointer to the Textures structure to be initialized
 * Return: 0 on success, -1 on failure
 */
int init_textures(Textures *textures)
{
	/* Initialize SDL_image */
	int flags = IMG_Init(IMG_INIT_PNG);

	if (!(flags & IMG_INIT_PNG))
	{
		printf("SDL_image initialization failed: %s\n", IMG_GetError());
		return (-1);
	}

	/* Set texture dimensions */
	(*textures).width = TEXTURE_SIZE;
	(*textures).height = TEXTURE_SIZE;

	/* Load wall textures */
	(*textures).north_south = load_texture("textures/greystone.png");
	(*textures).east_west = load_texture("textures/mossy.png");
	(*textures).floor = load_texture("textures/wood.png");

	if (!(*textures).north_south || !(*textures).east_west || !(*textures).floor)
	{
		IMG_Quit();
		return (-1);
	}

	return (0);
}

/**
 * cleanup_textures - Free texture resources
 * @textures: Pointer to the Textures structure to be initialized
 */
void cleanup_textures(Textures *textures)
{
	free((*textures).north_south);
	free((*textures).east_west);
	free((*textures).floor);
	IMG_Quit();
}
