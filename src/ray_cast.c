# include "wolf3d.h"

static void	set_ray(ENGINE *wolf, U32 x)
{
	HIT = 0;
	CAMERA = 2 * x / (double)WINDOW_W - 1;
	RAYDIR.x = DIR.x + PLANE.x * CAMERA;
	RAYDIR.y = DIR.y + PLANE.y * CAMERA;
	MAP_X = (U32)POS.x;
	MAP_Y = (U32)POS.y;
	RAYDELTA.x = sqrt(1 + (RAYDIR.y * RAYDIR.y) / (RAYDIR.x * RAYDIR.x));
	RAYDELTA.y = sqrt(1 + (RAYDIR.x * RAYDIR.x) / (RAYDIR.y * RAYDIR.y));
}

static void	get_step(ENGINE *wolf)
{
	if (RAYDIR.x < 0)
	{
		STEPX = -1;
		RAYDIST.x = (POS.x - MAP_X) * RAYDELTA.x;
	}
	else
	{
		STEPX = 1;
		RAYDIST.x = (MAP_X + 1.0 - POS.x) * RAYDELTA.x;
	}
	if (RAYDIR.y < 0)
	{
		STEPY = -1;
		RAYDIST.y = (POS.y - MAP_Y) * RAYDELTA.y;
	}
	else
	{
		STEPY = 1;
		RAYDIST.y = (MAP_Y + 1.0 - POS.y) * RAYDELTA.y;
	}
}

static void	get_hit(ENGINE *wolf)
{
	while(HIT == 0)
	{
		if (RAYDIST.x < RAYDIST.y)
		{
			RAYDIST.x += RAYDELTA.x;
			MAP_X += STEPX;
			SIDE = ((DIR.x > 0 && DIR.y > 0) ? 1 : 0);
		}
		else
		{
			RAYDIST.y += RAYDELTA.y;
			MAP_Y += STEPY;
			SIDE = ((DIR.y > 0 && DIR.x > 0) ? 2 : 3);
		
		}
		if (BLOCK[MAP_X][MAP_Y] > 0)
			HIT = 1;
	}
}

static void	get_lines_height(ENGINE *wolf)
{
	if (SIDE == 0 || SIDE == 1)
		WALLDIST = (MAP_X - POS.x + (1 - STEPX) / 2) / RAYDIR.x;
	else
		WALLDIST = (MAP_Y - POS.y + (1 - STEPY) / 2) / RAYDIR.y;
	COLHEIGHT = (U32)(WINDOW_H / WALLDIST);
	DRAWSTART = -COLHEIGHT / 2 + WINDOW_H / 2;
	if (DRAWSTART < 0)
		DRAWSTART = 0;
	DRAWEND = COLHEIGHT / 2 + WINDOW_H / 2;
	if (DRAWEND >= WINDOW_H)
		DRAWEND = WINDOW_H - 1;

}

void		ray_cast(ENGINE *wolf, U32 x)
{
	set_ray(wolf, x);
	get_step(wolf);
	get_hit(wolf);
	get_lines_height(wolf);
	if (BLOCK[MAP_X][MAP_Y] == 1)
		TEXTURE_T = 1;
	else if (BLOCK[MAP_X][MAP_Y] == 2)
		TEXTURE_T = 2;
}