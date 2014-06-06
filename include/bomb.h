#ifndef BOMB_H_
#define BOMB_H_

#include <player.h>
#include <map.h>
#include <constant.h>

struct bomb;

// Return specifications of a bomb
int bomb_get_x(struct bomb* bomb);
int bomb_get_y(struct bomb* bomb);
int bomb_get_timer(struct bomb* bomb);
void bomb_set_timer(struct bomb* bomb, float time);
enum state bomb_get_current_state(struct bomb* bomb);

// Set the state of a bomb
void bomb_set_current_state(struct bomb* bomb, enum state state);

// Search if there is a bomb on the map on {x,y} and return this bomb... or nothing if there is no bomb
struct bomb* bomb_find(struct map* map, int x, int y);

// Return a bomb with basic specifications
struct bomb* bomb_init(struct player* player);

// Install a bomb where the player is on the current map
void bomb_install(struct player* player, struct map* map);

// Display a bomb animation, include the animation of flames and the destruction of the elements
void bomb_display(struct map* map, struct player* player);

// Display the flames of the explosion
void bomb_flame_display(struct map* map, struct player* player,struct bomb* bomb);

// Destroy the elements during the explosion
void bomb_destruct(struct map* map, struct player* player,struct bomb* bomb);

void bomb_delay_timer(struct map* map, struct player* player, int delay);

#endif /* BOMB_H_ */
