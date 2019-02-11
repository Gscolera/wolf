#include "wolf3d.h"

U32		get_pix(PIXEL pixel)
{

	return((U32)pixel.a << 24 | pixel.r << 16 | pixel.g << 8 | pixel.b);
}

void	wolf_render_image(ENGINE *wolf, IMAGE *image, SDL_Rect *rect)
{
	U32	offset;
	U32 color;
	
	offset = rect->y;
	IMAGE_PTR = image->pixels;
	while (rect->x < rect->h)
	{
		rect->y = offset;
		while (rect->y < rect->w)
		{	
			color = get_pix(*(IMAGE_PTR++));
			if (color & 0xFF000000)
				SCREEN_PTR[rect->y + rect->x * WINDOW_W] = color;
			rect->y++;
		}
		rect->x++;
	}
}

void	render_bg(ENGINE *wolf)
{
	U32			i;
	U32			size;

	i = 0;
	
	size = WINDOW_H * WINDOW_W;
	while (i < size)
	{
		if (i * 2 < size)
			SCREEN_PTR[i++] = 0x000033;
		else
			SCREEN_PTR[i++] = 0x330d00;
	}
	
	
}


void	render_walls(ENGINE *wolf)
{
	U32 y;
	double wallx;
	Uint32 color;

	IMAGE	*current;
	
	
	y = 0;
	
	SCREEN_PTR = SCREEN->pixels;
	while (y < WINDOW_W)
	{
		ray_cast(wolf, y);
		if (SIDE == 0 || SIDE == 1)
			wallx = POS.y + WALLDIST * RAYDIR.y;
		else
			wallx = POS.x + WALLDIST * RAYDIR.x;
		wallx -= (int)(wallx);
		int texX = (int)(wallx * (double)(WALL[SIDE]->width));
      	if((SIDE == 0 || SIDE == 1) && RAYDIR.x > 0) 
		  texX = WALL[SIDE]->width - texX - 1;
      	if((SIDE == 2 || SIDE == 3) &&  RAYDIR.y < 0)
		  texX = WALL[SIDE]->width - texX - 1;

		while (DRAWSTART < DRAWEND)
		{
			int d = DRAWSTART * 256 - WINDOW_H * 128 + COLHEIGHT * 128;
			int texY = ((d * WALL[SIDE]->height) / COLHEIGHT) / 256;
			color = get_pix(WALL[SIDE]->pixels[WALL[SIDE]->width * texY + texX]);
			SCREEN_PTR[WINDOW_W * DRAWSTART + y] = color;
			DRAWSTART++;
		}
		y++;
	}

}

void	render_gun(ENGINE *wolf)
{
	SDL_Rect rect;
	
	rect.x = WINDOW_H - GUN->height;
	rect.y =  (WINDOW_W - GUN->height) / 2;
	rect.h	= GUN->height + rect.x;
	rect.w	= GUN->width + rect.y;
	wolf_render_image(wolf, GUN, &rect);

}

void	render_wolf(ENGINE *wolf)
{
	render_bg(wolf);
	render_walls(wolf);
	render_gun(wolf);
	SDL_UpdateWindowSurface(WINDOW);
}