#include "wolf3d.h"

void	wolf_render_image(ENGINE *wolf, IMAGE *image, SDL_Rect *rect)
{
	U32			offsetx;
	U32			offsety;
	U32			width;
	U32			height;
	U32			x;
	U32			y;

	x = 0;
	offsetx = ((rect) ? rect->x : 0);
	width = ((rect) ? rect->w : WINDOW_W);
	height = ((rect) ? rect->h : WINDOW_H);
	while (x < width)
	{
		offsety = ((rect) ? rect->y : 0);
		TEX_X = (double)image->width / width * x;
		y = 0;
		while (y < height)
		{
			TEX_Y = (double)image->height / height * y;
			if (image->pixels[TEX_Y * image->width + TEX_X] & 0xFF000000)
				SCREEN_PTR[(offsety + y) * WINDOW_W + x + offsetx] = image->pixels[TEX_Y * image->width + TEX_X];
			y++;
		}
		x++;
	}
}

void	render_bg(ENGINE *wolf)
{
	SDL_Rect	rect;
	U32			x;
	U32			y;

	rect.x = 0;
	rect.y = 0;
	rect.h = WINDOW_H / 2;
	rect.w = WINDOW_W;
	wolf_render_image(wolf, SKY, &rect);
	x = 0;
	while (x < WINDOW_W)
	{
		y = WINDOW_H / 2;
		while(y < WINDOW_H)
		{
			SCREEN_PTR[y * WINDOW_W + x] = 0x685A46;
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


	rect.w = WINDOW_W / 4;
	rect.h = WINDOW_H / 4;
	rect.y = WINDOW_H - rect.h;
	rect.x = WINDOW_W / 2 - rect.w / 2;
	wolf_render_image(wolf, GUN, &rect);
	
}

void	render_wolf(ENGINE *wolf)
{
	render_bg(wolf);
	render_walls(wolf);
	render_gun(wolf);
	SDL_UpdateWindowSurface(WINDOW);
}