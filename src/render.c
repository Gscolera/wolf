#include "wolf3d.h"

U32		get_pix(PIXEL pixel)
{
	return(pixel.r << 16 | pixel.g << 8 | pixel.b);
}

void	wolf_render_image(ENGINE *wolf, IMAGE *image, SDL_Rect *rect)
{
	U32	offset;
	
	offset = rect->y;
	IMAGE_PTR = image->pixels;
	while (rect->x < rect->h)
	{
		rect->y = offset;
		while (rect->y < rect->w)
		{	
			SCREEN_PTR[rect->y + rect->x * WINDOW_W] = get_pix(*(IMAGE_PTR++));;
			rect->y++;
		}
		rect->x++;
	}
}

void	render_bg(ENGINE *wolf)
{
	U32	i;
	U32	size;

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
	
	y = 0;
	while (y < WINDOW_W)
	{
		ray_cast(wolf, y);
		y++;
	}
}

void	render_wolf(ENGINE *wolf)
{
	render_bg(wolf);
	render_walls(wolf);
	SDL_UpdateWindowSurface(WINDOW);
}