#include <assert.h>
#include <time.h>

#include <game.h>
#include <misc.h>
#include <map.h>
#include <level.h>
#include <window.h>
#include <sprite.h>

int menu_display(struct game* game){
	int i = 0;
	int opt=0;
	SDL_Event event;
	while( i == 0 ){
		window_display_image(sprite_get_menu(opt),0,0);
		window_refresh();
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				return 1;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					return 1;
				case SDLK_UP:
					opt=0;
					break;
				case SDLK_DOWN:
					opt=1;
					break;
				case SDLK_RETURN:
					i=1;
					break;
				case SDLK_KP_ENTER:
					i=1;
					break;
				default :
					break;
				}
				break;
			}
		}
	}
	return 0;
}
