#include "wolf3d.h"

U32		get_pixel(PIXEL pixel)
{
	return(pixel.r << 16 | pixel.g << 8 | pixel.b);
}

int		main(int argc, char **argv)
{
	ENGINE	wolf;
	double	start;
	double	finish;
	double	frame_time;

	run_engine(&wolf);
	get_tga_info("images/gun.tga");
	read_map(&wolf, (argc > 1) ? argv[1] : "maps/level0");
	//show_intro(&wolf);
	while(wolf.power)
	{
		start = SDL_GetTicks();
		render_wolf(&wolf);
		 parse_events(&wolf);
		finish = SDL_GetTicks();
		frame_time = finish - start;
		if (frame_time < 1000 / FPS)
			SDL_Delay(1000 / FPS - finish + start);
		wolf.frame_time = (SDL_GetTicks() - start) / 1000;
	}
	stop_engine(&wolf);
	exit(0);
}