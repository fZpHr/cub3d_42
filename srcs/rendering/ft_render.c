/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:22:24 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/28 22:08:06 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

static void	ft_ray_casting(t_cub *cub, t_casting castings[RAYS]);

/**
 * @brief Render a frame.
 * 
 * @brief	1. Render the floor and the ceiling
 * 				(see ft_render_floor and ft_render_ceiling)
 * 
 * @brief	2. Ray casting (see ft_cast_ray)
 * @brief		- Cast `RAYS` rays evenly from
 * 					`dir - FOV / 2` to `dir + FOV / 2`
 * @brief		- Cast and save the result in `castings` (for the minimap)
 * 
 * @brief	3. Calculate wall height
 * @brief		- Fish-eye correction: `dist *= cos(dir - a)`
 * @brief		- `height = (HEIGHT / dist) * 1.5`
 * 
 * @brief	4. Draw the wall (see ft_render_chunk)
 * 
 * @brief	5. Draw the minimap (see ft_render_minimap)
 * 
 * @param cub 	The game structure
 */
void	ft_render(t_cub *cub)
{
	t_casting	castings[RAYS];

	ft_render_floor(cub);
	ft_render_ceiling(cub);
	ft_ray_casting(cub, castings);
	if (cub->minimap)
		ft_render_minimap(cub, castings);
	mlx_put_image_to_window(cub->mlx, cub->mlx_win, cub->frame.img, 0, 0);
	if (cub->info)
		ft_render_info(cub);
	cub->frames++;
}

void	ft_ray_casting(t_cub *cub, t_casting castings[RAYS])
{
	float		angle;
	float		width;
	int			ray;
	t_casting	casting;
	int			height;

	angle = cub->orientation - FOV / 2;
	if (angle < 0)
		angle += 2 * PI;
	width = (float) WIDTH / RAYS;
	ray = -1;
	while (++ray < RAYS)
	{
		casting = ft_cast_ray(cub, angle + ((float) FOV / RAYS) * ray);
		if (casting.distance != -1)
		{
			casting.distance *= cos(cub->orientation - casting.angle);
			if (casting.distance < 0.2)
				casting.distance = 0.2;
			height = ((HEIGHT / casting.distance) * 1.5);
			ft_render_chunk(cub, ray * width,
				(t_ipos){width + 1, height}, casting);
		}
		castings[ray] = casting;
	}
}
