#include <SDL/SDL_image.h>
#include <assert.h>

#include <player.h>
#include <sprite.h>
#include <window.h>
#include <misc.h>
#include <level.h>
#include <game.h>
#include <map.h>
#include <constant.h>

struct player {
	int x, y;
	enum way current_way;
	int nb_bomb;
	int nb_life;
	int range;
	int invincibleTimer;
	int dead;
	int key;
};

struct player* player_init(int bomb_number, int life_number, int range_number) {
	struct player* player = malloc(sizeof(*player));
	if (!player)
		error("Memory error");

	player->current_way = SOUTH;
	player->nb_bomb = bomb_number;
	player->nb_life = life_number;
	player->range = range_number;
	player->invincibleTimer = 0;
	player->dead = 0;
	player->key=0;

	return player;
}

void player_free(struct player* player) {
	assert(player);
	free(player);
}

int player_get_dead(struct player* player) {
	assert(player != NULL);
	return player->dead;
}

void player_set_dead(struct player* player) {
	assert(player != NULL);
	player->dead = 1;
}

int player_get_invincibleTimer(struct player* player) {
	assert(player != NULL);
	return player->invincibleTimer;
}

void player_dec_invincibleTimer(struct player* player) {
	assert(player);
	player->invincibleTimer -= 1;
}

void player_set_invincible(struct player* player, int n) {
	assert(player);
	player->invincibleTimer = n;
}

int player_get_x(struct player* player) {
	assert(player != NULL);
	return player->x;
}

int player_get_y(struct player* player) {
	assert(player != NULL);
	return player->y;
}

void player_set_current_way(struct player* player, enum way way) {
	assert(player);
	player->current_way = way;
}

int player_get_key(struct player* player){
	assert(player);
	return player->key;
}

int player_get_nb_bomb(struct player* player) {
	assert(player);
	return player->nb_bomb;
}

int player_get_nb_life(struct player* player) {
	assert(player);
	return player->nb_life;
}

void player_inc_nb_bomb(struct player* player) {
	assert(player);
	player->nb_bomb += 1;
}

void player_inc_nb_life(struct player* player) {
	assert(player);
	player->nb_life += 1;
}

int player_get_range(struct player* player) {
	assert(player);
	return player->range;
}

void player_inc_range(struct player* player) {
	assert(player);
	player->range += 1;
}

void player_dec_range(struct player* player) {
	assert(player);
	player->range -= 1;
}

void player_dec_nb_bomb(struct player* player) {
	assert(player);
	player->nb_bomb -= 1;
}

void player_dec_nb_life(struct player* player) {
	assert(player);
	player->nb_life -= 1;
}

void player_from_map(struct player* player, struct map* map) {
	assert(player);
	assert(map);

	int i, j;
	for (i = 0; i < map_get_width(map); i++) {
		for (j = 0; j < map_get_height(map); j++) {
			if (map_get_cell_type(map, i, j) == CELL_PLAYER) {
				player->x = i;
				player->y = j;
			}
		}
	}
}

