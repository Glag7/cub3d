/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:04:42 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/16 19:31:12 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "specs.h"
# include "map.h"

//do not set to < 2
# define BUF_SIZE 4096

int		parse_map(void *mlx, t_map *map, int argc, char **argv);
int		parse_buf(void *mlx, t_map *map, char *buf);
int		try_load(void *mlx, t_map *map, char *buf, size_t *i);
int		load_no(void *mlx, t_map *map, char *buf, size_t *i);
int		load_so(void *mlx, t_map *map, char *buf, size_t *i);
int		load_ea(void *mlx, t_map *map, char *buf, size_t *i);
int		load_we(void *mlx, t_map *map, char *buf, size_t *i);
int		load_floor(void *mlx, t_map *map, char *buf, size_t *i);
int		load_ceil(void *mlx, t_map *map, char *buf, size_t *i);
int		load_img(void *mlx, char *path, t_img *img);
int		get_data(char *buf, t_map *map);
void	read_image(t_img *image, t_specs img_specs);
void	fill_map(t_map *map, char *buf);
int		check_map(t_map *map);

#endif
