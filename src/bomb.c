#include <SDL/SDL_image.h>
#include <assert.h>

#include <map.h>
#include <bomb.h>
#include <monster.h>
#include <list.h>
#include <player.h>
#include <sprite.h>
#include <window.h>
#include <misc.h>
#include <constant.h>

struct bomb {
	int x, y;
	enum state current_state;
	int range;
	float timer_bomb;
	int explode;
};


int bomb_get_x(struct bomb* bomb) {
	assert(bomb != NULL);
	return bomb->x;
}

int bomb_get_y(struct bomb* bomb) {
	assert(bomb != NULL);
	return bomb->y;
}

int bomb_get_timer(struct bomb* bomb) {
	assert(bomb != NULL);
	return bomb->timer_bomb;
}

void bomb_set_timer(struct bomb* bomb, float time) {
	assert(bomb != NULL);
	bomb->timer_bomb=time;
}

enum state bomb_get_current_state(struct bomb* bomb) {
	assert(bomb);
	return bomb->current_state;
}

void bomb_set_current_state(struct bomb* bomb, enum state state) {
	assert(bomb);
	bomb->current_state = state;
}

struct bomb* bomb_find(struct map* map, int x, int y) {
	struct list* bomb_list = map_get_bombs(map);
	while(bomb_list != NULL) {
		if(bomb_list->x == x && bomb_list->y == y)
			return bomb_list->data;
		bomb_list = bomb_list->next;
	}
	return NULL;
}

struct bomb* bomb_init(struct player* player) {
	struct bomb* bomb = malloc(sizeof(*bomb));
	bomb->x = player_get_x(player);
	bomb->y = player_get_y(player);
	bomb->current_state = STATE1;
	bomb->range = player_get_range(player);
	bomb->timer_bomb = SDL_GetTicks();
	bomb->explode = 0;

	return bomb;
}

void bomb_install(struct player* player, struct map* map) {
	struct bomb* bomb = malloc(sizeof(*bomb));
	if (!bomb)
		error("Memory error");
	bomb = bomb_init(player);												// Prepare a bomb with wanted specifications
	map_insert_bomb(map, bomb_get_x(bomb), bomb_get_y(bomb), bomb);			// Insert this bomb in the map bomb list
	map_set_cell_type(map, bomb_get_x(bomb), bomb_get_y(bomb), CELL_BOMB);	// Set the CELL to display the bomb
}

