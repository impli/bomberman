#ifndef CONSTANT_H_
#define CONSTANT_H_

#define WINDOW_NAME "[PG110] Bowser Jr. 2014"

// Size (# of pixels) of a cell of the map
#define SIZE_BLOC       40

#define MAP_1_1             "data/map_1_1.lvl"
#define MAP_1_2             "data/map_1_2.lvl"
#define MAP_1_3             "data/map_1_3.lvl"
#define MAP_2_1             "data/map_2_1.lvl"
#define MAP_2_2             "data/map_2_2.lvl"


// Size (# of pixels) of banner
#define LINE_HEIGHT			4
#define BANNER_HEIGHT		40

// Time management
#define DEFAULT_GAME_FPS 30

// map size
#define MAP_WIDTH 12
#define MAP_HEIGHT 12

typedef enum way {
	NORTH = 0,
	SOUTH, // 1
	WEST, // 2
	EAST //3
} way_t;

typedef enum state {
	STATE0 = 0,
	STATE1, // 1
	STATE2, // 2
	STATE3, // 3
	STATE4, // 4
	STATE5,
	STATE6,
	STATE7,
	STATE8,
	STATE9,
	STATE10
} state_t;

#endif /* CONSTANT */
