#include "wolf3d.h"

static void	init_engine(ENGINE *wolf)
{
	WINDOW		= NULL;
	SCREEN		= NULL;
	BLOCK		= NULL;
	LOGO 		= NULL;
	BGMUSIC		= NULL;
	SHOTSOUND	= NULL;
	VOLUME		= 50;
	MAP_W		= 0;
	MAP_H		= 0;
	PLANE.x 	= 0.0;
	PLANE.y 	= 0.66;
	POS.x 		= 5.0;
	POS.y 		= 3.0;
	DIR.x 		= 1.0;
	DIR.y 		= 0.0;
	MOUSE_STATE	= false;
	wolf->power = true;
}

static void	load_textures(ENGINE *wolf)
{
	LOGO	= read_tga("images/logo.tga");
	WALL[0]	= read_tga("images/bricks_01.tga");
	WALL[1]	= read_tga("images/text1.tga");
	WALL[2]	= read_tga("images/text2.tga");
	WALL[3]	= read_tga("images/text3.tga");
	GUN = read_tga("images/weapon.tga");

}

static void	load_sounds(ENGINE *wolf)
{
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	perror(Mix_GetError());

	BGMUSIC = Mix_LoadMUS("sounds/Klint - Diamond.mp3");
	perror(Mix_GetError());
	SHOTSOUND = Mix_LoadWAV("sounds/Gun+Shot2.wav");
	Mix_VolumeMusic(VOLUME);
	Mix_VolumeChunk(SHOTSOUND, 50);
	Mix_PlayMusic(BGMUSIC, -1);
	perror(Mix_GetError());
}

void		run_engine(ENGINE *wolf)
{
	init_engine(wolf);
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
		wolf->power = false;
	if (wolf->power)
	{
		if (!(WINDOW = SDL_CreateWindow("WOLF3D", 
								SDL_WINDOWPOS_CENTERED,
								SDL_WINDOWPOS_CENTERED,
								WINDOW_W, WINDOW_H,
								SDL_WINDOW_SHOWN)))
		wolf->power = false;
	}
	if (wolf->power)
	{
		if (!(SCREEN = SDL_GetWindowSurface(WINDOW)))
			wolf->power = false;
	}
	if (wolf->power)
		load_textures(wolf);
	if (wolf->power)
		load_sounds(wolf);
	SCREEN_PTR = SCREEN->pixels;
	SDL_ShowCursor(SDL_DISABLE);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_UpdateWindowSurface(WINDOW);
}