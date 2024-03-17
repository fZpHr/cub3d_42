/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:22:24 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/17 11:24:48 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

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
	ft_render_floor(cub);
	ft_render_ceiling(cub);

	t_casting	castings[RAYS];

	float	angle = cub->orientation - FOV / 2;
	if (angle < 0)
		angle += 2 * PI;
	float	step = (float) FOV / RAYS;
	float	width = (float) WIDTH / RAYS;
	int		ray = 0;
	while (ray < RAYS)
	{
		float		a = angle + step * ray;
		if (a >= 2 * PI)
			a -= 2 * PI;
		t_casting	casting = ft_cast_ray(cub, a);
		if (casting.distance != -1)
		{
			casting.distance *= cos(cub->orientation - casting.angle);
			if (casting.distance < 0.2)
				casting.distance = 0.2;
			int			height = ((HEIGHT / casting.distance) * 1.5);
			int			x = ray * width;
			ft_render_chunk(cub, x, (t_ipos){width + 1, height}, casting);
		}
		castings[ray] = casting;
		ray++;
	}

	if (cub->minimap)
		ft_render_minimap(cub, castings);

	mlx_put_image_to_window(cub->mlx, cub->mlx_win, cub->frame.img, 0, 0);

	cub->frames++;
}

