/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cast_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:09:02 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/28 16:51:55 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

static void	ft_update_casting(t_casting *casting);

/**
 * @brief Cast a ray from the player position to the given angle.
 * 
 * @brief	1. Make an horizontal collision detection:
 * @brief		- If the ray hits, save the
 * @brief			- x and y position of the collision
 * @brief			- distance to the collision
 * @brief			- facing of the wall (either `NORTH` or `SOUTH`)
 * @brief		- else, save `-1` as the distance.
 * 
 * @brief	2. Make a vertical collision detection:
 * @brief		- If the ray hits, save the
 * @brief			- x and y position of the collision
 * @brief			- distance to the collision
 * @brief			- facing of the wall (either `WEST` or `EAST`)
 * @brief		- else, save `-1` as the distance.
 * 
 * @brief	3. Take the closest collision, save it and return it.
 * @brief		- If the ray hits, save the
 * @brief			- x and y position of the collision
 * @brief			- distance to the collision
 * @brief			- facing of the wall (either `WEST` or `EAST`)
 * @brief		- else, save `-1` as the distance.
 * 
 * @brief	- This way, we check max `map's height + map's width` collisions !
 * 
 * @param cub 		The game structure
 * @param angle 	The angle of the ray (in rad)
 * 
 * @return t_casting 	The result of the ray casting
*/
t_casting	ft_cast_ray(t_cub *cub, float angle)
{
	t_casting	casting;

	while (angle >= 2 * PI)
		angle -= 2 * PI;
	casting = (t_casting){0};
	casting.angle = angle;
	casting.hor_dist = -1;
	casting.ver_dist = -1;
	ft_hor_casting(cub, &casting);
	ft_ver_casting(cub, &casting);
	ft_update_casting(&casting);
	return (casting);
}

static void	ft_update_casting(t_casting *casting)
{
	if (casting->hor_dist != -1
		&& (casting->hor_dist <= casting->ver_dist || casting->ver_dist == -1))
	{
		casting->x = casting->hor_x;
		casting->y = casting->hor_y;
		casting->distance = casting->hor_dist;
		casting->facing = SOUTH;
		if (casting->angle < PI)
			casting->facing = NORTH;
	}
	else if (casting->ver_dist != -1
		&& (casting->ver_dist <= casting->hor_dist || casting->hor_dist == -1))
	{
		casting->x = casting->ver_x;
		casting->y = casting->ver_y;
		casting->distance = casting->ver_dist;
		casting->facing = EAST;
		if (casting->angle < PI_2 || casting->angle > 3 * PI_2)
			casting->facing = WEST;
	}
	else
		casting->distance = -1;
}
