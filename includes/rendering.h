/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:07:39 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/15 15:55:14 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# include "cub3d.h"
# include <X11/keysym.h>

/**
 * @brief Result of a single ray casting
 * 
 * @param x 		X position of the collision
 * @param y 		Y position of the collision
 * @param angle 	Angle of the ray
 * @param distance 	Distance between the throwing and the hitting point
 * 					(-1 if no collision)
*/
typedef struct s_casting
{
	float	x;
	float	y;
	float	angle;
	float	distance;
}	t_casting;


enum e_mlx_events {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

enum e_mlx_masks {
	MASK_NO_MASK = 0L,
	MASK_KEY_PRESS = 1L<<0,
	MASK_KEY_RELEASE = 1L<<1,
	MASK_BUTTON_PRESS = 1L<<2,
	MASK_BUTTON_RELEASE = 1L<<3,
	MASK_ENTER_WINDOW = 1L<<4,
	MASK_LEAVE_WINDOW = 1L<<5,
	MASK_MOUSE_MOVE = 1L<<6,
	MASK_MOUSE_MOVE_HINT = 1L<<7,
	MASK_BUTTON1_MOTION = 1L<<8,
	MASK_BUTTON2_MOTION = 1L<<9,
	MASK_BUTTON3_MOTION = 1L<<10,
	MASK_BUTTON4_MOTION = 1L<<11,
	MASK_BUTTON5_MOTION = 1L<<12,
	MASK_BUTTON_MOTION = 1L<<13,
	MASK_KEYMAP_STATE = 1L<<14,
	MASK_EXPOSE = 1L<<15,
	MASK_VISIBILITY_CHANGE = 1L<<16,
	MASK_DESTROY = 1L<<17,
	MASK_RESIZE_REDIRECT = 1L<<18,
	MASK_SUBSTRUCTURE_NOTIFY = 1L<<19,
	MASK_SUBSTRUCTURE_REDIRECT = 1L<<20,
	MASK_FOCUS_CHANGE = 1L<<21,
	MASK_PROPERTY_CHANGE = 1L<<22,
	MASK_COLORMAP_CHANGE = 1L<<23,
	MASK_OWNER_GRAB_BUTTON = 1L<<24
};

#endif
