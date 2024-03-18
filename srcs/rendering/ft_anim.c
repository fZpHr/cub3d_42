/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_anim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student->42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:07:00 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/18 16:14:02 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

void	ft_anim_door(t_texture *t)
{
	if (t->no_anim && t->no_anim_count <= 1)
		t->no_anim = FALSE;
	if (t->so_anim && t->so_anim_count <= 1)
		t->so_anim = FALSE;
	if (t->we_anim && t->we_anim_count <= 1)
		t->we_anim = FALSE;
	if (t->ea_anim && t->ea_anim_count <= 1)
		t->ea_anim = FALSE;
	if (t->anim_counter < t->anim_delay)
	{
		t->anim_counter++;
		return ;
	}
	t->anim_counter = 0;
	if (t->no_anim && t->no_anim_count > 1)
	{
		t->no_anim_num++;
		if (t->no_anim_num >= t->no_anim_count)
			t->no_anim = FALSE;
	}
	if (t->so_anim && t->so_anim_count > 1)
	{
		t->so_anim_num++;
		if (t->so_anim_num >= t->so_anim_count)
			t->so_anim = FALSE;
	}
	if (t->we_anim && t->we_anim_count > 1)
	{
		t->we_anim_num++;
		if (t->we_anim_num >= t->we_anim_count)
			t->we_anim = FALSE;
	}
	if (t->ea_anim && t->ea_anim_count > 1)
	{
		t->ea_anim_num++;
		if (t->ea_anim_num >= t->ea_anim_count)
			t->ea_anim = FALSE;
	}
	if (!t->no_anim && !t->so_anim && !t->we_anim && !t->ea_anim)
		t->empty = TRUE;
}

/**
 * @brief Handle the animation.
 * 
 * @param cub 	The game structure
 */
void	ft_anim(t_cub *cub)
{
	int			i;
	t_texture	*t;

	i = -1;
	while (i < 127)
	{
		i++;
		t = &cub->textures[i];
		if (cub->textures[i].empty)
			continue ;
		if (i == (int) '-')
		{
			ft_anim_door(t);
			continue ;
		}
		if (t->anim_counter < t->anim_delay)
		{
			t->anim_counter++;
			continue ;
		}
		t->anim_counter = 0;
		if (t->no_anim && t->no_anim_count > 1)
		{
			t->no_anim_num++;
			if (t->no_anim_num >= t->no_anim_count)
				t->no_anim_num = 0;
		}
		if (t->so_anim && t->so_anim_count > 1)
		{
			t->so_anim_num++;
			if (t->so_anim_num >= t->so_anim_count)
				t->so_anim_num = 0;
		}
		if (t->we_anim && t->we_anim_count > 1)
		{
			t->we_anim_num++;
			if (t->we_anim_num >= t->we_anim_count)
				t->we_anim_num = 0;
		}
		if (t->ea_anim && t->ea_anim_count > 1)
		{
			t->ea_anim_num++;
			if (t->ea_anim_num >= t->ea_anim_count)
				t->ea_anim_num = 0;
		}
	}
}
