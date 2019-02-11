#include "wolf3d.h"

void	wolf_render_image(ENGINE *wolf, IMAGE *image, SDL_Rect *rect)
{
	U32	offset;
	U32	dx;
	U32	dy;
	U32	x;
	U32	y;

	x = 0;
	while (x < WINDOW_W)
	{
		dx = x * 256 - WINDOW_W * 128 + rect->w * 128;
		TEX_X = ((dx * image->width) / rect->w) / 256;
		y = 0;
		while (y < rect->h)
		{
			dy = y * 256 - WINDOW_H * 128 + rect->h * 128;
			TEX_Y = ((dy * image->height) / rect->h) / 256;
			SCREEN_PTR[rect->x * WINDOW_W + y] = image->pixels[IMAGE_W * TEX_X + TEX_Y];
			y++;
		}
		x++;
	}
}

void	render_bg(ENGINE *wolf)
{
	U32			x;
	U32			y;
	U32			dx;
	U32			dy;
	U32			size;

	x = 0;
	size = WINDOW_H * WINDOW_W;
	while (x < WINDOW_W)
	{
		y = 0;
		dx = x * 256 - WINDOW_W * 128 + WINDOW_W * 128;
		TEX_X = ((dx * LOGO->width) / WINDOW_W) / 256;

		while (y < WINDOW_H)
		{
			dy = y * 256 - WINDOW_H * 128 + WINDOW_H * 128;
			TEX_Y = ((dy * LOGO->height) / WINDOW_H) / 256;
			SCREEN_PTR[x * WINDOW_H + y] = LOGO->pixels[TEX_Y * LOGO->width + TEX_X];
			y++;
		}
		x++;
	}
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