/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:04:42 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/28 17:54:45 by glaguyon         ###   ########.fr       */
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
int		try_load(void *mlx, t_map *map, char *buf, unsigned int *i);
int		load_no(void *mlx, t_map *map, char *buf, unsigned int *i);
int		load_so(void *mlx, t_map *map, char *buf, unsigned int *i);
int		load_ea(void *mlx, t_map *map, char *buf, unsigned int *i);
int		load_we(void *mlx, t_map *map, char *buf, unsigned int *i);
int		load_floor(void *mlx, t_map *map, char *buf, unsigned int *i);
int		load_ceil(void *mlx, t_map *map, char *buf, unsigned int *i);
int		load_img(void *mlx, char *path, t_img *img);
int		get_data(char *buf, t_data *data);
void	read_image(t_img *image, t_specs img_specs);
void	fill_map(t_map *map, char *buf);
int		check_map(t_map *map);

#endif
