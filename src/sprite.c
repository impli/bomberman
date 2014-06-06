#include <SDL/SDL_image.h>
#include <assert.h>

#include <sprite.h>
#include <misc.h>

// Sprites general
#define MAP_CASE        "sprite/wood_box.png"
#define MAP_KEY			"sprite/key.png"
#define MAP_DOOR		"sprite/door.png"
#define MAP_CLOSED_DOOR	"sprite/closed_door.png"

#define MAP_FLAG	"sprite/flag.png"
#define MAP_WOMAN	"sprite/bomberwoman.png"

#define MAP_NEXT	"sprite/next_level.png"
#define MAP_END		"sprite/the_end.png"

// Scenery elements
#define MAP_STONE		"sprite/stone.png"
#define MAP_TREE        "sprite/tree.png"

// Sprites of Banner
#define BANNER_LINE		"sprite/banner_line.png"
#define BANNER_LIFE		"sprite/banner_life.png"
#define BANNER_BOMB		"sprite/banner_bomb.png"
#define BANNER_RANGE	"sprite/banner_range.png"
#define BANNER_0		"sprite/banner_0.jpg"
#define BANNER_1		"sprite/banner_1.jpg"
#define BANNER_2		"sprite/banner_2.jpg"
#define BANNER_3		"sprite/banner_3.jpg"
#define BANNER_4		"sprite/banner_4.jpg"
#define BANNER_5		"sprite/banner_5.jpg"
#define BANNER_6		"sprite/banner_6.jpg"
#define BANNER_7		"sprite/banner_7.jpg"
#define BANNER_8		"sprite/banner_8.jpg"
#define BANNER_9		"sprite/banner_9.jpg"

#define GROUND	"sprite/ground.png"

// Sprite of pause
#define PAUSE		"sprite/pause.png"

// Sprites of Menu
#define MENU_UP		"sprite/menu1.png"
#define MENU_DOWN	"sprite/menu2.png"

// Sprites of Bombs
#define BOMB_TTL000		"sprite/explosion0.png"
#define BOMB_TTL00		"sprite/explosion1.png"
#define BOMB_TTL0		"sprite/explosion2.png"
#define BOMB_TTL1       "sprite/bomb1.png"
#define BOMB_TTL2       "sprite/bomb2.png"
#define BOMB_TTL3       "sprite/bomb3.png"
#define BOMB_TTL4       "sprite/bomb4.png"
#define BOMB_TTL5       "sprite/bomb5.png"
#define BOMB_TTL6       "sprite/bomb6.png"
#define BOMB_TTL7       "sprite/bomb7.png"
#define BOMB_TTL8       "sprite/bomb8.png"


// Sprites of Bonus
#define IMG_BONUS_BOMB_RANGE_INC  "sprite/bonus_bomb_range_inc.png"
#define IMG_BONUS_BOMB_RANGE_DEC  "sprite/bonus_bomb_range_dec.png"
#define IMG_BONUS_BOMB_NB_INC     "sprite/bonus_bomb_nb_inc.png"
#define IMG_BONUS_BOMB_NB_DEC     "sprite/bonus_bomb_nb_dec.png"

// Sprites of Players
#define PLAYER_LEFT     "sprite/player_left.png"
#define PLAYER_UP       "sprite/player_up.png"
#define PLAYER_RIGHT    "sprite/player_right.png"
#define PLAYER_DOWN     "sprite/player_down.png"

#define PLAYER_INV_LEFT     "sprite/player_inv_left.png"
#define PLAYER_INV_UP       "sprite/player_inv_up.png"
#define PLAYER_INV_RIGHT    "sprite/player_inv_right.png"
#define PLAYER_INV_DOWN     "sprite/player_inv_down.png"

// Sprites of Monsters
#define MONSTER_LEFT     "sprite/monster_left.png"
#define MONSTER_UP       "sprite/monster_up.png"
#define MONSTER_RIGHT    "sprite/monster_right.png"
#define MONSTER_DOWN     "sprite/monster_down.png"

// banner
SDL_Surface* numbers[10];
SDL_Surface* banner_life;
SDL_Surface* banner_bomb;
SDL_Surface* banner_range;
SDL_Surface* banner_line;

// pause
SDL_Surface* pause;

//menu
SDL_Surface* menu_up;
SDL_Surface* menu_down;

