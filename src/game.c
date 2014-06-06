#include <assert.h>
#include <time.h>

<<<<<<< HEAD
#include <list.h>
#include <bomb.h>
#include <monster.h>
#include <game.h>
#include <misc.h>
#include <map.h>
#include <level.h>
=======
#include <game.h>
#include <misc.h>
>>>>>>> 9cdb4d406aae54b9c6f500cb75d562a688f7bcb3
#include <window.h>
#include <sprite.h>

struct game {
	struct level* curr_level; // current level
	struct player* player;
<<<<<<< HEAD
	int win;

=======
>>>>>>> 9cdb4d406aae54b9c6f500cb75d562a688f7bcb3
};

struct game* game_new(void) {
	sprite_load(); // load sprites into process memory

	struct game* game = malloc(sizeof(*game));
	game->curr_level = level_get_level(0); // get maps of the first level

<<<<<<< HEAD
	game->player = player_init(1,2,1);
	player_from_map(game->player, level_get_map(game->curr_level, 0)); // get x,y of the player on the first map

	game->win=0;

=======
	game->player = player_init(1);
	player_from_map(game->player, level_get_map(game->curr_level, 0)); // get x,y of the player on the first map

>>>>>>> 9cdb4d406aae54b9c6f500cb75d562a688f7bcb3
	return game;
}

void game_free(struct game* game) {
	assert(game);

	player_free(game->player);
	level_free(game->curr_level);
}

<<<<<<< HEAD
int game_get_win(struct game* game) {
	assert(game);
	return game->win;
}

void game_set_win(struct game* game) {
	game->win=1;
}

=======
>>>>>>> 9cdb4d406aae54b9c6f500cb75d562a688f7bcb3
struct player* game_get_player(struct game* game) {
	assert(game);
	return game->player;
}

<<<<<<< HEAD
void game_change_level(struct game* game, int i){
	level_free(game->curr_level);
	game->curr_level = level_get_level(i);
	player_from_map(game->player, level_get_map(game->curr_level, 0));
}

=======
>>>>>>> 9cdb4d406aae54b9c6f500cb75d562a688f7bcb3
struct level* game_get_curr_level(struct game* game) {
	return game->curr_level;
}

void game_banner_display(struct game* game) {
	assert(game);

	struct map* map = level_get_curr_map(game_get_curr_level(game));
<<<<<<< HEAD
	struct player* player = game_get_player(game);
=======
>>>>>>> 9cdb4d406aae54b9c6f500cb75d562a688f7bcb3

	int y = (map_get_height(map)) * SIZE_BLOC;
	for (int i = 0; i < map_get_width(map); i++)
		window_display_image(sprite_get_banner_line(), i * SIZE_BLOC, y);

	int white_bloc = ((map_get_width(map) * SIZE_BLOC) - 6 * SIZE_BLOC) / 4;
	int x = white_bloc;
	y = (map_get_height(map) * SIZE_BLOC) + LINE_HEIGHT;
	window_display_image(sprite_get_banner_life(), x, y);

	x = white_bloc + SIZE_BLOC;
<<<<<<< HEAD
	window_display_image(
				sprite_get_number(player_get_nb_life(game_get_player(game))), x, y);
=======
	window_display_image(sprite_get_number(2), x, y);
>>>>>>> 9cdb4d406aae54b9c6f500cb75d562a688f7bcb3

	x = 2 * white_bloc + 2 * SIZE_BLOC;
	window_display_image(sprite_get_banner_bomb(), x, y);

	x = 2 * white_bloc + 3 * SIZE_BLOC;
	window_display_image(
			sprite_get_number(player_get_nb_bomb(game_get_player(game))), x, y);

	x = 3 * white_bloc + 4 * SIZE_BLOC;
	window_display_image(sprite_get_banner_range(), x, y);

	x = 3 * white_bloc + 5 * SIZE_BLOC;
<<<<<<< HEAD
	window_display_image(sprite_get_number(player_get_range(game_get_player(game))), x, y);

	if(player_get_key(player)==1){
		x = 3 * white_bloc + 6 * SIZE_BLOC;
		window_display_image(sprite_get_key(), x, y);
	}

=======
	window_display_image(sprite_get_number(1), x, y);
>>>>>>> 9cdb4d406aae54b9c6f500cb75d562a688f7bcb3
}

