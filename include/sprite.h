#ifndef SPRITE_H_
#define SPRITE_H_

#include <SDL/SDL.h>
#include <map.h>
#include <constant.h>

// load game's sprites
void		 sprite_load();

SDL_Surface* sprite_get_player(way_t direction);
<<<<<<< HEAD
SDL_Surface* sprite_get_inv_player(way_t direction);
SDL_Surface* sprite_get_monster(way_t direction);
SDL_Surface* sprite_get_bomb(state_t state);
=======
SDL_Surface* sprite_get_bonus(bonus_type_t bonus_type);
>>>>>>> 9cdb4d406aae54b9c6f500cb75d562a688f7bcb3
SDL_Surface* sprite_get_tree();
SDL_Surface* sprite_get_box();
SDL_Surface* sprite_get_key();
SDL_Surface* sprite_get_stone();
SDL_Surface* sprite_get_door();
SDL_Surface* sprite_get_closed_door();
<<<<<<< HEAD
SDL_Surface* sprite_get_range_inc();
SDL_Surface* sprite_get_range_dec();
SDL_Surface* sprite_get_nb_inc();
SDL_Surface* sprite_get_nb_dec();
SDL_Surface* sprite_get_flag();
SDL_Surface* sprite_get_peach();
SDL_Surface* sprite_get_next();
SDL_Surface* sprite_get_end();
SDL_Surface* sprite_get_ground();

=======
>>>>>>> 9cdb4d406aae54b9c6f500cb75d562a688f7bcb3

SDL_Surface* sprite_get_number(short number);
SDL_Surface* sprite_get_banner_life();
SDL_Surface* sprite_get_banner_bomb();
SDL_Surface* sprite_get_banner_line();
SDL_Surface* sprite_get_banner_range();
<<<<<<< HEAD
SDL_Surface* sprite_get_pause();
SDL_Surface* sprite_get_menu(int n);
=======
>>>>>>> 9cdb4d406aae54b9c6f500cb75d562a688f7bcb3

#endif /* SPRITE_H_ */