// map
SDL_Surface* box;
SDL_Surface* goal;
SDL_Surface* key;
SDL_Surface* door;
SDL_Surface* closed_door;
SDL_Surface* stone;
SDL_Surface* tree;
SDL_Surface* range_inc;
SDL_Surface* range_dec;
SDL_Surface* nb_inc;
SDL_Surface* nb_dec;
SDL_Surface* flag;
SDL_Surface* woman;
SDL_Surface* ground;

SDL_Surface* next;
SDL_Surface* end;

// player
SDL_Surface* player_img[4];

SDL_Surface* player_inv_img[4];

// monster
SDL_Surface* monster_img[4];

// bomb
SDL_Surface* bomb_img[11];

void pause_load() {
	pause = load_image(PAUSE);
}

void pause_unload() {
	SDL_FreeSurface(pause);
}

void menu_load(){
	menu_up = load_image(MENU_UP);
	menu_down = load_image(MENU_DOWN);
}

void menu_unload(){
	SDL_FreeSurface(menu_up);
	SDL_FreeSurface(menu_down);
}

void banner_load() {
	// numbers imgs
	numbers[0] = load_image(BANNER_0);
	numbers[1] = load_image(BANNER_1);
	numbers[2] = load_image(BANNER_2);
	numbers[3] = load_image(BANNER_3);
	numbers[4] = load_image(BANNER_4);
	numbers[5] = load_image(BANNER_5);
	numbers[6] = load_image(BANNER_6);
	numbers[7] = load_image(BANNER_7);
	numbers[8] = load_image(BANNER_8);
	numbers[9] = load_image(BANNER_9);

	// other banner sprites
	banner_life = load_image(BANNER_LIFE);
	banner_bomb = load_image(BANNER_BOMB);
	banner_range = load_image(BANNER_RANGE);
	banner_line = load_image(BANNER_LINE);
}

void banner_unload() {
	// numbers imgs
	for (int i = 0; i < 10; i++) {
		SDL_FreeSurface(numbers[i]);
	}

	// other banner sprites
	SDL_FreeSurface(banner_life);
	SDL_FreeSurface(banner_bomb);
	SDL_FreeSurface(banner_range);
	SDL_FreeSurface(banner_life);
}

void map_load() {
	// Sprite loading
	tree = load_image(MAP_TREE);
	box = load_image(MAP_CASE);
	key = load_image(MAP_KEY);
	stone = load_image(MAP_STONE);
	door = load_image(MAP_DOOR);
	closed_door = load_image(MAP_CLOSED_DOOR);
	range_inc = load_image(IMG_BONUS_BOMB_RANGE_INC);
	range_dec = load_image(IMG_BONUS_BOMB_RANGE_DEC);
	nb_inc = load_image(IMG_BONUS_BOMB_NB_INC);
	nb_dec = load_image(IMG_BONUS_BOMB_NB_DEC);
	flag = load_image(MAP_FLAG);
	woman = load_image(MAP_WOMAN);
	next = load_image(MAP_NEXT);
	end = load_image(MAP_END);
	ground = load_image(GROUND);
}

void map_unload() {
	SDL_FreeSurface(tree);
	SDL_FreeSurface(box);
	SDL_FreeSurface(goal);
	SDL_FreeSurface(key);
	SDL_FreeSurface(stone);
	SDL_FreeSurface(door);
	SDL_FreeSurface(closed_door);
	SDL_FreeSurface(range_inc);
	SDL_FreeSurface(range_dec);
	SDL_FreeSurface(nb_inc);
	SDL_FreeSurface(nb_dec);
	SDL_FreeSurface(flag);
	SDL_FreeSurface(woman);
	SDL_FreeSurface(next);
	SDL_FreeSurface(end);
	SDL_FreeSurface(ground);
}

void player_load() {
	player_img[WEST] = load_image(PLAYER_LEFT);
	player_img[EAST] = load_image(PLAYER_RIGHT);
	player_img[NORTH] = load_image(PLAYER_UP);
	player_img[SOUTH] = load_image(PLAYER_DOWN);
	player_inv_img[WEST] = load_image(PLAYER_INV_LEFT);
	player_inv_img[EAST] = load_image(PLAYER_INV_RIGHT);
	player_inv_img[NORTH] = load_image(PLAYER_INV_UP);
	player_inv_img[SOUTH] = load_image(PLAYER_INV_DOWN);
}

void monster_load() {
	monster_img[WEST] = load_image(MONSTER_LEFT);
	monster_img[EAST] = load_image(MONSTER_RIGHT);
	monster_img[NORTH] = load_image(MONSTER_UP);
	monster_img[SOUTH] = load_image(MONSTER_DOWN);
}

