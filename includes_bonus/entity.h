/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:26:53 by glaguyon          #+#    #+#             */
/*   Updated: 2024/08/09 17:20:18 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITY_H
# define ENTITY_H

# define MORE_JUST_IN_CASE 64

# define DOOR 1
# define MAN 2
# define BOMB 4

typedef struct s_ent
{//XXX
	int		type;
	double	x;
	double	y;
	double	z;
	double	hei;
	double	wid;
}	t_ent;

#endif
