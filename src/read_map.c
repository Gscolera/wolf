#include "wolf3d.h"

static bool	map_error(ENGINE *wolf, char *path)
{
	wolf->power = false;
	perror(path);
	return (0);
}

static void	parse_map(ENGINE *wolf, U32 fd)
{
	U32	i;
	U32 j;
	U8	buff[MAP_W + 1];

	i = 0;
	BLOCK = (U8 **)malloc(sizeof(U8 *) * MAP_H);
	while (i < MAP_H)
	{
		BLOCK[i] = (U8 *)malloc(MAP_W);
		read(fd, buff, MAP_W + 1);
		j = 0;
		while (j < MAP_W)
		{
			BLOCK[i][j] = buff[j] - 48;
			j++;
		}
		i++;
	}
}

bool		read_map(ENGINE *wolf, char *path)
{
	U32 fd;
	U8	buf[1];

	if ((fd = open(path, O_RDONLY)) == -1)
		return (map_error(wolf, path));
	while (read(fd, buf, 1))
	{
		if (buf[0] == '\n')
			break ;
		MAP_W = MAP_W * 10 + buf[0] - 48;
	}
	while (read(fd, buf, 1))
	{
		if (buf[0] == '\n')
			break ;
		MAP_H = MAP_H * 10 + buf[0] - 48;
	}
	parse_map(wolf, fd);
	close(fd);
	return (1);
}