void game_display(struct game* game) {
	assert(game);

	window_clear();

	game_banner_display(game);
	level_display(game_get_curr_level(game));
	player_display(game->player);
<<<<<<< HEAD
	bomb_display(level_get_curr_map(game_get_curr_level(game)),game->player);
	monster_display(level_get_curr_map(game_get_curr_level(game)),game->player);
=======
>>>>>>> 9cdb4d406aae54b9c6f500cb75d562a688f7bcb3

	window_refresh();
}

<<<<<<< HEAD
void game_pause_display(struct game* game){
	int delay;
	int timer;
	int pause=0;
	SDL_Event event;
	struct player* player = game_get_player(game);
	struct map* map = level_get_curr_map(game_get_curr_level(game));
	pause = 1;
	timer=SDL_GetTicks();
	while(pause == 1){

		window_display_image(sprite_get_pause(),((map_get_width(map) / 2 )-1)* SIZE_BLOC,(( map_get_height(map) / 2) -1)* SIZE_BLOC);
		window_refresh();
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_p:
					pause=0;
					break;
				default :
					break;
				}
				break;
			}
		}
	}
	delay=SDL_GetTicks()-timer;
	bomb_delay_timer(map,player, delay);
	monster_delay_timer(map,player);
}

=======
>>>>>>> 9cdb4d406aae54b9c6f500cb75d562a688f7bcb3
short input_keyboard(struct game* game) {
	SDL_Event event;
	struct player* player = game_get_player(game);
	struct map* map = level_get_curr_map(game_get_curr_level(game));

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT: // keyboard : esc
			return 1;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				return 1;
<<<<<<< HEAD
			case SDLK_p:
				game_pause_display(game);
				break;
			case SDLK_r:
				player_set_dead(player);
				break;
			case SDLK_UP:
				player_set_current_way(player, NORTH);
				player_move(game);
				break;
			case SDLK_DOWN:
				player_set_current_way(player, SOUTH);
				player_move(game);
				break;
			case SDLK_RIGHT:
				player_set_current_way(player, EAST);
				player_move(game);
				break;
			case SDLK_LEFT:
				player_set_current_way(player, WEST);
				player_move(game);
				break;
			case SDLK_SPACE:
				if (player_get_nb_bomb(player) > 0 && map_get_cell_type(map, player_get_x(player), player_get_y(player)) != CELL_BOMB) {
					bomb_install(player,map);
					player_dec_nb_bomb(player);
				}
=======
			case SDLK_UP:
				player_set_current_way(player, NORTH);
				player_move(player, map);
				break;
			case SDLK_DOWN:
				player_set_current_way(player, SOUTH);
				player_move(player, map);
				break;
			case SDLK_RIGHT:
				player_set_current_way(player, EAST);
				player_move(player, map);
				break;
			case SDLK_LEFT:
				player_set_current_way(player, WEST);
				player_move(player, map);
				break;
			case SDLK_SPACE:
>>>>>>> 9cdb4d406aae54b9c6f500cb75d562a688f7bcb3
				break;
			default:
				break;
			}

			break;
		}
	}
	return 0;
}

<<<<<<< HEAD

int game_update(struct game* game) {
	if (input_keyboard(game) == 1)
		return 1; // exit game
=======
int game_update(struct game* game) {
	if (input_keyboard(game) == 1)
		return 1; // exit game

>>>>>>> 9cdb4d406aae54b9c6f500cb75d562a688f7bcb3
	return 0;
}
