/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:15:20 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/18 16:59:21 by ysabik           ###   ########.fr       */
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
