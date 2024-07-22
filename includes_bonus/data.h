/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:50:21 by glaguyon          #+#    #+#             */
/*   Updated: 2024/07/17 13:01:34 by glag             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include <stdint.h>
# include "map.h"
# include "img.h"
# include "play.h"
# include "set.h"
# include "mini.h"
# include "point.h"

typedef struct s_data
{
	t_mini		mini;
	t_map		map;
	t_play		play;
	t_mlx		mlx;
	t_set		set;
	uint64_t	keys;
	t_ipoint	oldmouse;
}	t_data;

#endif
