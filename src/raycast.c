#include "../inc/maze.h"

/**
 * get_texture_pixel - Get a pixel from a texture
 * @texture: Texture pixel data
 * @x: X coordinate in texture
 * @y: Y coordinate in texture
 * Return: Pixel color value
 */
static Uint32 get_texture_pixel(Uint32 *texture, int x, int y)
{
	return (texture[(y * TEXTURE_SIZE) + x]);
}

/**
 * draw_textured_wall - Draws a textured wall column
 * @renderer: SDL renderer
 * @x: Screen X position
 * @wall_height: Height of wall
 * @tex_x: X position in texture
 * @distance: Distance to wall
 * @is_ns: 1 if north/south wall, 0 if east/west
 * @textures: Pointer to the Textures structure to be initialized
 */
void draw_textured_wall(SDL_Renderer *renderer, int x, int wall_height,
				float tex_x, float distance, int is_ns, Textures *textures)
{
	Uint32 *texture;
	int tex_x_int, tex_y;
	float shade;
	Uint32 pixel;
	Uint8 r, g, b;
	int y;

	texture = is_ns ? (*textures).north_south : (*textures).east_west;
	tex_x_int = (int)(tex_x * TEXTURE_SIZE) % TEXTURE_SIZE;

	/* Scale color based on distance */
	shade = 1.0 - (distance * 0.1);
	if (shade < 0.3)
		shade = 0.3;

	/* Draw the wall column pixel by pixel */
	for (y = 0; y < wall_height; y++)
	{
		/* Calculate texture Y coordinate */
		tex_y = y * TEXTURE_SIZE / wall_height;

		/* Get pixel color from texture */
		pixel = get_texture_pixel(texture, tex_x_int, tex_y);
		r = (pixel >> 16) & 0xFF;
		g = (pixel >> 8) & 0xFF;
		b = pixel & 0xFF;

		/* Apply distance shading */
		r = (Uint8)(r * shade);
		g = (Uint8)(g * shade);
		b = (Uint8)(b * shade);

		/* Draw the pixel */
		SDL_SetRenderDrawColor(renderer, r, g, b, 255);
		SDL_RenderDrawPoint(renderer,
			x, (SCREEN_HEIGHT - wall_height) / 2 + y);
	}
}

/**
 * draw_floor - Draws a textured floor and ceiling
 * @renderer: SDL renderer
 * @x: Screen X position
 * @wall_height: Height of wall at this column
 * @player: Player structure
 * @ray_angle: Angle of current ray
 * @textures: Pointer to the Textures structure to be initialized
 */
void draw_floor(SDL_Renderer *renderer, int x, int wall_height,
			const Player *player, float ray_angle, Textures *textures)
{
	int wall_bottom = (SCREEN_HEIGHT + wall_height) / 2;
	float distance, shade, world_x, world_y;
	int tex_x, tex_y, y;
	Uint32 pixel;
	Uint8 r, g, b;

	for (y = wall_bottom; y < SCREEN_HEIGHT; y++)
	{
		distance = (float)(SCREEN_HEIGHT) / (2.0f * y - SCREEN_HEIGHT);
		distance = fabs(distance);

		world_x = player->x + cos(ray_angle) * distance;
		world_y = player->y + sin(ray_angle) * distance;

		tex_x = (int)(world_x * TEXTURE_SIZE) & (TEXTURE_SIZE - 1);
		tex_y = (int)(world_y * TEXTURE_SIZE) & (TEXTURE_SIZE - 1);

		pixel = get_texture_pixel((*textures).floor, tex_x, tex_y);
		r = (pixel >> 16) & 0xFF;
		g = (pixel >> 8) & 0xFF;
		b = pixel & 0xFF;

		shade = 1.0f - (distance * 0.1f);
		if (shade < 0.3f)
			shade = 0.3f;

		r = (Uint8)(r * shade);
		g = (Uint8)(g * shade);
		b = (Uint8)(b * shade);
		SDL_SetRenderDrawColor(renderer, r, g, b, 255);
		SDL_RenderDrawPoint(renderer, x, y);
		SDL_SetRenderDrawColor(renderer, r / 2, g / 2, b / 2, 255);
		SDL_RenderDrawPoint(renderer, x, SCREEN_HEIGHT - y);
	}
}

/**
 * is_north_south_wall - Determines if wall faces north/south
 * @ray_angle: The angle of the ray that hit the wall
 * Return: 1 if north/south wall, 0 if east/west wall
 */
static int is_north_south_wall(float ray_angle)
{
	float abs_cos;

	/* Normalize angle to 0-2π range */
	ray_angle = fmod(ray_angle, 2 * M_PI);
	if (ray_angle < 0)
		ray_angle += 2 * M_PI;

	/* Calculate absolute cosine of the angle */
	abs_cos = fabs(cos(ray_angle));

	/* If cosine is larger, ray is more horizontal (hits N/S wall) */
	return (abs_cos > fabs(sin(ray_angle)));
}

/**
 * cast_rays - Cast rays and render the 3D view
 * @renderer: SDL renderer to draw on
 * @player: Player structure containing position and angle
 * @maze: 2D array representing the maze layout
 * @textures: Pointer to the Textures structure to be initialized
 */
void cast_rays(SDL_Renderer *renderer, Player *player, const int maze[15][15],
			Textures *textures)
{
	float ray_angle, delta_x, delta_y, distance, tex_x, ray_x, ray_y;
	int i, x, wall_height, hit_wall;

	ray_angle = player->angle - (FOV / 2) * (M_PI / 180.0);
	for (i = 0; i < NUM_RAYS; i++)
	{
		ray_x = player->x;
		ray_y = player->y;
		delta_x = cos(ray_angle) * 0.05;
		delta_y = sin(ray_angle) * 0.05;
		distance = hit_wall = tex_x = 0;
		while (distance < MAX_DEPTH)
		{
			ray_x += delta_x;
			ray_y += delta_y;
			distance += 0.05;

			if (maze[(int)ray_y][(int)ray_x] == 1)
			{
				hit_wall = 1;
				if (is_north_south_wall(ray_angle))
					tex_x = ray_x - (int)ray_x;
				else
					tex_x = ray_y - (int)ray_y;
				break;
			}
		}

		x = i * (SCREEN_WIDTH / NUM_RAYS);
		wall_height = 0;
		if (hit_wall)
		{
			wall_height = (int)(SCREEN_HEIGHT / distance);
			wall_height = (int)(wall_height * 0.8);
draw_textured_wall(renderer, x, wall_height,
				tex_x, distance, is_north_south_wall(ray_angle), textures);
		}
		draw_floor(renderer, x, wall_height, player, ray_angle, textures);
		ray_angle += (FOV * (M_PI / 180.0)) / NUM_RAYS;
	}
}
