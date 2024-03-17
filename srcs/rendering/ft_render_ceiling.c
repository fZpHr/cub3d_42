/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_ceiling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:05:35 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/17 13:10:34 by ysabik           ###   ########.fr       */
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
	int	i;
	int	j;

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT / 2)
		{
			ft_put_pixel(cub->frame, i, j, cub->ceiling_c);
			j++;
		}
		i++;
	}
}
