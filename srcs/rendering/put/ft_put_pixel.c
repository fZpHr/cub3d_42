/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:07:32 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/28 22:08:06 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

/**
 * @brief Set the pixel of the frame at the given position
 * 			to the given color using addresses.
 * 
 * @param frame 	The frame to edit
 * @param x 		The x position of the pixel
 * @param y 		The y position of the pixel
 * @param color 	The color to set (in ARGB format)
 */
void	ft_put_pixel(t_frame frame, int x, int y, int color)
{
	char	*dst;

	dst = frame.addr + (y * frame.line_size + x * (frame.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
