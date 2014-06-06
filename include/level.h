#ifndef LEVEL_H_
#define LEVEL_H_

#include <map.h>

struct level;

// return level number num
struct level*  level_get_level(int num);

// return current map of the level
struct map* level_get_curr_map(struct level* level);

<<<<<<< HEAD
void level_set_cur_map(struct level* level, int i);

=======
>>>>>>> 9cdb4d406aae54b9c6f500cb75d562a688f7bcb3
// return map number num of the level
struct map*  level_get_map(struct level* level, int num);

// free the level
void  level_free(struct level* level);

// display the level
void  level_display(struct level* level);

// free level struct
void   level_free(struct level* level);

<<<<<<< HEAD
int level_get_map_nb(struct level* level);

int level_get_lvl_nb(struct level* level);

=======
>>>>>>> 9cdb4d406aae54b9c6f500cb75d562a688f7bcb3
#endif /* LEVEL_H_ */
