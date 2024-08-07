/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 18:22:13 by glaguyon          #+#    #+#             */
/*   Updated: 2024/08/07 14:05:15 by glaguyon         ###   ########.fr       */
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
# define ERR_IMG_SIZE	"Image has a size of 0\n"
# define ERR_FORMAT	"Image is in wrong format (not BMP)\n"
# define ERR_BPP	"Image has wrong bits per pixel value\n"
# define ERR_COMPRESS	"Image has wrong compression level\n"
# define ERR_IMG_EXT	"Image file has an unsupported extension\n"
# define ERR_READ	"Failed to read file\n"
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
# define ERR_DUP_FLOOR	"Duplicate floor texture\n"
# define ERR_DUP_CEIL	"Duplicate ceiling texture\n"
# define ERR_DUP_DOOR	"Duplicate door texture\n"
# define ERR_BAD_FLOOR	"Unrecognized floor color\n"
# define ERR_BAD_CEIL	"Unrecognized ceiling color\n"

//MAP
# define ERR_TOOLARGE	"Map is too large\n"
# define ERR_BADCHAR	"Map contains unrecognized character\n"
# define ERR_NOPLAYER	"Map does not contain a player\n"
# define ERR_MOREPLAYER	"Map contains more than one player\n"
# define ERR_NOWALL	"Map contains areas without walls\n"

//MALLOC
# define ERR_MALLOC	"Failed memory allocation\n"

#endif
