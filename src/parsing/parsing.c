/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:04:13 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/14 16:03:33 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "mlx.h"
#include "map.h"
#include "utils.h"

static int	check_name(const char *name)
{
	size_t	len;
	int		fd;

	len = 0;
	while (name[len])
		len++;
	if (len < 4 || !(name[len - 4] == '.' && name[len - 3] == 'c'
			&& name[len - 2] == 'u' && name[len - 1] == 'b'))
	{
		ft_perror("Map name needs to end with '.cub'\n");
		return (1);
	}
	fd = open(name, O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		ft_perror("Map is a directory\n");
		return (1);
	}
	return (0);

}

int	parse_map(void *mlx, t_map *map, int argc, char **argv)
{
	int	fd;

	if (argc < 2)
		ft_perror("No map name given\n");
	if (argc > 2)
		ft_perror("Too many arguments\n");
	if (argc != 2 || check_name(argv[1]))
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		ft_perror("Cannot open map\n");
		return (1);
	}
	close(fd);
	return (0);
}
