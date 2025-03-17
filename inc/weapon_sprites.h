#ifndef WEAPON_SPRITES_H
#define WEAPON_SPRITES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Surface *create_weapon_sprite(int width, int height);
int save_weapon_sprites(void);

#endif
