#ifndef TGA_READER_H
# define TGA_READER_H

# include <stdbool.h>
# include <fcntl.h>
# include <sys/stat.h>
# include "ft_printf.h"

# define TGA			t_tga
# define IMAGE			t_image


typedef unsigned int 	U32;
typedef unsigned char 	U8;


typedef struct			s_image
{
	U32					width;
	U32					height;
	U32					length;
	U32					*pixels;
}						t_image;

typedef struct			s_tga
{
	U32					size;
	U8					data_type;
	U8					*data;
	U8					*ptr;
	IMAGE				*image;
}						t_tga;

IMAGE					*read_tga(char *path);
bool					get_tga_info(char *path);
/*
******************ERRORS*******************************************************
*/
bool					open_error(char *path);
bool					mem_error(TGA *tga);
bool					unsupported_error(TGA *tga);


#endif