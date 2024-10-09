/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:32:28 by glaguyon          #+#    #+#             */
/*   Updated: 2024/08/06 16:02:45 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "err.h"
#include "utils.h"
#include "parsing.h"

int	load_no(void *mlx, t_data *data, char *buf, unsigned int *i)
{
	unsigned int	j;
	char			c;

	if (data->map.n.px)
	{
		ft_perror(ERR_DUP_NO);
		return (1);
	}
	*i += 2;
	while (buf[*i] == ' ')
		(*i)++;
	j = *i;
	while (buf[j] && buf[j] != '\n')
		j++;
	c = buf[j];
	buf[j] = 0;
	if (load_img(mlx, buf + *i, &data->map.n,
			(t_dim){data->set.texsiz, data->set.texsiz}))
		return (1);
	buf[j] = c;
	*i = j;
	return (0);
}

int	load_so(void *mlx, t_data *data, char *buf, unsigned int *i)
{
	unsigned int	j;
	char			c;

	if (data->map.s.px)
	{
		ft_perror(ERR_DUP_SO);
		return (1);
	}
	*i += 2;
	while (buf[*i] == ' ')
		(*i)++;
	j = *i;
	while (buf[j] && buf[j] != '\n')
		j++;
	c = buf[j];
	buf[j] = 0;
	if (load_img(mlx, buf + *i, &data->map.s,
			(t_dim){data->set.texsiz, data->set.texsiz}))
		return (1);
	buf[j] = c;
	*i = j;
	return (0);
}

int	load_we(void *mlx, t_data *data, char *buf, unsigned int *i)
{
	unsigned int	j;
	char			c;

	if (data->map.w.px)
	{
		ft_perror(ERR_DUP_WE);
		return (1);
	}
	*i += 2;
	while (buf[*i] == ' ')
		(*i)++;
	j = *i;
	while (buf[j] && buf[j] != '\n')
		j++;
	c = buf[j];
	buf[j] = 0;
	if (load_img(mlx, buf + *i, &data->map.w,
			(t_dim){data->set.texsiz, data->set.texsiz}))
		return (1);
	buf[j] = c;
	*i = j;
	return (0);
}

int	load_ea(void *mlx, t_data *data, char *buf, unsigned int *i)
{
	unsigned int	j;
	char			c;

	if (data->map.e.px)
	{
		ft_perror(ERR_DUP_EA);
		return (1);
	}
	*i += 2;
	while (buf[*i] == ' ')
		(*i)++;
	j = *i;
	while (buf[j] && buf[j] != '\n')
		j++;
	c = buf[j];
	buf[j] = 0;
	if (load_img(mlx, buf + *i, &data->map.e,
			(t_dim){data->set.texsiz, data->set.texsiz}))
		return (1);
	buf[j] = c;
	*i = j;
	return (0);
}