static int player_move_aux(struct game* game, struct player* player, struct map* map, int x, int y) {

	if (!map_is_inside(map, x, y))
		return 0;

	int i=0;
	switch (map_get_cell_type(map, x, y)) {
	case CELL_SCENERY:
		return 0;
		break;

	case CELL_CASE:
		if(player->current_way == SOUTH && map_is_inside(map, x, y + 1) && map_get_cell_type(map, x, y + 1)==CELL_EMPTY) {
			map_set_cell_type(map, x, y + 1, map_get_cell(map, x, y));
			map_set_cell_type(map, x, y, CELL_EMPTY);
			return 1;
		}
		if(player->current_way == NORTH && map_is_inside(map, x, y - 1) && map_get_cell_type(map, x, y - 1)==CELL_EMPTY) {
			map_set_cell_type(map, x, y - 1, map_get_cell(map, x, y));
			map_set_cell_type(map, x, y, CELL_EMPTY);
			return 1;
		}
		if(player->current_way == EAST && map_is_inside(map, x + 1, y) && map_get_cell_type(map, x + 1, y)==CELL_EMPTY) {
			map_set_cell_type(map, x + 1, y, map_get_cell(map, x, y));
			map_set_cell_type(map, x, y, CELL_EMPTY);
			return 1;
		}
		if(player->current_way == WEST && map_is_inside(map, x - 1, y) && map_get_cell_type(map, x - 1, y)==CELL_EMPTY) {
			map_set_cell_type(map, x - 1, y, map_get_cell(map, x, y));
			map_set_cell_type(map, x, y, CELL_EMPTY);
			return 1;
		}
		return 0;
		break;

	case CELL_BONUS:
		switch (map_get_cell_bonus_type(map, x,  y)) {
			case NB_INC:
				player_inc_nb_bomb(player);
				return 1;
				break;
			case NB_DEC:
				if (player_get_nb_bomb(player) > 0)
					player_dec_nb_bomb(player);
				return 1;
				break;
			case RANGE_INC:
				player_inc_range(player);
				return 1;
				break;
			case RANGE_DEC:
				if (player_get_range(player) > 1)
					player_dec_range(player);
				return 1;
				break;
			case LIFE:
				player_inc_nb_life(player);
				return 1;
				break;
			default:
				break;
		}
		return 0;
		break;

	case CELL_GOAL:
		if(map_get_goal_type(map, x, y)==0){
			i=SDL_GetTicks();
			while(SDL_GetTicks() - i < 2000){
			window_display_image(sprite_get_next(),
					((map_get_width(map) / 2 )-4)* SIZE_BLOC,(( map_get_height(map) / 2) -1)* SIZE_BLOC);
			window_refresh();
			}
			game_change_level(game,1);
			return 0;
		}
		if(map_get_goal_type(map, x, y)==1){
			i=SDL_GetTicks();
			while(SDL_GetTicks() - i < 3000){
				window_display_image(sprite_get_end(),
						((map_get_width(map) / 2 )-4)* SIZE_BLOC,(( map_get_height(map) / 2) -1)* SIZE_BLOC);
				window_refresh();
			}
			game_set_win(game);

			return EXIT_SUCCESS;
		}
		break;

	case CELL_MONSTER:
		if (player->invincibleTimer == 0) {
			if (player_get_nb_life(player) == 0 ) {
				player->dead = 1;
				return 0;
			}
			player_dec_nb_life(player);
			player->invincibleTimer = 60;
		}
		return 0;
		break;

	case CELL_PLAYER:
		break;

	case CELL_BOMB:
		return 0;
		break;

	case CELL_DOOR:
		if (map_get_cell_door_type(map, x, y)){
			i=map_get_door_number(map, x, y);
			map_set_cell_type(map, player->x, player->y, 0);
			level_set_cur_map(game_get_curr_level(game), i);
			map_set_cell_type(level_get_curr_map(game_get_curr_level(game)), player->x, player->y, CELL_PLAYER);
			return 0;
		}
		if (player->key == 1){
			map_set_opened_door(map, x, y);
			player->key=0;
		}
		return 0;
		break;

	case CELL_KEY:
		player->key=1;
		return 1;
		break;

	default:
		break;
	}

	// Player has moved
	return 1;
}

int player_move(struct game* game) {

	struct player* player = game_get_player(game);
	struct map* map = level_get_curr_map(game_get_curr_level(game));

	int x = player->x;
	int y = player->y;
	int move = 0;

	switch (player->current_way) {
	case NORTH:
		if (player_move_aux(game, player, map, x, y - 1)) {
			player->y--;
			move = 1;
		}
		break;

	case SOUTH:
		if (player_move_aux(game, player, map, x, y + 1)) {
			player->y++;
			move = 1;
		}
		break;

	case WEST:
		if (player_move_aux(game, player, map, x - 1, y)) {
			player->x--;
			move = 1;
		}
		break;

	case EAST:
		if (player_move_aux(game, player, map, x + 1, y)) {
			player->x++;
			move = 1;
		}
		break;
	}

	if (move) {
		if ( map_get_cell_type(map, x, y) != CELL_BOMB && map_get_cell_type(map, x, y) != CELL_DOOR )
			map_set_cell_type(map, x, y, CELL_EMPTY);
		map_set_cell_type(map, player->x, player->y, CELL_PLAYER);
	}
	return move;
}

void player_display(struct player* player) {
	assert(player);
	if (player_get_invincibleTimer(player)>0){
		window_display_image(sprite_get_inv_player(player->current_way),
				player->x * SIZE_BLOC, player->y * SIZE_BLOC);
		}
	if (player_get_invincibleTimer(player)==0){
		window_display_image(sprite_get_player(player->current_way),
				player->x * SIZE_BLOC, player->y * SIZE_BLOC);
	}
	if (player_get_invincibleTimer(player) > 0)
			player_dec_invincibleTimer(player);
}