void bomb_display(struct map* map, struct player* player) {
	if(map_get_bombs(map) != NULL){
		struct list* bomb_list = map_get_bombs(map);
		struct bomb* bomb = NULL;
		while (bomb_list != NULL){
			bomb = bomb_list->data;
			if ( SDL_GetTicks() - bomb_get_timer(bomb) < 200 ) {			// Display the 8 bomb pictures
				bomb_set_current_state(bomb, STATE0);
				window_display_image(sprite_get_bomb(bomb_get_current_state(bomb)),
						bomb_get_x(bomb) * SIZE_BLOC, bomb_get_y(bomb) * SIZE_BLOC);
			} else if ( SDL_GetTicks() - bomb_get_timer(bomb) < 400 ) {
				bomb_set_current_state(bomb, STATE1);
				window_display_image(sprite_get_bomb(bomb_get_current_state(bomb)),
						bomb_get_x(bomb) * SIZE_BLOC, bomb_get_y(bomb) * SIZE_BLOC);
			} else if ( SDL_GetTicks() - bomb_get_timer(bomb) < 600 ) {
				bomb_set_current_state(bomb, STATE2);
				window_display_image(sprite_get_bomb(bomb_get_current_state(bomb)),
						bomb_get_x(bomb) * SIZE_BLOC, bomb_get_y(bomb) * SIZE_BLOC);
			} else if ( SDL_GetTicks() - bomb_get_timer(bomb) < 800 ) {
				bomb_set_current_state(bomb, STATE3);
				window_display_image(sprite_get_bomb(bomb_get_current_state(bomb)),
						bomb_get_x(bomb) * SIZE_BLOC, bomb_get_y(bomb) * SIZE_BLOC);
			} else if ( SDL_GetTicks() - bomb_get_timer(bomb) < 1000 ) {
				bomb_set_current_state(bomb, STATE4);
				window_display_image(sprite_get_bomb(bomb_get_current_state(bomb)),
						bomb_get_x(bomb) * SIZE_BLOC, bomb_get_y(bomb) * SIZE_BLOC);
			} else if ( SDL_GetTicks() - bomb_get_timer(bomb) < 1200 ) {
				bomb_set_current_state(bomb, STATE5);
				window_display_image(sprite_get_bomb(bomb_get_current_state(bomb)),
						bomb_get_x(bomb) * SIZE_BLOC, bomb_get_y(bomb) * SIZE_BLOC);
			} else if ( SDL_GetTicks() - bomb_get_timer(bomb) < 1400 ) {
				bomb_set_current_state(bomb, STATE6);
				window_display_image(sprite_get_bomb(bomb_get_current_state(bomb)),
										bomb_get_x(bomb) * SIZE_BLOC, bomb_get_y(bomb) * SIZE_BLOC);
			} else if ( SDL_GetTicks() - bomb_get_timer(bomb) < 1600 ) {
				bomb_set_current_state(bomb, STATE7);
				window_display_image(sprite_get_bomb(bomb_get_current_state(bomb)),
										bomb_get_x(bomb) * SIZE_BLOC, bomb_get_y(bomb) * SIZE_BLOC);
			} else if ( SDL_GetTicks() - bomb_get_timer(bomb) < 1633 ) {
				bomb_set_current_state(bomb, STATE8);		// Display the flames
				bomb_flame_display(map,player,bomb);
			} else if ( SDL_GetTicks() - bomb_get_timer(bomb) < 1666 ) {
				bomb_set_current_state(bomb, STATE9);
				bomb_flame_display(map,player,bomb);
			} else if ( SDL_GetTicks() - bomb_get_timer(bomb) < 1700 ) {
				bomb_set_current_state(bomb, STATE10);
				bomb_flame_display(map,player,bomb);
			} else {
				map_set_cell_type(map, bomb_get_x(bomb), bomb_get_y(bomb), CELL_EMPTY);							// Reset the CELL
				bomb_destruct(map, player, bomb);																// Destruction of the elements
				map_set_bombs(map, list_find_delete(map_get_bombs(map),bomb_get_x(bomb), bomb_get_y(bomb)));	// Erase the bomb of the list
				bomb_list = map_get_bombs(map);	// Reload the list

			}
			if (map_get_bombs(map) != NULL)
				bomb_list = bomb_list->next;
		}
	}
}

