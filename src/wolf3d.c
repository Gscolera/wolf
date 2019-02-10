#include "wolf3d.h"

int		main(int argc, char **argv)
{
	ENGINE	wolf;
	double	start;
	double	finish;
	double	frame_time;

	run_engine(&wolf);
	read_map(&wolf, (argc > 1) ? argv[1] : "maps/level0");
	//show_intro(&wolf);
	while(wolf.power)
	{
		start = SDL_GetTicks();
		render_wolf(&wolf);
		parse_events(&wolf);
		finish = SDL_GetTicks();
		frame_time = finish - start;
		if (frame_time < 6)
			SDL_Delay(6 - frame_time);
	}
	stop_engine(&wolf);
	exit(0);
}