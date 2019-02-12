#include "wolf3d.h"

void	wolf_render_image(ENGINE *wolf, IMAGE *image, SDL_Rect *rect)
{
	U32			x;
	U32			y;

	x = 0;
	while (x < WINDOW_W)
	{
		y = 0;
		TEX_X = (double)image->width / WINDOW_W * x;
		while (y < WINDOW_H)
		{
			TEX_Y = (double)image->height / WINDOW_H * y;
			SCREEN_PTR[y * WINDOW_W + x] = image->pixels[TEX_Y * image->width + TEX_X];
			y++;
		}
		x++;
	}
}

void	render_bg(ENGINE *wolf)
{
	wolf_render_image(wolf, SKY, NULL);
}

void	render_walls(ENGINE *wolf)
{
	U32 y;
	U32	d;
	Uint32 color;
	
	y = 0;
	SCREEN_PTR = SCREEN->pixels;
	while (y < WINDOW_W)
	{
		ray_cast(wolf, y);
		TEX_X = (int)(WALL_X * (double)(WALL[SIDE]->width));
      	if((SIDE == 0 || SIDE == 1) && RAYDIR.x > 0) 
		  TEX_X = WALL[SIDE]->width - TEX_X - 1;
      	if((SIDE == 2 || SIDE == 3) &&  RAYDIR.y < 0)
		  TEX_X = WALL[SIDE]->width - TEX_X - 1;
		while (DRAWSTART < DRAWEND)
		{
			d = DRAWSTART * 256 - WINDOW_H * 128 + COLHEIGHT * 128;
			TEX_Y = ((d * WALL[SIDE]->height) / COLHEIGHT) / 256;
			color = WALL[SIDE]->pixels[WALL[SIDE]->width * TEX_Y + TEX_X];
			SCREEN_PTR[WINDOW_W * DRAWSTART + y] = color;
			DRAWSTART++;
		}
		y++;
	}
}

void	render_gun(ENGINE *wolf)
{
	SDL_Rect rect;


	rect.w = WINDOW_W / 5;;
	rect.h = WINDOW_H / 5;
	rect.y = WINDOW_H - rect.h;
	rect.x = WINDOW_W / 2 - rect.w / 2;
	wolf_render_image(wolf, GUN, &rect);
	
}

void	render_wolf(ENGINE *wolf)
{
	render_bg(wolf);
	//render_walls(wolf);
	//render_gun(wolf);
	SDL_UpdateWindowSurface(WINDOW);
}