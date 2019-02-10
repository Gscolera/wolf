#ifndef WOLF3D_H
# define WOLF3D_h

# include <SDL2/SDL.h>
# include <SDL2/SDL_mixer.h>
# include "tga_reader.h"
# include <math.h>

# define ENGINE		t_engine
# define WINDOW_W	1200
# define WINDOW_H	800
# define FPS		60

/*
********************WINDOW DEFINITIONS***************************************
*/
# define STR_WINDOW	t_window
# define WINDOW		wolf->window.window
# define SCREEN		wolf->window.screen
# define SCREEN_PTR	wolf->window.ptr
/*
********************TEXTURE DEFINITIONS**************************************
*/
# define TEXTURE	t_texture
# define LOGO		wolf->texture.logo
# define WALL		wolf->texture.wall
# define BG			wolf->texture.bg
# define IMAGE_H	image->height
# define IMAGE_W	image->width
# define IMAGE_L	image->length
# define IMAGE_PTR	wolf->texture.ptr
# define TEXTURE_T	wolf->texture.type
# define COLHEIGHT	wolf->texture.colheight
# define DRAWSTART	wolf->texture.drawstart
# define DRAWEND	wolf->texture.drawend

/*
********************EVENT DEFINITIONS***************************************
*/
# define EVENT		wolf->event
# define ETYPE		wolf->event.type
# define KEY		wolf->event.key.keysym.sym
/*
********************MAP DEFINITIONS*****************************************
*/
# define MAP		t_map
# define BLOCK		wolf->map.block
# define MAP_W		wolf->map.width
# define MAP_H		wolf->map.height
# define MAP_X		wolf->map.x
# define MAP_Y		wolf->map.y
/*
***************SOUND DEFINITIONS***************************************
*/
# define SOUND		t_sound
# define BGMUSIC	wolf->sound.bgmusic
# define SHOTSOUND	wolf->sound.shot
# define VOLUME		wolf->sound.volume
/*
***************PLAYER DEFINITIONS***************************************
*/
# define PLAYER		t_player
# define COORDS		t_coords
# define POS		wolf->player.pos
# define DIR		wolf->player.dir
# define PLANE		wolf->player.plane
# define MVSPEED	wolf->player.mvspeed
# define RTSPEED	wolf->player.rtspeed
/*
***************RAY DEFINITIONS***************************************
*/
# define RAY			t_ray
# define HIT			wolf->ray.hit
# define CAMERA			wolf->ray.camera
# define RAYDIR			wolf->ray.dir
# define RAYDIST		wolf->ray.dist
# define RAYDELTA		wolf->ray.delta_dist
# define WALLDIST		wolf->ray.wall_dist
# define SIDE			wolf->ray.side
# define STEPX			wolf->ray.stepx
# define STEPY			wolf->ray.stepy
/*
***************MOUSE DEFINITIONS***************************************
*/
# define MOUSE			t_mouse
# define MOUSEX			wolf->mouse.newx
# define MOUSEPX		wolf->mouse.prevx
# define MOUSEDLT		wolf->mouse.delta

typedef	struct		s_mouse
{
	double			newx;
	double			prevx;
	double			delta;
}					t_mouse;

typedef struct		s_window
{
	SDL_Window		*window;
	SDL_Surface		*screen;
	U32				*ptr;
}					t_window;

typedef struct		s_sound
{
	Mix_Music		*bgmusic;
	Mix_Chunk		*shot;
	short			volume;
}					t_sound;

typedef	struct		s_coords
{
	double			x;
	double			y;
}					t_coords;

typedef struct		s_player
{
	COORDS			pos;
	COORDS			dir;
	COORDS			plane;
	double			mvspeed;	
	double			rtspeed;	
}					t_player;

typedef struct		s_ray
{
	COORDS			dir;
	COORDS			dist;
	COORDS			delta_dist;
	double			camera;
	double			wall_dist;
	short			stepx;
	short			stepy;
	_Bool			hit;
	_Bool			side;
}					t_ray;

typedef struct		s_map
{
	U8				**block;
	U32				width;
	U32				height;
	U32				x;
	U32				y;
}					t_map;

typedef struct		s_texture
{
	IMAGE			*logo;
	IMAGE			*wall;
	IMAGE			*bg;
	PIXEL			*ptr;
	U8				type;
	short			colheight;
	short			drawstart;
	short			drawend;
}					t_texture;

typedef struct		s_engine
{
	STR_WINDOW		window;
	SDL_Event		event;
	TEXTURE			texture;
	SOUND			sound;
	PLAYER			player;
	RAY				ray;
	MAP				map;
	MOUSE			mouse;
	bool			power;
	
}					t_engine;

void				run_engine(ENGINE *wolf);
void				stop_engine(ENGINE *wolf);
void				parse_events(ENGINE *wolf);
bool				read_map(ENGINE *wolf, char *path);
void				show_intro(ENGINE *wolf);
void				wolf_render_image(ENGINE *wolf, IMAGE *image, SDL_Rect *rect);
void				render_wolf(ENGINE *wolf);
void				ray_cast(ENGINE *wolf, U32 x);


#endif