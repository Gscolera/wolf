#include "wolf3d.h"

static void	fade_image(IMAGE *image, IMAGE *faded, U8 scale)
{
	U32	i;

	i = 0;
	while (i < image->length)
	{
		if (image->pixels[i] & 0xFFFFFF == 0xFFFFFF)
		{
			faded->pixels[i++] = (U32)(scale << 16 | scale << 8 | scale);
		}
		else
			faded->pixels[i++] = 0;
		ft_printf("%d\n", i);
	}

}

static void	fade_in(ENGINE *wolf, IMAGE *image)
{
	SDL_Rect		rect;
	IMAGE			faded;
	U8				scale;

	scale			= 0;
	faded.width		= IMAGE_W;
	faded.height	= IMAGE_H;
	faded.length	= IMAGE_L;
	faded.pixels	= (U32 *)malloc(sizeof(U32) * image->length);
	while (++scale < 255)
	{	
		rect.x	= (WINDOW_H - IMAGE_H) / 2;
		rect.y	= (WINDOW_W - IMAGE_W) / 2;
		fade_image(image, &faded, scale);
		wolf_render_image(wolf, &faded, &rect);
		SDL_UpdateWindowSurface(WINDOW);
		SDL_Delay(5);
	}
	free(faded.pixels);
}

static void	fade_out(ENGINE *wolf, IMAGE *image)
{
	SDL_Rect		rect;
	IMAGE			faded;
	U32				scale;

	scale			= 255;
	faded.width		= IMAGE_W;
	faded.height	= IMAGE_H;
	faded.length	= IMAGE_L;
	faded.pixels	= (U32 *)malloc(sizeof(U32) * image->length);
	while (--scale > 0)
	{
		rect.x	= (WINDOW_H - IMAGE_H) / 2;
		rect.y	= (WINDOW_W - IMAGE_W) / 2;
		fade_image(image, &faded, scale);
		wolf_render_image(wolf, &faded, &rect);
		SDL_UpdateWindowSurface(WINDOW);
		SDL_Delay(5);
	}
	free(faded.pixels);
}

void		show_intro(ENGINE *wolf)
{
	 fade_in(wolf, LOGO);
	 SDL_Delay(1000);
	 fade_out(wolf, LOGO);
	 free(LOGO->pixels);
	 free(LOGO);
}