#ifndef GAME_H_
#define GAME_H_

#include <player.h>
#include <level.h>
<<<<<<< HEAD
#include <map.h>
=======
>>>>>>> 9cdb4d406aae54b9c6f500cb75d562a688f7bcb3

struct game;

// Create a new game
struct game* game_new();

// Free a game
void game_free(struct game* game);

<<<<<<< HEAD
int game_get_win(struct game* game);
void game_set_win(struct game* game);

=======
>>>>>>> 9cdb4d406aae54b9c6f500cb75d562a688f7bcb3
// Return the player of the current game
struct player* game_get_player(struct game* game);

// Return the current level
struct level* game_get_curr_level(struct game* game);

// Display the game of the screen
void game_display(struct game* game);

<<<<<<< HEAD
void game_pause_display(struct game* game);

void game_change_level(struct game* game, int i);

=======
>>>>>>> 9cdb4d406aae54b9c6f500cb75d562a688f7bcb3
// update
int game_update(struct game* game);

#endif /* GAME_H_ */
