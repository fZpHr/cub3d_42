/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_new_frame.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:19:03 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/17 13:40:45 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

/**
 * @brief Create a new MLX frame (screen sized) and return all the info.
 * 
 * @param cub 		The game structure
 * @param free_old 	Should we free the old frame ? (in cub is not NULL)
 * 
 * @return t_frame 	The new frame
*/
t_frame	ft_mlx_new_frame(t_cub *cub, t_bool free_old)
{
	t_frame	frame;

	if (free_old && cub->frame.img)
	{
		mlx_destroy_image(cub->mlx, cub->frame.img);
		cub->frame.img = NULL;
	}
	frame.img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (frame.img)
		frame.addr = mlx_get_data_addr(frame.img,
				&frame.bits_per_pixel, &frame.line_size, &frame.endian);
	if (!frame.img || !frame.addr)
	{
		ft_error("Frame creation failed");
		if (frame.img)
			mlx_destroy_image(cub->mlx, frame.img);
		frame.img = NULL;
	}
	return (frame);
}