void bomb_flame_display(struct map* map, struct player* player,struct bomb* bomb){

	window_display_image(sprite_get_bomb(bomb_get_current_state(bomb)), bomb_get_x(bomb) * SIZE_BLOC, bomb_get_y(bomb) * SIZE_BLOC);

	int i;
	for(i = 1 ; i <= bomb->range ; i++){
		if (map_is_inside(map, bomb->x +i, bomb->y)){
			switch (map_get_cell_type(map, bomb->x +i, bomb->y)) {
			case CELL_EMPTY:
				window_display_image(sprite_get_bomb(bomb_get_current_state(bomb)), (bomb_get_x(bomb)+i) * SIZE_BLOC, bomb_get_y(bomb) * SIZE_BLOC);
				break;						// Display an explosion

			case CELL_SCENERY:
				i = bomb->range +1;			// Stop the explosion on this row
				break;

			case CELL_CASE:
				window_display_image(sprite_get_bomb(bomb_get_current_state(bomb)), (bomb_get_x(bomb)+i) * SIZE_BLOC, bomb_get_y(bomb) * SIZE_BLOC);
				i = bomb->range +1;			// Display and stop the explosion
				break;

			case CELL_BONUS:
				window_display_image(sprite_get_bomb(bomb_get_current_state(bomb)), (bomb_get_x(bomb)+i) * SIZE_BLOC, bomb_get_y(bomb) * SIZE_BLOC);
				i = bomb->range +1;
				break;

			case CELL_GOAL:
				i = bomb->range +1;
				break;

			case CELL_DOOR:
				i = bomb->range +1;
				break;

			case CELL_KEY:
				i = bomb->range +1;
				break;

			case CELL_MONSTER:
				window_display_image(sprite_get_bomb(bomb_get_current_state(bomb)), (bomb_get_x(bomb)+i) * SIZE_BLOC, bomb_get_y(bomb) * SIZE_BLOC);
				i = bomb->range +1;
				break;

			case CELL_PLAYER:
				window_display_image(sprite_get_bomb(bomb_get_current_state(bomb)), (bomb_get_x(bomb)+i) * SIZE_BLOC, bomb_get_y(bomb) * SIZE_BLOC);
				i = bomb->range +1;
				break;

			case CELL_BOMB:
				window_display_image(sprite_get_bomb(bomb_get_current_state(bomb)), (bomb_get_x(bomb)+i) * SIZE_BLOC, bomb_get_y(bomb) * SIZE_BLOC);
				i = bomb->range +1;
				break;

			default:
				break;
			}
		}
	}
	for(i = 1 ; i <= bomb->range ; i++){
		if (map_is_inside(map, bomb->x -i, bomb->y)){
			switch (map_get_cell_type(map, bomb->x -i, bomb->y)) {
			case CELL_EMPTY:
				window_display_image(sprite_get_bomb(bomb_get_current_state(bomb)), (bomb_get_x(bomb)-i) * SIZE_BLOC, bomb_get_y(bomb) * SIZE_BLOC);
				break;

			case CELL_SCENERY:
				i = bomb->range +1;
				break;

			case CELL_CASE:
				window_display_image(sprite_get_bomb(bomb_get_current_state(bomb)), (bomb_get_x(bomb)-i) * SIZE_BLOC, bomb_get_y(bomb) * SIZE_BLOC);
				i = bomb->range +1;
				break;

			case CELL_BONUS:
				window_display_image(sprite_get_bomb(bomb_get_current_state(bomb)), (bomb_get_x(bomb)-i) * SIZE_BLOC, bomb_get_y(bomb) * SIZE_BLOC);
				i = bomb->range +1;
				break;

			case CELL_GOAL:
				i = bomb->range +1;
				break;

			case CELL_DOOR:
				i = bomb->range +1;
				break;

			case CELL_KEY:
				i = bomb->range +1;
				break;

			case CELL_MONSTER:
				window_display_image(sprite_get_bomb(bomb_get_current_state(bomb)), (bomb_get_x(bomb)-i) * SIZE_BLOC, bomb_get_y(bomb) * SIZE_BLOC);
				i = bomb->range +1;
				break;

			case CELL_PLAYER:
				window_display_image(sprite_get_bomb(bomb_get_current_state(bomb)), (bomb_get_x(bomb)-i) * SIZE_BLOC, bomb_get_y(bomb) * SIZE_BLOC);
				i = bomb->range +1;
				break;

			case CELL_BOMB:
				window_display_image(sprite_get_bomb(bomb_get_current_state(bomb)), (bomb_get_x(bomb)-i) * SIZE_BLOC, bomb_get_y(bomb) * SIZE_BLOC);
				i = bomb->range +1;
				break;

			default:
				break;
			}
		}
	}
	for(i = 1 ; i <= bomb->range ; i++){
		if (map_is_inside(map, bomb->x, bomb->y +i)){
			switch (map_get_cell_type(map, bomb->x, bomb->y +i)) {
			case CELL_EMPTY:
				window_display_image(sprite_get_bomb(bomb_get_current_state(bomb)), bomb_get_x(bomb) * SIZE_BLOC, (bomb_get_y(bomb)+i) * SIZE_BLOC);
				break;

			case CELL_SCENERY:
				i = bomb->range +1;
				break;

			case CELL_CASE:
				window_display_image(sprite_get_bomb(bomb_get_current_state(bomb)), bomb_get_x(bomb) * SIZE_BLOC, (bomb_get_y(bomb)+i) * SIZE_BLOC);
				i = bomb->range +1;
				break;

			case CELL_BONUS:
				window_display_image(sprite_get_bomb(bomb_get_current_state(bomb)), bomb_get_x(bomb) * SIZE_BLOC, (bomb_get_y(bomb)+i) * SIZE_BLOC);
				i = bomb->range +1;
				break;

			case CELL_GOAL:
				i = bomb->range +1;
				break;

			case CELL_DOOR:
				i = bomb->range +1;
				break;

			case CELL_KEY:
				i = bomb->range +1;
				break;

			case CELL_MONSTER:
				window_display_image(sprite_get_bomb(bomb_get_current_state(bomb)), bomb_get_x(bomb) * SIZE_BLOC, (bomb_get_y(bomb)+i) * SIZE_BLOC);
				i = bomb->range +1;
				break;

			case CELL_PLAYER:
				window_display_image(sprite_get_bomb(bomb_get_current_state(bomb)), bomb_get_x(bomb) * SIZE_BLOC, (bomb_get_y(bomb)+i) * SIZE_BLOC);
				i = bomb->range +1;
				break;

			case CELL_BOMB:
				window_display_image(sprite_get_bomb(bomb_get_current_state(bomb)), bomb_get_x(bomb) * SIZE_BLOC, (bomb_get_y(bomb)+i) * SIZE_BLOC);
				i = bomb->range +1;
				break;

			default:
				break;
			}
		}
	}
	for(i = 1 ; i <= bomb->range ; i++){
		if (map_is_inside(map, bomb->x, bomb->y -i)){
			switch (map_get_cell_type(map, bomb->x, bomb->y -i)) {
			case CELL_EMPTY:
				window_display_image(sprite_get_bomb(bomb_get_current_state(bomb)), bomb_get_x(bomb) * SIZE_BLOC, (bomb_get_y(bomb)-i) * SIZE_BLOC);
				break;

			case CELL_SCENERY:
				i = bomb->range +1;
				break;

			case CELL_CASE:
				window_display_image(sprite_get_bomb(bomb_get_current_state(bomb)), bomb_get_x(bomb) * SIZE_BLOC, (bomb_get_y(bomb)-i) * SIZE_BLOC);
				i = bomb->range +1;
				break;

			case CELL_BONUS:
				window_display_image(sprite_get_bomb(bomb_get_current_state(bomb)), bomb_get_x(bomb) * SIZE_BLOC, (bomb_get_y(bomb)-i) * SIZE_BLOC);
				i = bomb->range +1;
				break;

			case CELL_GOAL:
				i = bomb->range +1;
				break;

			case CELL_DOOR:
				i = bomb->range +1;
				break;

			case CELL_KEY:
				i = bomb->range +1;
				break;

			case CELL_MONSTER:
				window_display_image(sprite_get_bomb(bomb_get_current_state(bomb)), bomb_get_x(bomb) * SIZE_BLOC, (bomb_get_y(bomb)-i) * SIZE_BLOC);
				i = bomb->range +1;
				break;

			case CELL_PLAYER:
				window_display_image(sprite_get_bomb(bomb_get_current_state(bomb)), bomb_get_x(bomb) * SIZE_BLOC, (bomb_get_y(bomb)-i) * SIZE_BLOC);
				i = bomb->range +1;
				break;

			case CELL_BOMB:
				window_display_image(sprite_get_bomb(bomb_get_current_state(bomb)), bomb_get_x(bomb) * SIZE_BLOC, (bomb_get_y(bomb)-i) * SIZE_BLOC);
				i = bomb->range +1;
				break;

			default:
				break;
			}
		}
	}
}

