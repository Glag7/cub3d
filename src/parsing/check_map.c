/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 19:27:08 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/16 19:31:35 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "map.h"
#include "err.h"
#include "utils.h"

int	check_map(t_map *map)
{
	if (0)
	{
		ft_perror(ERR_MALLOC);//n
		free_map(map);
		return (1);
	}
	return (0);
}
