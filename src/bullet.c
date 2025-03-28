#include "../inc/maze.h"
#include "../inc/weapon_sprites.h"

/**
 * create_bullet - Create a new bullet from player position
 * @weapon_system: Pointer to weapon system
 * @player: Pointer to player struct
 */
void create_bullet(WeaponSystem *weapon_system, Player *player)
{
	int i;
	Uint32 current_time = SDL_GetTicks();

	/* Implement shot cooldown */
	if (current_time - weapon_system->last_shot_time < SHOT_COOLDOWN)
		return;

	/* Find an inactive bullet slot */
	for (i = 0; i < MAX_BULLETS; i++)
	{
		if (!weapon_system->bullets[i].active)
		{
			/* Initialize the bullet */
			weapon_system->bullets[i].x = player->x;
			weapon_system->bullets[i].y = player->y;
			weapon_system->bullets[i].dx = player->dx;
			weapon_system->bullets[i].dy = player->dy;
			weapon_system->bullets[i].active = 1;
			weapon_system->bullets[i].created = current_time;

			/* Update last shot time */
			weapon_system->last_shot_time = current_time;
			break;
		}
	}
}

/**
 * update_bullets - Move bullets and check for collisions
 * @weapon_system: Pointer to weapon system
 */
void update_bullets(WeaponSystem *weapon_system)
{
	int i, j;
	const float bullet_speed = 0.2f;

	for (i = 0; i < MAX_BULLETS; i++)
	{
		if (weapon_system->bullets[i].active)
		{
			weapon_system->bullets[i].x += weapon_system->bullets[i].dx * bullet_speed;
			weapon_system->bullets[i].y += weapon_system->bullets[i].dy * bullet_speed;
			if (check_collision(maze, weapon_system->bullets[i].x,
						weapon_system->bullets[i].y))
			{
				weapon_system->bullets[i].active = 0;
				continue;
			}
			for (j = 0; j < MAX_ENEMIES; j++) /* Check for enemy collision */
			{
				if (weapon_system->enemies[j].alive)
				{
					float dx = weapon_system->bullets[i].x - weapon_system->enemies[j].x;
					float dy = weapon_system->bullets[i].y - weapon_system->enemies[j].y;
					float distance = sqrtf(dx * dx + dy * dy);

					if (distance >= 0.5f)
						continue;
					weapon_system->enemies[j].health -= 50.0f; /* Damage enemy */
					if (weapon_system->enemies[j].health <= 0) /* Check if enemy is killed */
					{
						weapon_system->enemies[j].alive = 0;
						weapon_system->score += 100;
						weapon_system->enemy_count--;
					}
					weapon_system->bullets[i].active = 0; /* Deactivate bullet */
					break;
				}
			}
			if (SDL_GetTicks() - weapon_system->bullets[i].created > 3000)
			weapon_system->bullets[i].active = 0; /* Deactivate bullets after 3sec */
		}}}
