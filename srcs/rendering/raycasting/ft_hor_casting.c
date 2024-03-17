/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hor_casting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:06:01 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/17 11:06:30 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

/**
 * @brief Check if the ray is hitting horizontally a wall.
 * 
 * @brief	1. Step to the closest horizontal grid line
 * @brief		- `y = closest y coordinate of a horizontal grid line`
 * @brief		- `x = pos.x - (pos.y - y) / tan(a)` --> The x of the ray at y
 * 
 * @brief	2. Define deltas to checks all the other horizontal grid lines
 * @brief		- `delta_y = -1 if ray facing up else 1`
 * @brief		- `delta_x = 1 / tan(-a) if ray facing left else -1 / tan(-a)`
 * 
 * @note `-a` is used trigo instead of `a` because the Y axis is inverted.
 * 
 * @param cub 		The game structure
 * @param casting 	The ray casting structure, with all the results !
*/
void	ft_hor_casting(t_cub *cub, t_casting *casting)
{
	casting->hor_y = (int) cub->position.y;
	if (casting->angle < PI)
		casting->hor_y++;
	casting->hor_x = cub->position.x - (cub->position.y - casting->hor_y) / tan(casting->angle);

	casting->hor_step_y = -1;
	if (casting->angle < PI)
		casting->hor_step_y = 1;
	casting->hor_step_x = 1 / tan(-casting->angle);
	if (casting->angle < PI)
		casting->hor_step_x = -casting->hor_step_x;

	while (casting->hor_y - (casting->angle < PI ? 0 : 1) >= 0 && casting->hor_y < cub->map_size.y
		&& casting->hor_x >= 0 && casting->hor_x < cub->map_size.x
		&& !cub->map_array[(int) casting->hor_y - (casting->angle < PI ? 0 : 1)][(int) casting->hor_x].is_solid)
	{
		casting->hor_x += casting->hor_step_x;
		casting->hor_y += casting->hor_step_y;
	}

	if (casting->hor_y - (casting->angle < PI ? 0 : 1) < 0 || casting->hor_y >= cub->map_size.y
		|| casting->hor_x < 0 || casting->hor_x >= cub->map_size.x
		|| !cub->map_array[(int) casting->hor_y - (casting->angle < PI ? 0 : 1)][(int) casting->hor_x].is_solid)
		casting->hor_dist = -1;
	else
		casting->hor_dist = sqrt(pow(cub->position.x - casting->hor_x, 2)
			+ pow(cub->position.y - casting->hor_y, 2));
}
