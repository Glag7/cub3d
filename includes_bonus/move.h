/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:53:07 by glaguyon          #+#    #+#             */
/*   Updated: 2024/09/06 18:08:39 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOVE_H
# define MOVE_H

# include <stdint.h>
# include "data.h"

void	move(t_data *data, double delta, uint64_t keys);
void	move_angle(t_data *data, double delta, uint64_t keys);
void	open_door(t_data *data, double delta);

#endif 
