/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:53:07 by glaguyon          #+#    #+#             */
/*   Updated: 2024/09/24 20:08:51 by glag             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOVE_H
# define MOVE_H

# include <stdint.h>
# include "data.h"

void	move(t_data *data, double delta, uint64_t keys);
void	move_xy(t_data *data, double delta, int stopped);
void	move_angle(t_data *data, double delta, uint64_t keys);
void	open_door(t_data *data, double delta);
void	open_doors(t_data *data, double delta);
void	shoot(t_data *data, double delta);

#endif 
