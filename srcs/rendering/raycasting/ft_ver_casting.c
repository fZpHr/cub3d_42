/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ver_casting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:08:35 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/17 11:08:50 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

/**
 * @brief Check if the ray is hitting vertically a wall.
 * 
 * @brief	1. Step to the closest vertical grid line
 * @brief		- `x = closest x coordinate of a vertical grid line`
 * @brief		- `y = pos.y - (pos.x - x) * tan(a)` --> The y of the ray at x
 * 
 * @brief	2. Define deltas to checks all the other vertical grid lines
 * @brief		- `delta_x = -1 if ray facing left else 1`
 * @brief		- `delta_y = tan(-a) if ray facing up else -tan(-a)`
 * 
 * @note `-a` is used trigo instead of `a` because the Y axis is inverted.
 * 
 * @param cub 		The game structure
 * @param casting 	The ray casting structure, with all the results !
*/
void	ft_ver_casting(t_cub *cub, t_casting *casting)
{
	casting->ver_x = (int) cub->position.x;
	if (casting->angle < PI_2 || casting->angle > 3 * PI_2)
		casting->ver_x++;
	casting->ver_y = cub->position.y - (cub->position.x - casting->ver_x) * tan(casting->angle);

	casting->ver_step_x = -1;
	if (casting->angle < PI_2 || casting->angle > 3 * PI_2)
		casting->ver_step_x = 1;
	casting->ver_step_y = tan(-casting->angle);
	if (casting->angle < PI_2 || casting->angle > 3 * PI_2)
		casting->ver_step_y = -casting->ver_step_y;

	while (casting->ver_y >= 0 && casting->ver_y < cub->map_size.y
		&& casting->ver_x - (casting->angle < PI_2 || casting->angle > 3 * PI_2 ? 0 : 1) >= 0 && casting->ver_x < cub->map_size.x
		&& !cub->map_array[(int) casting->ver_y][(int) casting->ver_x - (casting->angle < PI_2 || casting->angle > 3 * PI_2 ? 0 : 1)].is_solid)
	{
		casting->ver_x += casting->ver_step_x;
		casting->ver_y += casting->ver_step_y;
	}

	if (casting->ver_y < 0 || casting->ver_y >= cub->map_size.y
		|| casting->ver_x - (casting->angle < PI_2 || casting->angle > 3 * PI_2 ? 0 : 1) < 0 || casting->ver_x >= cub->map_size.x
		|| !cub->map_array[(int) casting->ver_y][(int) casting->ver_x - (casting->angle < PI_2 || casting->angle > 3 * PI_2 ? 0 : 1)].is_solid)
		casting->ver_dist = -1;
	else
		casting->ver_dist = sqrt(pow(cub->position.x - casting->ver_x, 2)
			+ pow(cub->position.y - casting->ver_y, 2));
}
