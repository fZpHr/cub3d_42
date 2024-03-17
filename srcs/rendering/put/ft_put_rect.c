/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_rect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:07:51 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/17 13:40:22 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

/**
 * @brief Fill a rectangle of the frame with the given color (see ft_put_pixel).
 * 
 * @param frame 	The frame to edit
 * @param pos 		The position of the rectangle (in px)
 * @param size 		The size of the rectangle (width, height, in px)
 * @param color 	The color to set (in ARGB format)
*/
void	ft_put_rect(t_frame frame, t_ipos pos, t_ipos size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size.x)
	{
		j = 0;
		while (j < size.y)
		{
			ft_put_pixel(frame, pos.x + i, pos.y + j, color);
			j++;
		}
		i++;
	}
}
