/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:24:33 by glaguyon          #+#    #+#             */
/*   Updated: 2024/10/09 20:18:35 by glag             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAY_H
# define PLAY_H

# define FAT .25

typedef struct s_play
{
	double	x;
	double	y;
	double	z;
	double	leglen;
	double	vx;
	double	vy;
	double	vz;
	double	a;
	double	az;
	double	cosa;
	double	sina;
}	t_play;

#endif
