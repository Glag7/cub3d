/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:40:48 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/28 18:52:15 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <stdint.h>
# include <stddef.h>
# include "data.h"
# include "map.h"

int		draw(void *data_);
void	drawv(t_data *data, t_img img, unsigned int x, unsigned int offset, double hei);
void	draw_minimap(t_data *data);
void	move(t_data *data, double delta, uint64_t keys);

#endif
