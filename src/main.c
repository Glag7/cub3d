/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:58:59 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/15 18:45:33 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mlx.h"
#include "map.h"
#include "utils.h"
#include "parsing.h"
#include "err.h"

int	main(int argc, char **argv)
{
	t_img	img;
	void	*mlx;
	void	*mlx_img;
	int	res;
	void	*win;

	img = (t_img){0, 0};
	mlx = mlx_init();
	res = load_img(mlx, argv[1], &img);
	win = mlx_new_window(mlx, img.size, img.size, "test");
	mlx_img = mlx_new_image(mlx, img.size, img.size);
	size_t i = 0;
	char	*ptr;
	int null;
	ptr = (char *)img.px;
	char	*addr = mlx_get_data_addr(mlx_img, &null, &null, &null);
	while (i < (img.size * img.size) * 4)
	{
		*((int *)addr) = 0x00000000;
		addr += 4;
		ptr++;
		i += 4;
	}
	mlx_put_image_to_window(mlx, win, mlx_img, 0, 0);
	mlx_loop(mlx);
	free(img.px);
	mlx_destroy_image(mlx, mlx_img);
	mlx_destroy_window(mlx, win);
	mlx_destroy_display(mlx);
	free(mlx);
	return (0);
}

/*int	main(int argc, char **argv)
{
	t_map	map;
	void	*mlx;

	mlx = mlx_init();
	if (mlx == NULL)
	{
		ft_perror(ERR_MLX);
		return (1);
	}
	if (parse_map(mlx, &map, argc, argv))
	{
		mlx_destroy_display(mlx);
		free(mlx);
		return (1);
	}
	//TODO DRAW
	mlx_destroy_display(mlx);
	free(mlx);
	return (0);
}*/
