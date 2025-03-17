#ifndef RAYCAST_H
#define RAYCAST_H

#include <SDL2/SDL.h>
#include "maze.h"
#include "player.h"

/* Constants for raycasting */
#define FOV 60.0       /* Field of View in degrees */
#define NUM_RAYS 320   /* Number of rays to cast */
#define MAX_DEPTH 10   /* Maximum distance a ray can travel */


/* Function prototype */
void cast_rays(SDL_Renderer *renderer, Player *player, const int maze[15][15]);

#endif /* RAYCAST_H */
