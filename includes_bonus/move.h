/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:53:07 by glaguyon          #+#    #+#             */
/*   Updated: 2024/09/26 04:35:01 by glag             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOVE_H
# define MOVE_H

# include <stdint.h>
# include "data.h"
# include "point.h"

void		move(t_data *data, double delta, uint64_t keys);
void		move_xy(t_data *data, double delta, int stopped);
void		move_angle(t_data *data, double delta, uint64_t keys);
void		open_door(t_data *data, double delta);
void		open_doors(t_data *data, double delta);
void		shoot(t_data *data, double delta);
t_point	raycast_newpos(t_data *data);

#endif 
