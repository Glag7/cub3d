/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:29:41 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/15 15:51:34 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include <stdint.h>

typedef struct s_img
{
	uint32_t	*px;
	uint64_t	size;
}	t_img;

typedef struct s_map
{
	uint8_t		*map;
	t_img		n;
	t_img		s;
	t_img		w;
	t_img		e;
	uint32_t	floor;
	uint32_t	ceil;
}	t_map;

#endif
