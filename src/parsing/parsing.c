/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:04:13 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/16 16:46:19 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "map.h"
#include "err.h"
#include "utils.h"
#include "parsing.h"

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
		ft_perror(ERR_DOTCUB);
		return (1);
	}
	fd = open(name, O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		ft_perror(ERR_DIR);
		return (1);
	}
	return (0);
}

static inline void	change_size(size_t *size, size_t nread)
{
	if (*size != BUF_SIZE)
		*size = *size / 2 + nread;
	else
		*size = nread;
}

static char	*fill_buf(int fd, size_t *size)
{
	char	*buf;
	char	*tmp;
	size_t	nread;

	buf = malloc(*size + 1);
	if (buf == NULL)
		return (NULL);
	nread = read(fd, buf, *size);
	while (nread == *size / 2 || (nread == *size && nread == BUF_SIZE))
	{
		tmp = malloc(*size * 2 + 1);
		if (tmp == NULL)
			free(buf);
		if (tmp == NULL)
			return (NULL);
		ft_memcpy(tmp, buf, *size);
		free(buf);
		buf = tmp;
		nread = read(fd, buf + *size, *size);
		*size *= 2;
	}
	change_size(size, nread);
	buf[*size] = 0;
	return (buf);
}

static inline int	check_args(int argc)
{
	if (argc < 2)
		ft_perror(ERR_NOMAP);
	if (argc > 2)
		ft_perror(ERR_ARGS);
	return (argc != 2);
}

int	parse_map(void *mlx, t_map *map, int argc, char **argv)
{
	int		fd;
	char	*buf;
	size_t	size;

	if (check_args(argc) || check_name(argv[1]))
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		ft_perror(ERR_OPEN);
		return (1);
	}
	size = BUF_SIZE;
	buf = fill_buf(fd, &size);
	if (buf == NULL)
	{
		ft_perror(ERR_MALLOC);
		close(fd);
		return (1);
	}
	close(fd);
	ft_bzero(map, sizeof(*map));
	return (parse_buf(mlx, map, buf));
}
