/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 18:22:13 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/15 18:44:55 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERR_H
# define ERR_H

//MLX
# define ERR_MLX	"MLX failure\n"
# define ERR_MLX_XPM	"MLX: failed to open image\n"

//ARGS
# define ERR_DOTCUB	"Map name needs to end with '.cub'\n"
# define ERR_DIR	"Map is a directory\n"
# define ERR_ARGS	"Too many arguments\n"
# define ERR_OPEN	"Cannot open map\n"
# define ERR_NOMAP	"No map name given\n"

//TEXTURES
# define ERR_BPP	"Too many bits per pixel in an image (max 32 bpp)\n"
# define ERR_IMG_SIZE	"Image has a size of 0\n"
# define ERR_MISS_NO	"Missing north texture\n"
# define ERR_MISS_SO	"Missing south texture\n"
# define ERR_MISS_WE	"Missing west texture\n"
# define ERR_MISS_EA	"Missing east texture\n"
# define ERR_MISS_CEIL	"Missing ceiling color\n"
# define ERR_MISS_FLOOR	"Missing floor color\n"
# define ERR_DUP_NO	"Duplicate north texture\n"
# define ERR_DUP_SO	"Duplicate south texture\n"
# define ERR_DUP_EA	"Duplicate east texture\n"
# define ERR_DUP_WE	"Duplicate west texture\n"
# define ERR_DUP_FLOOR	"Duplicate floor color\n"
# define ERR_DUP_CEIL	"Duplicate ceiling color\n"

//MALLOC
# define ERR_MALLOC	"Failed memory allocation\n"

#endif