void bomb_destruct(struct map* map, struct player* player,struct bomb* bomb){

	struct monster* monster;
	if(player_get_x(player)==bomb_get_x(bomb) && player_get_y(player)==bomb_get_y(bomb)){
		if (player_get_invincibleTimer(player) == 0) {
			if (player_get_nb_life(player) == 0 ) {
				player_set_dead(player);
			} else {
				player_dec_nb_life(player);
				player_set_invincible(player, 60);
			}
		}
	}		// Kill the player if he is touched by an explosion
	if (map_get_cell_type(map, bomb->x , bomb->y)== CELL_MONSTER){
		monster=monster_find(map, bomb->x, bomb->y);
		monster_set_dead(monster);
	}
	int i;
	for(i = 1 ; i <= bomb->range ; i++){
		if (map_is_inside(map, bomb->x +i, bomb->y)){
			struct bomb* fbomb = bomb_find(map, bomb->x +i, bomb->y);	// Search if there is a bomb on that area
			switch (map_get_cell_type(map, bomb->x +i, bomb->y)) {
			case CELL_EMPTY:
				break;

			case CELL_SCENERY:
				i = bomb->range +1;
				break;

			case CELL_CASE:
				map_case_explosion(map, bomb->x +i, bomb->y);			// Destroy the case and display a bonus
				i = bomb->range +1;
				break;

			case CELL_BONUS:
				map_set_cell_type(map, bomb->x +i, bomb->y, CELL_EMPTY);
				i = bomb->range +1;
				break;

			case CELL_GOAL:
				i = bomb->range +1;
				break;

			case CELL_DOOR:
				i = bomb->range +1;
				break;

			case CELL_KEY:
				i = bomb->range +1;
				break;

			case CELL_MONSTER:
				monster=monster_find(map, bomb->x +i, bomb->y);
				monster_set_dead(monster);
				i = bomb->range +1;
				break;

			case CELL_PLAYER:
				if (player_get_invincibleTimer(player) == 0) {
					if (player_get_nb_life(player) == 0 ) {
						player_set_dead(player);
					} else {
						player_dec_nb_life(player);
						player_set_invincible(player, 60);
					}
				}
				i = bomb->range +1;
				break;

			case CELL_BOMB:												// Cause an explosion chain if the explosion touches a bomb
				if(fbomb != NULL)
					fbomb->timer_bomb= (SDL_GetTicks() - 1601);
				i = bomb->range +1;
				break;

			default:
				break;
			}
		}
	}
	for(i = 1 ; i <= bomb->range ; i++){
		if (map_is_inside(map, bomb->x -i, bomb->y)){
			struct bomb* fbomb = bomb_find(map, bomb->x -i, bomb->y);
			switch (map_get_cell_type(map, bomb->x -i, bomb->y)) {
			case CELL_EMPTY:
				break;

			case CELL_SCENERY:
				i = bomb->range +1;
				break;

			case CELL_CASE:
				map_case_explosion(map, bomb->x -i, bomb->y);
				i = bomb->range +1;
				break;

			case CELL_BONUS:
				map_set_cell_type(map, bomb->x -i, bomb->y, CELL_EMPTY);
				i = bomb->range +1;
				break;

			case CELL_GOAL:
				i = bomb->range +1;
				break;

			case CELL_DOOR:
				i = bomb->range +1;
				break;

			case CELL_KEY:
				i = bomb->range +1;
				break;

			case CELL_MONSTER:
				monster=monster_find(map, bomb->x -i, bomb->y);
				monster_set_dead(monster);
				i = bomb->range +1;
				break;

			case CELL_PLAYER:
				if (player_get_invincibleTimer(player) == 0) {
					if (player_get_nb_life(player) == 0 ) {
						player_set_dead(player);
					} else {
						player_dec_nb_life(player);
						player_set_invincible(player, 60);
					}
				}
				i = bomb->range +1;
				break;

			case CELL_BOMB:
				if(fbomb != NULL)
					fbomb->timer_bomb= (SDL_GetTicks() - 1601);
				i = bomb->range +1;
				break;

			default:
				break;
			}
		}
	}
	for(i = 1 ; i <= bomb->range ; i++){
		if (map_is_inside(map, bomb->x, bomb->y +i)){
			struct bomb* fbomb = bomb_find(map, bomb->x, bomb->y +i);
			switch (map_get_cell_type(map, bomb->x, bomb->y +i)) {
			case CELL_EMPTY:
				break;

			case CELL_SCENERY:
				i = bomb->range +1;
				break;

			case CELL_CASE:
				map_case_explosion(map, bomb->x, bomb->y +i);
				i = bomb->range +1;
				break;

			case CELL_BONUS:
				map_set_cell_type(map, bomb->x, bomb->y +i, CELL_EMPTY);
				i = bomb->range +1;
				break;

			case CELL_DOOR:
				i = bomb->range +1;
				break;

			case CELL_KEY:
				i = bomb->range +1;
				break;

			case CELL_GOAL:
				i = bomb->range +1;
				break;

			case CELL_MONSTER:
				monster=monster_find(map, bomb->x , bomb->y +i);
				monster_set_dead(monster);
				i = bomb->range +1;
				break;

			case CELL_PLAYER:
				if (player_get_invincibleTimer(player) == 0) {
					if (player_get_nb_life(player) == 0 ) {
						player_set_dead(player);
					} else {
						player_dec_nb_life(player);
						player_set_invincible(player, 60);
					}
				}
				i = bomb->range +1;
				break;

			case CELL_BOMB:
				if(fbomb != NULL)
					fbomb->timer_bomb= (SDL_GetTicks() - 1601);
				i = bomb->range +1;
				break;

			default:
				break;
			}
		}
	}
	for(i = 1 ; i <= bomb->range ; i++){
		if (map_is_inside(map, bomb->x, bomb->y -i)){
			struct bomb* fbomb = bomb_find(map, bomb->x, bomb->y -i);
			switch (map_get_cell_type(map, bomb->x, bomb->y -i)) {
			case CELL_EMPTY:
				break;

			case CELL_SCENERY:
				i = bomb->range +1;
				break;

			case CELL_CASE:
				map_case_explosion(map, bomb->x, bomb->y -i);
				i = bomb->range +1;
				break;

			case CELL_BONUS:
				map_set_cell_type(map, bomb->x, bomb->y -i, CELL_EMPTY);
				i = bomb->range +1;
				break;

			case CELL_DOOR:
				i = bomb->range +1;
				break;

			case CELL_KEY:
				i = bomb->range +1;
				break;

			case CELL_GOAL:
				i = bomb->range +1;
				break;

			case CELL_MONSTER:
				monster=monster_find(map, bomb->x , bomb->y +i);
				monster_set_dead(monster);
				i = bomb->range +1;
				break;

			case CELL_PLAYER:
				if (player_get_invincibleTimer(player) == 0) {
					if (player_get_nb_life(player) == 0 ) {
						player_set_dead(player);
					} else {
						player_dec_nb_life(player);
						player_set_invincible(player, 60);
					}
				}
				i = bomb->range +1;
				break;

			case CELL_BOMB:
				if(fbomb != NULL)
					fbomb->timer_bomb= (SDL_GetTicks() - 1601);
				i = bomb->range +1;
				break;

			default:
				break;
			}
		}
	}
}

void bomb_delay_timer(struct map* map, struct player* player, int delay){
	struct list* bomb_list = map_get_bombs(map);
	struct bomb* bomb = NULL;
	while (bomb_list != NULL){

		bomb = bomb_list->data;
		bomb->timer_bomb += delay;

		if (map_get_bombs(map) != NULL)
			bomb_list = bomb_list->next;
	}
}
