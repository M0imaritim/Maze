#ifndef WEAPON_SPRITES_H
#define WEAPON_SPRITES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/* Maximum number of enemies and bullets */
#define MAX_ENEMIES 10
#define MAX_BULLETS 20
#define SHOT_COOLDOWN 500 /* ms between shots */

/**
 * struct Enemy - Enemy entity representation
 * @x: X position in maze
 * @y: Y position in maze
 * @alive: 1 if alive, 0 if dead
 * @health: Current health points
 * @speed: Movement speed
 * @last_attack: Time of last attack
 * @frame_time: Time of last frame change
 * @frame: Current animation frame
 * @direction: where enemy is facing
 */
typedef struct Enemy
{
float x;
float y;
int alive;
float health;
float speed;
Uint32 last_attack, frame_time;
int frame;
int direction;
} Enemy;

/**
 * struct Bullet - Bullet entity representation
 * @x: X position in maze
 * @y: Y position in maze
 * @dx: X direction
 * @dy: Y direction
 * @active: 1 if active, 0 if inactive
 * @created: Time when bullet was created
 */
typedef struct Bullet
{
float x;
float y;
float dx;
float dy;
int active;
Uint32 created;
} Bullet;

/**
 * struct WeaponSystem - Manages weapon, enemies and bullets
 * @enemies: Array of enemies
 * @bullets: Array of bullets
 * @enemy_count: Current number of active enemies
 * @score: Player's score
 * @player_health: Player's current health
 * @last_shot_time: Time of last shot fired
 * @enemy_texture: Texture for enemy sprites
 * @enemy_texture_width: Width of enemy texture
 * @enemy_texture_height: Height of enemy texture
 */
typedef struct WeaponSystem
{
Enemy enemies[MAX_ENEMIES];
Bullet bullets[MAX_BULLETS];
int enemy_count;
int score;
int player_health;
Uint32 last_shot_time;
SDL_Texture *enemy_texture;
int enemy_texture_width;
int enemy_texture_height;
} WeaponSystem;

/* Surface manipulation functions */
SDL_Surface *resize_surface(SDL_Surface *surface, int width, int height);
SDL_Surface *load_weapon_image(const char *filename, int width, int height);
SDL_Surface *create_weapon_sprite(int width, int height);

/* Weapon system initialization and cleanup */
int init_weapon_system(WeaponSystem *weapon_system, const int maze[15][15]);
void cleanup_weapon_system(void);
void cleanup_weapon_sprite(Player *player);

/* Enemy management functions */
void init_enemies(WeaponSystem *weapon_system, const int maze[15][15]);
void update_enemies(WeaponSystem *weapon_system, Player *player);
int check_collision(const int maze[15][15], float x, float y);
int has_line_of_sight(float start_x, float start_y, float end_x, float end_y);
void draw_minimap_enemies(SDL_Renderer *renderer, int map_x, int map_y,
int cell_size, WeaponSystem *weapon_system);

/* Bullet management functions */
void create_bullet(WeaponSystem *weapon_system, Player *player);
void update_bullets(WeaponSystem *weapon_system);

/* Shooting mechanics */
void handle_shooting(WeaponSystem *weapon_system, Player *player,
const Uint8 *keyboard);

/* Update and render functions */
void update_weapon_system(WeaponSystem *weapon_system, Player *player,
					const Uint8 *keyboard, const int maze[15][15]);
void render_weapon_system(SDL_Renderer *renderer, Player *player,
					WeaponSystem *weapon_system);

/* HUD and enemy rendering */
void draw_bullets_minimap(SDL_Renderer *renderer, WeaponSystem *weapon_system);
void draw_enemies_3d(SDL_Renderer *renderer, Player *player,
			WeaponSystem *weapon_system);
void draw_hud(SDL_Renderer *renderer, WeaponSystem *weapon_system);

#endif /* WEAPON_SPRITES_H */