void bomb_load() {
	bomb_img[STATE0] = load_image(BOMB_TTL8);
	bomb_img[STATE1] = load_image(BOMB_TTL7);
	bomb_img[STATE2] = load_image(BOMB_TTL6);
	bomb_img[STATE3] = load_image(BOMB_TTL5);
	bomb_img[STATE4] = load_image(BOMB_TTL4);
	bomb_img[STATE5] = load_image(BOMB_TTL3);
	bomb_img[STATE6] = load_image(BOMB_TTL2);
	bomb_img[STATE7] = load_image(BOMB_TTL1);
	bomb_img[STATE8] = load_image(BOMB_TTL0);
	bomb_img[STATE9] = load_image(BOMB_TTL00);
	bomb_img[STATE10] = load_image(BOMB_TTL000);
}

void bomb_unload() {
	for (int i = 0; i < 11; i++)
		SDL_FreeSurface(bomb_img[i]);
}

void player_unload() {
	for (int i = 0; i < 4; i++){
		SDL_FreeSurface(player_img[i]);
		SDL_FreeSurface(player_inv_img[i]);
	}
}

void monster_unload() {
	for (int i = 0; i < 4; i++){
		SDL_FreeSurface(monster_img[i]);
	}
}

void sprite_load() {
	map_load();
	pause_load();
	menu_load();
	banner_load();
	player_load();
	monster_load();
	bomb_load();
}

void sprite_free() {
	map_unload();
	pause_unload();
	menu_unload();
	banner_unload();
	player_unload();
	monster_unload();
	bomb_unload();
}

SDL_Surface* sprite_get_number(short number) {
	assert(number >= 0 && number <= 9);
	return numbers[number];
}

SDL_Surface* sprite_get_player(enum way direction) {
	assert(player_img[direction]);
	return player_img[direction];
}

SDL_Surface* sprite_get_inv_player(enum way direction) {
	assert(player_inv_img[direction]);
	return player_inv_img[direction];
}

SDL_Surface* sprite_get_monster(enum way direction) {
	assert(monster_img[direction]);
	return monster_img[direction];
}

SDL_Surface* sprite_get_bomb(enum state state) {
	assert(bomb_img[state]);
	return bomb_img[state];
}

SDL_Surface* sprite_get_banner_life() {
	assert(banner_life);
	return banner_life;
}

SDL_Surface* sprite_get_banner_bomb() {
	assert(banner_bomb);
	return banner_bomb;
}

SDL_Surface* sprite_get_pause() {
	assert(pause);
	return pause;
}

SDL_Surface* sprite_get_menu(int n) {
	assert(menu_up && menu_down);
	if( n == 0 )
		return menu_up;
	else
		return menu_down;
}

SDL_Surface* sprite_get_next() {
	assert(next);
	return next;
}

SDL_Surface* sprite_get_end() {
	assert(end);
	return end;
}

SDL_Surface* sprite_get_ground(){
	assert(ground);
	return ground;
}

SDL_Surface* sprite_get_flag() {
	assert(flag);
	return flag;
}

SDL_Surface* sprite_get_woman() {
	assert(woman);
	return woman;
}

SDL_Surface* sprite_get_banner_line() {
	assert(banner_line);
	return banner_line;
}

SDL_Surface* sprite_get_banner_range() {
	assert(banner_range);
	return banner_range;
}

SDL_Surface* sprite_get_tree() {
	assert(tree);
	return tree;
}

SDL_Surface* sprite_get_box() {
	assert(box);
	return box;
}

SDL_Surface* sprite_get_key() {
	assert(key);
	return key;
}

SDL_Surface* sprite_get_stone() {
	assert(stone);
	return stone;
}

SDL_Surface* sprite_get_door() {
	assert(door);
	return door;
}

SDL_Surface* sprite_get_closed_door() {
	assert(closed_door);
	return closed_door;
}

SDL_Surface* sprite_get_range_inc() {
	assert(range_inc);
	return range_inc;
}

SDL_Surface* sprite_get_range_dec() {
	assert(range_dec);
	return range_dec;
}

SDL_Surface* sprite_get_nb_inc() {
	assert(nb_inc);
	return nb_inc;
}

SDL_Surface* sprite_get_nb_dec() {
	assert(nb_dec);
	return nb_dec;
}
