/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:08:11 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/17 11:08:24 by ysabik           ###   ########.fr       */
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
	int		dx;
	int		dy;
	int		steps;
	float	x;
	float	y;

	dx = end.x - start.x;
	dy = end.y - start.y;
	steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	x = (float) dx / steps;
	y = (float) dy / steps;
	for (int i = 0; i < steps; i++)
	{
		ft_put_pixel(frame, start.x + x * i, start.y + y * i, color);
	}
}
