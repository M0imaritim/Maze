#include "../inc/maze.h"
#include "../inc/weapon_sprites.h"

/* Enemy texture pointers */
static SDL_Texture *enemy_texture1;
static SDL_Texture *enemy_texture2;
static int animation_frame;

/**
 * load_enemy_textures - Load enemy textures into memory
 * @renderer: SDL renderer
 */
void load_enemy_textures(SDL_Renderer *renderer)
{
SDL_Surface *surface;

/* Load enemy images*/
surface = IMG_Load("./textures/Enemies/enm222.png");
if (!surface)
	printf("Error loading enm222.png: %s\n", IMG_GetError());

/*Create an enemy surface*/
enemy_texture1 = SDL_CreateTextureFromSurface(renderer, surface);
SDL_FreeSurface(surface);

surface = IMG_Load("./textures/Enemies/enm33.png");
if (!surface)
	printf("Error loading enm33.png: %s\n", IMG_GetError());

enemy_texture2 = SDL_CreateTextureFromSurface(renderer, surface);
SDL_FreeSurface(surface);
}

/**
 * init_enemies - Initialize enemies in the maze
 * @weapon_system: Pointer to weapon system
 * @maze: The maze array
 */
void init_enemies(WeaponSystem *weapon_system, const int maze[15][15])
{
int i, x, y;

srand(time(NULL));
weapon_system->enemy_count = 0;

for (i = 0; i < MAX_ENEMIES; i++)
{
	do {
		x = rand() % 15;
		y = rand() % 15;
	} while (maze[y][x] != 0 || (x == 1 && y == 1));

	weapon_system->enemies[i].x = (float)x + 0.5f;
	weapon_system->enemies[i].y = (float)y + 0.5f;
	weapon_system->enemies[i].alive = 1;
	weapon_system->enemies[i].health = 100.0f;
	weapon_system->enemies[i].speed = 0.03f + ((float)rand() / RAND_MAX) * 0.02f;
	weapon_system->enemies[i].last_attack = 0;
	weapon_system->enemies[i].direction = 0;

	weapon_system->enemy_count++;
}
}

/**
 * update_enemies - Move enemies towards player with smoother simulation
 * @weapon_system: Pointer to weapon system
 * @player: Pointer to player struct
 */
void update_enemies(WeaponSystem *weapon_system, Player *player)
{
int i;
Uint32 current_time = SDL_GetTicks();
animation_frame = (current_time / 200) % 2;

for (i = 0; i < MAX_ENEMIES; i++)
{
	if (weapon_system->enemies[i].alive)
	{
		float dx = player->x - weapon_system->enemies[i].x;
		float dy = player->y - weapon_system->enemies[i].y;
		float length = sqrtf(dx * dx + dy * dy);
		float new_x, new_y;

		if (length > 0)
		{
			dx /= length;
			dy /= length;
			weapon_system->enemies[i].direction = atan2f(dy, dx);
		}
		float speed = weapon_system->enemies[i].speed;

		new_x = weapon_system->enemies[i].x + dx * speed;
		new_y = weapon_system->enemies[i].y + dy * speed;
		if (!check_collision(maze, new_x, weapon_system->enemies[i].y))
			weapon_system->enemies[i].x = new_x;
		if (!check_collision(maze, weapon_system->enemies[i].x, new_y))
			weapon_system->enemies[i].y = new_y;

		if (length < 1.5f && current_time -
				weapon_system->enemies[i].last_attack > 1000)
		{
			weapon_system->player_health -= 10;
			weapon_system->enemies[i].last_attack = current_time;
		}
	}
}
}

/**
 * draw_enemies_3d - Draw enemies in 3D view with textures, only if visible
 * @renderer: SDL renderer
 * @player: Pointer to player struct
 * @weapon_system: Pointer to weapon system
*/
void draw_enemies_3d(SDL_Renderer *renderer, Player *player,
	WeaponSystem *weapon_system)
{
	int i;
	float player_angle = player->angle;
	float fov = M_PI / 3; /* 60-degree FOV */
	SDL_Rect enemy_rect;

	if (!enemy_texture1 || !enemy_texture2)
		load_enemy_textures(renderer);
	for (i = 0; i < MAX_ENEMIES; i++)
	{
		if (weapon_system->enemies[i].alive)
		{
			float dx = weapon_system->enemies[i].x - player->x;
			float dy = weapon_system->enemies[i].y - player->y;
			float distance = sqrtf(dx * dx + dy * dy);
			float angle = atan2f(dy, dx);
			float relative_angle = angle - player_angle;

			while (relative_angle < -M_PI)
				relative_angle += 2 * M_PI; /* Normalize angle */
			while (relative_angle > M_PI)
				relative_angle -= 2 * M_PI;
			/* Check if enemy is in FOV and has line of sight */
			if (fabsf(relative_angle) < fov / 2 && has_line_of_sight(player->x,
				player->y, weapon_system->enemies[i].x, weapon_system->enemies[i].y))
			{
				int screen_x = (int)(SCREEN_WIDTH / 2 * (1 + relative_angle / (fov / 2)));
				int height = (int)(SCREEN_HEIGHT / distance);

				if (height > SCREEN_HEIGHT * 2)
					height = SCREEN_HEIGHT * 2;
				enemy_rect.x = screen_x - height / 4;
				enemy_rect.y = SCREEN_HEIGHT / 2 - height / 2;
				enemy_rect.w = height / 2;
				enemy_rect.h = height;
				SDL_Texture *current_texture = animation_frame ?
					enemy_texture2 : enemy_texture1;
				SDL_RenderCopy(renderer, current_texture, NULL, &enemy_rect);
			}
		}
	}
}

/**
 * cleanup_enemies - Free enemy textures
 */
void cleanup_enemies(void)
{
	if (enemy_texture1)
		SDL_DestroyTexture(enemy_texture1);
	if (enemy_texture2)
		SDL_DestroyTexture(enemy_texture2);
}
