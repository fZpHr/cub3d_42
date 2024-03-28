/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_keys.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:13:51 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/28 22:08:06 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

/**
 * @brief Check if a key is pressed --> move of the player if needed.
 * 
 * @param cub 	The game structure
 */
void	ft_handle_keys(t_cub *cub)
{
	if (cub->keys.forward)
		ft_move_forward(cub);
	if (cub->keys.backward)
		ft_move_backward(cub);
	if (cub->keys.left)
		ft_move_left(cub);
	if (cub->keys.right)
		ft_move_right(cub);
	if (cub->keys.rot_left)
		cub->orientation -= ROT_SPEED;
	if (cub->keys.rot_right)
		cub->orientation += ROT_SPEED;
	if (cub->orientation > 2 * PI)
		cub->orientation -= 2 * PI;
	else if (cub->orientation < 0)
		cub->orientation += 2 * PI;
}
