/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:04:42 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/15 16:57:44 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

//do not set to < 2
# define BUF_SIZE 4096

int		parse_map(void *mlx, t_map *map, int argc, char **argv);
int		parse_buf(void *mlx, t_map *map, char *buf, size_t size);
int		try_load(void *mlx, t_map *map, char *buf, size_t *i);
int		load_no(void *mlx, t_map *map, char *buf, size_t *i);
int		load_so(void *mlx, t_map *map, char *buf, size_t *i);
int		load_ea(void *mlx, t_map *map, char *buf, size_t *i);
int		load_we(void *mlx, t_map *map, char *buf, size_t *i);
int		load_floor(void *mlx, t_map *map, char *buf, size_t *i)
int		load_ceil(void *mlx, t_map *map, char *buf, size_t *i)

#endif
