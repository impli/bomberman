#include <SDL/SDL_image.h>
#include <assert.h>

#include <player.h>
#include <monster.h>
#include <map.h>
#include <list.h>
#include <sprite.h>
#include <window.h>
#include <misc.h>
#include <constant.h>

struct monster {
	int x, y;
	enum way current_way;
	float timer_monster;
	int dead;
};

void monster_init(struct map* map, int i, int j) {
	struct monster* monster = malloc(sizeof(*monster));
	if (!monster)
		error("Memory error");

	monster->x=i;
	monster->y=j;
	monster->current_way = SOUTH;
	monster->timer_monster = 0;
	monster->dead = 0;

	map_insert_monster(map, i, j, monster);
}

void monster_free(struct monster* monster) {
	assert(monster);
	free(monster);
}

int monster_get_dead(struct monster* monster) {
	assert(monster != NULL);
	return monster->dead;
}

void monster_set_dead(struct monster* monster) {
	assert(monster != NULL);
	monster->dead = 1;
}

float monster_get_timer(struct monster* monster) {
	assert(monster != NULL);
	return monster->timer_monster;
}

void monster_set_timer(struct monster* monster, float time) {
	assert(monster);
	monster->timer_monster = time;
}

int monster_get_x(struct monster* monster) {
	assert(monster != NULL);
	return monster->x;
}

int monster_get_y(struct monster* monster) {
	assert(monster != NULL);
	return monster->y;
}

void monster_set_current_way(struct monster* monster, enum way way) {
	assert(monster);
	monster->current_way = way;
}

struct monster* monster_find(struct map* map, int x, int y) {
	struct list* monster_list = map_get_monsters(map);
	while(monster_list != NULL) {
		if(monster_list->x == x && monster_list->y == y)
			return monster_list->data;
		monster_list = monster_list->next;
	}
	return NULL;
}

void monster_from_map(struct map* map) {
	assert(map);

	int i, j;
	for (i = 0; i < map_get_width(map); i++) {
		for (j = 0; j < map_get_height(map); j++) {
			if (map_get_cell_type(map, i, j) == CELL_MONSTER) {
				monster_init(map,i,j);
			}
		}
	}
}

static int monster_move_aux(struct monster* monster, struct player* player, struct map* map, int x, int y) {


	if (!map_is_inside(map, x, y))
		return 0;

	switch (map_get_cell_type(map, x, y)) {
	case CELL_SCENERY:
		return 0;
		break;

	case CELL_CASE:
		return 0;
		break;

	case CELL_BONUS:
		return 1;
		break;

	case CELL_GOAL:
		return 0;
		break;

	case CELL_MONSTER:
		return 0;
		break;

	case CELL_PLAYER:
		return 1;
		break;

	case CELL_KEY:
		return 0;
		break;

	case CELL_BOMB:
		return 0;
		break;

	case CELL_DOOR:
		return 0;
		break;

	default:
		break;
	}

	// Monster has moved
	return 1;
}

void monster_move(struct monster* monster, struct player* player, struct map* map) {
	int x = monster->x;
	int y = monster->y;
	int move = 0;

	int proba = rand() % 4;
	switch (proba) {
	case 0:
		monster->current_way = NORTH;
		if (monster_move_aux(monster, player, map, x, y - 1)) {
			monster->y--;
			move = 1;
		}
		break;

	case 1:
		monster->current_way = SOUTH;
		if (monster_move_aux(monster, player, map, x, y + 1)) {
			monster->y++;
			move = 1;
		}
		break;

	case 2:
		monster->current_way = WEST;
		if (monster_move_aux(monster, player, map, x - 1, y)) {
			monster->x--;
			move = 1;
		}
		break;

	case 3:
		monster->current_way = EAST;
		if (monster_move_aux(monster, player, map, x + 1, y)) {
			monster->x++;
			move = 1;
		}
		break;

	}

	if (move) {
		if ( map_get_cell_type(map, x, y) != CELL_BONUS && map_get_cell_type(map, x, y) != CELL_PLAYER )
			map_set_cell_type(map, x, y, CELL_EMPTY);
		map_set_cell_type(map, monster->x, monster->y, CELL_MONSTER);
	}
	if( monster->x == player_get_x(player) && monster->y == player_get_y(player) ){
		if (player_get_invincibleTimer(player) == 0) {
			if (player_get_nb_life(player) == 0 ) {
				player_set_dead(player);
			} else {
				player_dec_nb_life(player);
								player_set_invincible(player, 60);
			}
		}
	}

}

void monster_display(struct map* map, struct player* player) {
	if(map_get_monsters(map) != NULL){
		struct list* monster_list = map_get_monsters(map);
		struct monster* monster = NULL;
		while (monster_list != NULL){
			monster = monster_list->data;
			if(monster->dead == 1){
				map_set_monsters(map, list_find_delete(map_get_monsters(map), monster->x, monster->y));
				map_set_cell_type(map, monster->x, monster->y, CELL_EMPTY);
			}
			if(monster->dead == 0){
				window_display_image(sprite_get_monster(monster->current_way),
						monster->x * SIZE_BLOC, monster->y * SIZE_BLOC);

				if ( SDL_GetTicks() - monster_get_timer(monster) > 1000 ) {
					monster_move(monster, player, map);
					window_display_image(sprite_get_monster(monster->current_way),
							monster->x * SIZE_BLOC, monster->y * SIZE_BLOC);
					monster_set_timer(monster, SDL_GetTicks());
					map_set_monsters(map, list_find_delete(map_get_monsters(map),monster_get_x(monster), monster_get_y(monster)));
					map_insert_monster(map,  monster_get_x(monster),  monster_get_y(monster), monster);
					monster_list = map_get_monsters(map);																	// Reload the list
				}
			}
			if (map_get_monsters(map) != NULL)
				monster_list = monster_list->next;
		}
	}
}

void monster_delay_timer(struct map* map, struct player* player){
	struct list* monster_list = map_get_monsters(map);
	struct monster* monster = NULL;
	while (monster_list != NULL){

		monster = monster_list->data;
		monster->timer_monster -= SDL_GetTicks();

		if (map_get_monsters(map) != NULL)
			monster_list = monster_list->next;
	}
}
