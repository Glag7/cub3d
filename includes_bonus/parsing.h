/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:04:42 by glaguyon          #+#    #+#             */
/*   Updated: 2024/09/04 16:56:41 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stddef.h>
# include "specs.h"
# include "data.h"
# include "map.h"

//do not set to < 2
# define BUF_SIZE 4096

int		parse_map(void *mlx, t_data *data, int argc, char **argv);
int		parse_buf(void *mlx, t_data *data, char *buf, size_t size);
int		try_load(void *mlx, t_data *data, char *buf, unsigned int *i);
int		load_no(void *mlx, t_data *data, char *buf, unsigned int *i);
int		load_so(void *mlx, t_data *data, char *buf, unsigned int *i);
int		load_ea(void *mlx, t_data *data, char *buf, unsigned int *i);
int		load_we(void *mlx, t_data *data, char *buf, unsigned int *i);
int		load_floor(t_data *data, char *buf, unsigned int *i);
int		load_ceil(t_data *data, char *buf, unsigned int *i);
int		load_door(void *mlx, t_data *data, char *buf, unsigned int *i);
int		load_glass(void *mlx, t_data *data, char *buf, unsigned int *i);
int		load_topbottom(void *mlx, t_data *data, char *buf, unsigned int *i);
int		load_img(void *mlx, char *path, t_img *image, t_dim dim);
int		load_gun(t_data *data);
int		get_bmp_img(char *path, t_specs *specs);
int		get_data(char *buf, t_data *data);
void	resize_image(t_img *image, t_specs specs);
void	fill_map(t_map *map, char *buf);
int		check_map(t_map *map);

#endif
