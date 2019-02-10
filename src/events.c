#include "wolf3d.h"

static void	wolf_rotate(ENGINE *wolf)
{
	double	old_dir;
	double	old_plane;

	old_dir = DIR.x;
	old_plane = PLANE.x;
	MOUSEPX = MOUSEX;
	MOUSEX = wolf->event.motion.x;
	MOUSEDLT = (MOUSEX - MOUSEPX) * 0.01;
	DIR.x = DIR.x * cos(MOUSEDLT) - DIR.y * sin(MOUSEDLT);
	DIR.y = old_dir * sin(MOUSEDLT) + DIR.y * cos(MOUSEDLT);
	PLANE.x = PLANE.x * cos(MOUSEDLT) - PLANE.y * sin(MOUSEDLT);
	PLANE.y = old_plane * sin(MOUSEDLT) + PLANE.y * cos(MOUSEDLT);
}

static void	wolf_move(ENGINE *wolf, int key)
{
	MVSPEED = 0.06 * 3;
	if (key == SDLK_w)
	{
		if (BLOCK[(short)(POS.x + DIR.x * MVSPEED)][(short)POS.y] == 0)
			POS.x += DIR.x * MVSPEED;
		if (BLOCK[(short)(POS.x)][(short)(POS.y + DIR.y * MVSPEED)] == 0)
			POS.y += DIR.y * MVSPEED;
	}
	if (key == SDLK_s)
	{
		if (BLOCK[(short)(POS.x - DIR.x * MVSPEED)][(short)POS.y] == 0)
			POS.x -= DIR.x * MVSPEED;
		if (BLOCK[(short)(POS.x)][(short)(POS.y - DIR.y * MVSPEED)] == 0)
			POS.y -= DIR.y * MVSPEED;
	}
	if (key == SDLK_a)
	{
		if (BLOCK[(short)(POS.x - PLANE.x * MVSPEED)][(short)POS.y] == 0)
			POS.x -= PLANE.x * MVSPEED;
		if (BLOCK[(short)POS.x][(short)(POS.y - PLANE.y * MVSPEED)] == 0)
			POS.y -= PLANE.y * MVSPEED;
	}
	if (key == SDLK_d)
	{
		if (BLOCK[(short)(POS.x + PLANE.x * MVSPEED)][(short)POS.y] == 0)
			POS.x += PLANE.x * MVSPEED;
		if (BLOCK[(short)POS.x][(short)(POS.y + PLANE.y * MVSPEED)] == 0)
			POS.y += PLANE.y * MVSPEED;
	}
	
}

void	parse_events(ENGINE *wolf)
{
	SDL_PollEvent(&EVENT);
	if (ETYPE == SDL_QUIT || (ETYPE == SDL_KEYUP && KEY == SDLK_ESCAPE))
		wolf->power = false;
	else if (ETYPE == SDL_KEYDOWN)
		wolf_move(wolf, KEY);
	else if (ETYPE == SDL_MOUSEMOTION)
		wolf_rotate(wolf);
}