#include "tga_reader.h"

bool	open_error(char *path)
{
	perror(path);
	return (0);
}

bool	mem_error(TGA *tga)
{
	ft_printf("{red}{eoc}Unable to allocate memory{eoc}\n");
	if (tga->data)
		free(tga->data);
	return (0);
}

bool	unsupported_error(TGA *tga)
{
	ft_printf("{red}{eoc}Unsupported format{eoc}\n");
	free(tga->data);
	return (0);
}