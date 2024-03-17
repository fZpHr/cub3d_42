/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_ceiling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:05:35 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/17 11:07:13 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

/**
 * @brief The ceiling == colored rectangle, expanding along the width
 * 			from the top to the middle of the screen.
 * 
 * @param cub 	The game structure
*/
void	ft_render_ceiling(t_cub *cub)
{
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT / 2; j++)
		{
			ft_put_pixel(cub->frame, i, j, cub->ceiling_c);
		}
	}
}
