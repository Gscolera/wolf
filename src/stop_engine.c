#include "wolf3d.h"

static void	stop_sounds(ENGINE *wolf)
{
	Mix_HaltChannel(-1);
	if (BGMUSIC)
		Mix_FreeMusic(BGMUSIC);
	if (SHOTSOUND)
		Mix_FreeChunk(SHOTSOUND);
}

static void	free_textures(ENGINE *wolf)
{
	int i;

	i = 4;
	while (i--)
	{
		free(WALL[i]->pixels);
		free(WALL[i]);
	}
	free(GUN->pixels);
	free(GUN);
	free(SKY->pixels);
	free(SKY);
	free(GRASS->pixels);
	free(GRASS);
}

void		stop_engine(ENGINE *wolf)
{
	
	
	free_textures(wolf);
	if (BLOCK)
	{
		while (MAP_H-- > 0)
			free(BLOCK[MAP_H]);
		free(BLOCK);
	}
	stop_sounds(wolf);
	SDL_DestroyWindow(WINDOW);
	SDL_Quit();
}