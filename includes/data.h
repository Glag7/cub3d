/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:50:21 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/19 16:51:42 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include "map.h"
# include "img.h"

typedef struct s_data
{
	t_map	map;
	t_mlx	mlx;
}	t_data;

#endif
