#ifndef MONSTER_H_
#define MONSTER_H_

#include <map.h>
#include <player.h>
#include <constant.h>

struct monster;

// Creates a new monster
void monster_init(struct map* map, int i, int j);
void monster_free(struct monster* monster);

int monster_get_dead(struct monster* monster);
void monster_set_dead(struct monster* monster);

// Returns the current position of the monster
int monster_get_x(struct monster* monster);
int monster_get_y(struct monster* monster);

float monster_get_timer(struct monster* monster);
void monster_set_timer(struct monster* monster, float time);

// Set the direction of the next move of the monster
void monster_set_current_way(struct monster* monster, way_t way);

// Load the player position from the map
void monster_from_map(struct map* map);

// Move the player according to the current direction
void monster_move(struct monster* monster, struct player* player, struct map* map);

// Display the player on the screen
void monster_display(struct map* map, struct player* player);

struct monster* monster_find(struct map* map, int x, int y);

void monster_delay_timer(struct map* map, struct player* player);

#endif /* MONSTER_H_ */
