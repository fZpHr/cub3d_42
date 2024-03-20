/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_load_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 04:14:53 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/20 05:30:56 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Load a texture from a file and return all the info.
 * 
 * @param cub 	The game structure
 * @param path 	The path of the texture file
 * 
 * @note	If there is a problem, `frame.img` is `NULL`.
 * 
 * @return t_frame 	The texture
*/
t_frame	ft_load_texture(t_cub *cub, char *path)
{
	t_frame	frame;
	int		width;
	int		height;
	int		bpp;
	int		endian;

	frame.img = mlx_xpm_file_to_image(cub->mlx, path, &width, &height);
	if (!frame.img)
		return (frame);
	frame.addr = mlx_get_data_addr(frame.img, &bpp, &frame.line_size, &endian);
	frame.width = width;
	frame.height = height;
	frame.bits_per_pixel = bpp;
	frame.endian = endian;
	return (frame);
}
