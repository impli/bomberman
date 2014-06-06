#include <SDL/SDL_image.h>
#include <assert.h>
#include <stdio.h>
<<<<<<< HEAD
#include <stdlib.h>
#include <time.h>

#include <bomb.h>
#include <map.h>
#include <constant.h>
#include <list.h>
#include <monster.h>
=======
#include <time.h>

#include <map.h>
#include <constant.h>
>>>>>>> 9cdb4d406aae54b9c6f500cb75d562a688f7bcb3
#include <misc.h>
#include <sprite.h>
#include <window.h>

struct map {
	int width;
	int height;
	char* grid;
<<<<<<< HEAD
	struct list* bomb_list;
	struct list* monster_list;
=======
>>>>>>> 9cdb4d406aae54b9c6f500cb75d562a688f7bcb3
};

#define CELL(i,j) (i +  map->width * j)

struct map* map_new(int width, int height)
{
	assert(width > 0 && height > 0);

	struct map* map = malloc(sizeof *map);
	if (map == NULL )
		error("map_new : malloc map failed");

	map->width = width;
	map->height = height;

	map->grid = malloc(height * width);
	if (map->grid == NULL) {
		error("map_new : malloc grid failed");
	}

<<<<<<< HEAD
	map->bomb_list = list_new();
	map->monster_list = list_new();

=======
>>>>>>> 9cdb4d406aae54b9c6f500cb75d562a688f7bcb3
	// Grid cleaning
	int i, j;
	for (i = 0; i < width; i++)
		for (j = 0; j < height; j++)
			map->grid[CELL(i,j)] = CELL_EMPTY;

	return map;
}

int map_is_inside(struct map* map, int x, int y)
{
	assert(map);
<<<<<<< HEAD
	if ( 0<=x && x<=(map_get_width(map)-1) && 0<=y && y<=(map_get_height(map)-1) )
		return 1;
	return 0;
=======
	return 1;
>>>>>>> 9cdb4d406aae54b9c6f500cb75d562a688f7bcb3
}

void map_free(struct map* map)
{
	if (map == NULL )
		return;
<<<<<<< HEAD
	map->bomb_list=list_delete(map->bomb_list);
	map->monster_list = list_delete(map->monster_list);
=======
>>>>>>> 9cdb4d406aae54b9c6f500cb75d562a688f7bcb3
	free(map->grid);
	free(map);
}

int map_get_width(struct map* map)
{
	assert(map != NULL);
	return map->width;
}

int map_get_height(struct map* map)
{
	assert(map);
	return map->height;
}

enum cell_type map_get_cell_type(struct map* map, int x, int y)
{
	assert(map && map_is_inside(map, x, y));
	return map->grid[CELL(x,y)] & 15;
}

<<<<<<< HEAD
enum cell_type map_get_cell(struct map* map, int x, int y)
{
	assert(map && map_is_inside(map, x, y));
	return map->grid[CELL(x,y)];
}

unsigned char map_get_true_cell(struct map* map, int x, int y)
{
	assert(map && map_is_inside(map, x, y));
	return map->grid[CELL(x,y)];
}

enum cell_type map_get_cell_bonus_type(struct map* map, int x, int y)
{
	assert(map && map_is_inside(map, x, y));
	return map->grid[CELL(x,y)] >> 4;
}

enum cell_type map_get_cell_door_type(struct map* map, int x, int y)
{
	assert(map && map_is_inside(map, x, y));
	return map->grid[CELL(x,y)] >> 7;
}

void map_set_opened_door(struct map* map, int x, int y)
{
	assert(map && map_is_inside(map, x, y));
	map->grid[CELL(x,y)] = map->grid[CELL(x,y)] | (OPENED_DOOR << 7);
}


int map_get_door_number(struct map* map, int x, int y)
{
	assert(map && map_is_inside(map, x, y));
	return ((map->grid[CELL(x,y)] & 112) >> 4);
}

int map_get_goal_type(struct map* map, int x, int y)
{
	assert(map && map_is_inside(map, x, y));
	return ((map->grid[CELL(x,y)]) >> 4);
}

=======
>>>>>>> 9cdb4d406aae54b9c6f500cb75d562a688f7bcb3
void map_set_cell_type(struct map* map, int x, int y, enum cell_type type)
{
	assert(map && map_is_inside(map, x, y));
	map->grid[CELL(x,y)] = type;
}

<<<<<<< HEAD
struct list* map_get_bombs(struct map* map)
{
	assert(map);
	return map->bomb_list;
}

