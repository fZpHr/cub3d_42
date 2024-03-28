/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:08:11 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/28 22:08:06 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

/**
 * @brief Draw a line between two points of the frame with the given color.
 * 
 * @param frame 	The frame to edit
 * @param start 	The start position of the line (in px)
 * @param end 		The end position of the line (in px)
 * @param color 	The color to set (in ARGB format)
 */
void	ft_put_line(t_frame frame, t_ipos start, t_ipos end, int color)
{
	t_ipos	delta;
	int		steps;
	t_pos	pos;
	int		i;

	delta.x = end.x - start.x;
	delta.y = end.y - start.y;
	steps = abs(delta.x);
	if (abs(delta.y) > steps)
		steps = abs(delta.y);
	pos.x = (float) delta.x / steps;
	pos.y = (float) delta.y / steps;
	i = 0;
	while (i < steps)
	{
		if (start.x + pos.x * i >= 0 && start.x + pos.x * i < frame.width
			&& start.y + pos.y * i >= 0 && start.y + pos.y * i < frame.height)
			ft_put_pixel(frame, start.x + pos.x * i,
				start.y + pos.y * i, color);
		i++;
	}
}
