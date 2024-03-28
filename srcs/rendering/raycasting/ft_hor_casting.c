/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hor_casting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:06:01 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/28 22:08:06 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

static void	ft_closest_hor_line(t_cub *cub, t_casting *casting);
static void	ft_define_steps(t_cub *cub, t_casting *casting);
static void	ft_parcours_until_collision(t_cub *cub, t_casting *casting);
static void	ft_save_distance(t_cub *cub, t_casting *casting);

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
	ft_closest_hor_line(cub, casting);
	ft_define_steps(cub, casting);
	ft_parcours_until_collision(cub, casting);
	ft_save_distance(cub, casting);
}

static void	ft_closest_hor_line(t_cub *cub, t_casting *casting)
{
	casting->hor_y = (int) cub->position.y;
	if (casting->angle < PI)
		casting->hor_y++;
	casting->hor_x = cub->position.x
		- (cub->position.y - casting->hor_y) / tan(casting->angle);
}

static void	ft_define_steps(t_cub *cub, t_casting *casting)
{
	(void)cub;
	casting->hor_step_y = -1;
	if (casting->angle < PI)
		casting->hor_step_y = 1;
	casting->hor_step_x = 1 / tan(-casting->angle);
	if (casting->angle < PI)
		casting->hor_step_x = -casting->hor_step_x;
}

static void	ft_parcours_until_collision(t_cub *cub, t_casting *casting)
{
	int	off;

	off = 1;
	if (casting->angle < PI)
		off = 0;
	while (casting->hor_y - off >= 0 && casting->hor_y < cub->map_size.y
		&& casting->hor_x >= 0 && casting->hor_x < cub->map_size.x
		&& !cub->map_array[(int) casting->hor_y - off] \
			[(int) casting->hor_x].is_solid)
	{
		casting->hor_x += casting->hor_step_x;
		casting->hor_y += casting->hor_step_y;
	}
}

static void	ft_save_distance(t_cub *cub, t_casting *casting)
{
	int	off;

	off = 1;
	if (casting->angle < PI)
		off = 0;
	if (casting->hor_y - off < 0 || casting->hor_y >= cub->map_size.y
		|| casting->hor_x < 0 || casting->hor_x >= cub->map_size.x
		|| !cub->map_array[(int) casting->hor_y - off] \
			[(int) casting->hor_x].is_solid)
		casting->hor_dist = -1;
	else
		casting->hor_dist = sqrt(pow(cub->position.x - casting->hor_x, 2)
				+ pow(cub->position.y - casting->hor_y, 2));
}