void map_set_bombs(struct map* map, struct list* l_bomb)
{
	assert(map);
	map->bomb_list = l_bomb;
}

void map_insert_bomb(struct map* map, int x, int y, void* data)
{
	map->bomb_list = list_insert_tail(map->bomb_list, x, y, data);
}

struct list* map_get_monsters(struct map* map)
{
	assert(map);
	return map->monster_list;
}

void map_set_monsters(struct map* map, struct list* l_monster)
{
	assert(map);
	map->monster_list = l_monster;
}

void map_insert_monster(struct map* map, int x, int y, void* data)
{
	map->monster_list = list_insert_tail(map->monster_list, x, y, data);
}


void map_case_explosion(struct map* map, int x, int y)
{
	assert(map && map_is_inside(map, x, y));

	int r = rand()%(99);	// Picks a random number between 0 and 99

	if(0 <= r && r < 30)
		map_set_cell_type(map, x, y, CELL_EMPTY);
	else if( 30 <= r && r < 35 )	{
		map_set_cell_type(map, x, y, CELL_EMPTY);
		monster_init(map, x, y);
	}
	else if( 35 <= r && r < 40 )
		map_set_cell_type(map, x, y, (CELL_BONUS|(LIFE << 4)));
	else if( 40 <= r && r < 55 )
		map_set_cell_type(map, x, y, (CELL_BONUS|(RANGE_INC << 4)));
	else if( 55 <= r && r < 70 )
		map_set_cell_type(map, x, y, (CELL_BONUS|(RANGE_DEC << 4)));
	else if( 70 <= r && r < 85 )
		map_set_cell_type(map, x, y, (CELL_BONUS|(NB_INC << 4)));
	else if( 85 <= r && r < 100 )
		map_set_cell_type(map, x, y, (CELL_BONUS|(NB_DEC << 4)));
}


=======
>>>>>>> 9cdb4d406aae54b9c6f500cb75d562a688f7bcb3
void display_bonus(struct map* map, int x, int y, char type)
{
	// bonus is encoded with the 4 most significant bits
	switch (type >> 4) {
<<<<<<< HEAD
	case RANGE_INC:
		window_display_image(sprite_get_range_inc(), x, y);
		break;

	case RANGE_DEC:
		window_display_image(sprite_get_range_dec(), x, y);
		break;

	case NB_INC:
		window_display_image(sprite_get_nb_inc(), x, y);
		break;

	case NB_DEC:
		window_display_image(sprite_get_nb_dec(), x, y);
		break;
	case LIFE :
		window_display_image(sprite_get_banner_life(), x, y);
=======
	case BONUS_BOMB_RANGE_INC:
		window_display_image(sprite_get_bonus(BONUS_BOMB_RANGE_INC), x, y);
		break;

	case BONUS_BOMB_RANGE_DEC:
		window_display_image(sprite_get_bonus(BONUS_BOMB_RANGE_DEC), x, y);
		break;

	case BONUS_BOMB_NB_INC:
		window_display_image(sprite_get_bonus(BONUS_BOMB_NB_INC), x, y);
		break;

	case BONUS_BOMB_NB_DEC:
		window_display_image(sprite_get_bonus(BONUS_BOMB_RANGE_DEC), x, y);
>>>>>>> 9cdb4d406aae54b9c6f500cb75d562a688f7bcb3
		break;
	}
}

void display_scenery(struct map* map, int x, int  y, char type)
{
	switch (type >> 4) { // sub-types are encoded with the 4 most significant bits
	case SCENERY_STONE:
		window_display_image(sprite_get_stone(), x, y);
		break;

	case SCENERY_TREE:
		window_display_image(sprite_get_tree(), x, y);
		break;
	}
}

<<<<<<< HEAD
void display_goal(struct map* map, int x, int  y, char type)
{
	switch (type >> 4) { // sub-types are encoded with the 4 most significant bits
	case FLAG:
		window_display_image(sprite_get_flag(), x, y);
		break;

	case WOMAN:
		window_display_image(sprite_get_woman(), x, y);
		break;
	}
}

void display_door(struct map* map, int x, int  y, char type)
{
	switch (type >> 7) { // sub-types are encoded with the 4 most significant bits
	case CLOSED_DOOR:
		window_display_image(sprite_get_closed_door(), x, y);
		break;

	default:
		window_display_image(sprite_get_door(), x, y);
		break;
	}
}

