/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_floor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:05:01 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/17 13:10:44 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

/**
 * @brief The floor == colored rectangle, expanding along the width
 * 			from the middle to the bottom of the screen.
 * 
 * @param cub 	The game structure
*/
void	ft_render_floor(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIDTH)
	{
		j = HEIGHT / 2 - 1;
		while (j < HEIGHT)
		{
			ft_put_pixel(cub->frame, i, j, cub->floor_c);
			j++;
		}
		i++;
	}
}
