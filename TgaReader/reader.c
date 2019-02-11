#include "tga_reader.h"

static bool		read_file(TGA *tga, char *path)
{
	struct stat st;
	int			fd;

	if (lstat(path, &st) == -1)
		return (open_error(path));
	tga->size = st.st_size;
	if (!(tga->data = (U8 *)malloc(tga->size)))
		return (mem_error(tga));
	if (!(tga->image = (IMAGE *)malloc(sizeof(IMAGE))))
		return (mem_error(tga));
	fd = open(path, O_RDONLY);
	read(fd, tga->data, tga->size);
	tga->ptr = tga->data;
	close(fd);
	return (1);
}

static bool	read_image_info(TGA *tga)
{
	U32	id_length;

	id_length 				= tga->ptr[0];
	tga->image->width 		= (tga->ptr[12] | tga->ptr[13] << 8);
	tga->image->height 		= (tga->ptr[14] | tga->ptr[15] << 8);
	tga->ptr 				+= 18 + id_length;
	tga->image->length 		= tga->image->width * tga->image->height;
	if (!(tga->image->pixels = (U32 *)malloc(sizeof(U32) * tga->image->length)))
		return (mem_error(tga));
	return (1);
}

static U32	get_pix_values(TGA *tga)
{
	
	return (tga->ptr[3] << 24 | tga->ptr[2] << 16 
					| tga->ptr[1] << 8 | tga->ptr[0]);
}

static void	read_data(TGA *tga)
{
	U32		i;
	U32		length;
	bool	type;
	
	i = 0;
	while(i < tga->image->length)
	{
		type 	= *tga->ptr & 128;
		length 	= (*(tga->ptr++) & 127) + 1;
		while (length-- > 0)
		{
			tga->image->pixels[i++] = get_pix_values(tga);
			if (!type || !length)
				tga->ptr += 4;
		}
	}
}

IMAGE		*read_tga(char *path)
{
	TGA	tga;

	tga.data = NULL;
	tga.image = NULL;
	if (!read_file(&tga, path))
		return (NULL);
	if (!read_image_info(&tga))
		return (NULL);
	read_data(&tga);
	free(tga.data);
	ft_printf("{green}Successfully read!{eoc}\n");
	return (tga.image);
}