=======
>>>>>>> 9cdb4d406aae54b9c6f500cb75d562a688f7bcb3
void map_display(struct map* map)
{
	assert(map != NULL);
	assert(map->height > 0 && map->width > 0);

	int x, y;
	for (int i = 0; i < map->width; i++) {
		for (int j = 0; j < map->height; j++) {
			x = i * SIZE_BLOC;
			y = j * SIZE_BLOC;

			char type = map->grid[CELL(i,j)];

			switch (type & 15) { // type is encoded with 4 bits, 15 (1111) is a mask to keep the four less significant bits
			case CELL_SCENERY:
				display_scenery(map, x, y, type);
				break;
			case CELL_CASE:
				window_display_image(sprite_get_box(), x, y);
				break;
			case CELL_BONUS:
				display_bonus(map, x, y, type);
				break;
			case CELL_KEY:
				window_display_image(sprite_get_key(), x, y);
				break;
<<<<<<< HEAD
			case CELL_GOAL:
				display_goal(map, x, y, type);
				break;
			case CELL_DOOR:
				display_door(map, x, y, type);
				break;
			}
		}
	}
}

struct map* map_load_from_file(char* data) {
	int width, height;
	FILE *file = fopen(data, "r");

	fscanf(file, "%d:%d\n", &width, &height);

	struct map* map = map_new(width, height);

	int type=0;

	for (int i = 0; i < height-1; i++) {
		for (int j = 0; j < width-1; j++) {
			fscanf(file, "%d ", &type);
			map_set_cell_type(map, j, i, type);
		}
		fscanf(file, "%d\n", &type);
		map_set_cell_type(map, width-1, i, type);
	}

	for(int j = 0; j < width-1; j++){
		fscanf(file, "%d ", &type);
		map_set_cell_type(map, j, height-1, type);
	}
	fscanf(file, "%d", &type);
	map_set_cell_type(map, width-1, height-1, type);
	fclose(file);

	monster_from_map(map);
=======
			case CELL_DOOR:
				window_display_image(sprite_get_door(), x, y);
				break;
			case CELL_CLOSED_DOOR:
				window_display_image(sprite_get_closed_door(), x, y);
				break;
			}
		}

	}
}

struct map* map_get_default(void)
{
	struct map* map = map_new(MAP_WIDTH, MAP_HEIGHT);

	char themap[MAP_WIDTH * MAP_HEIGHT] = {
			CELL_PLAYER, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY,
			CELL_STONE, CELL_STONE, CELL_STONE, CELL_EMPTY, CELL_STONE, CELL_EMPTY, CELL_STONE, CELL_STONE, CELL_STONE, CELL_STONE, CELL_EMPTY, CELL_EMPTY,
			CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_STONE, CELL_CASE, CELL_STONE, CELL_EMPTY, CELL_EMPTY, CELL_STONE, CELL_EMPTY, CELL_EMPTY,
			CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_STONE, CELL_CASE, CELL_STONE, CELL_EMPTY, CELL_EMPTY, CELL_STONE, CELL_EMPTY, CELL_EMPTY,
			CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_STONE, CELL_CASE, CELL_STONE, CELL_EMPTY, CELL_EMPTY, CELL_STONE, CELL_EMPTY, CELL_EMPTY,
			CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_STONE, CELL_STONE, CELL_STONE, CELL_EMPTY, CELL_EMPTY, CELL_STONE, CELL_EMPTY, CELL_EMPTY,
			CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY , CELL_EMPTY, CELL_EMPTY, CELL_STONE,  CELL_EMPTY, CELL_EMPTY,
			CELL_EMPTY, CELL_TREE, CELL_CASE, CELL_TREE, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY,  CELL_EMPTY, CELL_STONE,  CELL_EMPTY, CELL_EMPTY,
			CELL_EMPTY, CELL_TREE, CELL_TREE, CELL_TREE, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY,  CELL_STONE,  CELL_EMPTY, CELL_EMPTY,
			CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_STONE,  CELL_EMPTY, CELL_EMPTY,
			CELL_CASE, CELL_STONE, CELL_STONE, CELL_STONE, CELL_STONE, CELL_STONE, CELL_STONE, CELL_STONE, CELL_STONE, CELL_STONE,  CELL_CASE_LIFE, CELL_EMPTY,
			CELL_MONSTER,  CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_MONSTER
		};

	for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++)
		map->grid[i] = themap[i];

>>>>>>> 9cdb4d406aae54b9c6f500cb75d562a688f7bcb3
	return map;
}
