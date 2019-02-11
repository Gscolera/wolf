#include "wolf3d.h"

static void	wolf_rotate(ENGINE *wolf)
{
	double	old_dir;
	double	old_plane;

	old_dir = DIR.x;
	old_plane = PLANE.x;
	MOUSEPX = MOUSEX;
	MOUSEX = wolf->event.motion.x;
	MOUSEDLT = (MOUSEX - MOUSEPX) * wolf->frame_time * 0.5;
	DIR.x = DIR.x * cos(MOUSEDLT) - DIR.y * sin(MOUSEDLT);
	DIR.y = old_dir * sin(MOUSEDLT) + DIR.y * cos(MOUSEDLT);
	PLANE.x = PLANE.x * cos(MOUSEDLT) - PLANE.y * sin(MOUSEDLT);
	PLANE.y = old_plane * sin(MOUSEDLT) + PLANE.y * cos(MOUSEDLT);

}

static void	wolf_move(ENGINE *wolf, int key)
{
	MVSPEED = wolf->frame_time * 5.0;
	
	CX = ((DIR.x > 0) ? 0.1 : -0.1);
	CY = ((DIR.y > 0) ? 0.1 : -0.1);
	ft_printf("DIRX %f DIRY %f PLANE %f\n", DIR.x, DIR.y, PLANE.x);

	if (key == SDLK_w)
	{
		if (!BLOCK[(short)(POS.x + DIR.x * MVSPEED + CX)][(short)POS.y])
			POS.x += DIR.x * MVSPEED;
		if (!BLOCK[(short)(POS.x)][(short)(POS.y + DIR.y * MVSPEED + CY)])
			POS.y += DIR.y * MVSPEED;
	}
	if (key == SDLK_s)
	{
		if (!BLOCK[(short)(POS.x - DIR.x * MVSPEED)][(short)POS.y])
			POS.x -= DIR.x * MVSPEED;
		if (BLOCK[(short)(POS.x)][(short)(POS.y - DIR.y * MVSPEED)])
			POS.y -= DIR.y * MVSPEED;
	}
	if (key == SDLK_a)
	{
		if (!BLOCK[(short)(POS.x - PLANE.x * MVSPEED)][(short)POS.y])
			POS.x -= PLANE.x * MVSPEED;
		if (!BLOCK[(short)POS.x][(short)(POS.y - PLANE.y * MVSPEED)])
			POS.y -= PLANE.y * MVSPEED;
	}
	if (key == SDLK_d)
	{
		if (!BLOCK[(short)(POS.x + PLANE.x * MVSPEED)][(short)POS.y])
			POS.x += PLANE.x * MVSPEED;
		if (!BLOCK[(short)POS.x][(short)(POS.y + PLANE.y * MVSPEED)])
			POS.y += PLANE.y * MVSPEED;
	}
	
}

static void	wolf_turn_mouse(ENGINE *wolf)
{
	if (MOUSE_STATE)
	{
		SDL_ShowCursor(SDL_DISABLE);
		SDL_SetRelativeMouseMode(SDL_TRUE);
		MOUSE_STATE = false;
	}
	else
	{
		SDL_ShowCursor(SDL_ENABLE);
		SDL_SetRelativeMouseMode(SDL_FALSE);
		MOUSE_STATE = true;
	}
}

void		parse_events(ENGINE *wolf)
{
	while (SDL_PollEvent(&EVENT))
	{
		if (ETYPE == SDL_QUIT || (ETYPE == SDL_KEYDOWN && KEY == SDLK_ESCAPE))
			wolf->power = false;
		if (ETYPE == SDL_KEYDOWN)
			wolf_move(wolf, KEY);
		if (ETYPE == SDL_MOUSEMOTION && !MOUSE_STATE)
			wolf_rotate(wolf);
		if (ETYPE == SDL_KEYDOWN && KEY == SDLK_p)
			!Mix_PausedMusic() ? Mix_PauseMusic() : Mix_ResumeMusic();
		if (ETYPE == SDL_KEYDOWN && KEY == SDLK_TAB)
			wolf_turn_mouse(wolf);
	}
}