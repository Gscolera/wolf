#include "tga_reader.h"

bool	get_tga_info(char *path)
{
	int		fd;
	U8		info[18];

	if ((fd = open(path, O_RDONLY)) == -1)
		return (open_error(path));
	read(fd, info, 18);
	close(fd);
	ft_printf("{blue}{underline}%s\n{eoc}", path);
	ft_printf("ID length:  %d\n", info[0]);
	ft_printf("Image type: %d\n", info[2]);
	ft_printf("X-origin:   %d\n", (info[8] | info[9] << 8));
	ft_printf("Y-origin:   %d\n", (info[10] | info[11] << 8));
	ft_printf("Width:      %d\n", (info[12] | info[13] << 8));
	ft_printf("Height:     %d\n", (info[14] | info[15] << 8));
	ft_printf("BPP:        %d\n", info[16] / 8);
	ft_printf("Color map %s.\n", (info[1]) ? "included" : "not included");
	return (1);
}