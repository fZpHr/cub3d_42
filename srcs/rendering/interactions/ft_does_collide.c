/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_does_collide.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:11:54 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/28 22:08:06 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

/**
 * @brief Check if the player is colliding with a wall at the given position,
 * 			or if he is out of the map.
 * 
 * @param cub 		The game structure
 * @param position 	The position to check
 * 
 * @return t_bool 	`TRUE` if the player shouldn't be here, `FALSE` otherwise
 */
t_bool	ft_does_collide(t_cub *cub, t_pos position)
{
	if (!BONUS)
		return (position.x < 0 || position.x >= cub->map_size.x
			|| position.y < 0 || position.y >= cub->map_size.y);
	return (position.x < 0 || position.x >= cub->map_size.x
		|| position.y < 0 || position.y >= cub->map_size.y
		|| cub->map_array[(int) position.y][(int) position.x].is_solid);
}
