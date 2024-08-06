/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 16:17:10 by glaguyon          #+#    #+#             */
/*   Updated: 2024/08/06 15:38:05 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "utils.h"
#include "map.h"

void	free_map(t_map *map)
{
	free(map->map);
	free(map->n.px);
	free(map->s.px);
	free(map->w.px);
	free(map->e.px);
	free(map->f.px);
	free(map->c.px);
	free(map->d.px);
	ft_bzero(map, sizeof(*map));
}
