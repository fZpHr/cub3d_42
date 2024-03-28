/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:15:20 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/28 22:08:06 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

/**
 * @brief The game loop.
 * 
 * @param cub 	The game structure
 * 
 * @return int 	Always `0`
 */
int	ft_game_loop(t_cub *cub)
{
	ft_handle_keys(cub);
	ft_anim(cub);
	ft_handle_doors(cub);
	ft_render(cub);
	return (0);
}
