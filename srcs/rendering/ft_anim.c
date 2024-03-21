/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_anim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:07:00 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/21 02:37:41 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

static void	ft_update_no(t_texture *t);
static void	ft_update_so(t_texture *t);
static void	ft_update_we(t_texture *t);
static void	ft_update_ea(t_texture *t);

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
			ft_anim_door(t);
		if (i == (int) '-')
			continue ;
		if (t->anim_counter < t->anim_delay)
		{
			t->anim_counter++;
			continue ;
		}
		t->anim_counter = 0;
		ft_update_no(t);
		ft_update_so(t);
		ft_update_we(t);
		ft_update_ea(t);
	}
}

static void	ft_update_no(t_texture *t)
{
	if (t->no_anim && t->no_anim_count > 1)
	{
		t->no_anim_num++;
		if (t->no_anim_num >= t->no_anim_count)
			t->no_anim_num = 0;
	}
}

static void	ft_update_so(t_texture *t)
{
	if (t->so_anim && t->so_anim_count > 1)
	{
		t->so_anim_num++;
		if (t->so_anim_num >= t->so_anim_count)
			t->so_anim_num = 0;
	}
}

static void	ft_update_we(t_texture *t)
{
	if (t->we_anim && t->we_anim_count > 1)
	{
		t->we_anim_num++;
		if (t->we_anim_num >= t->we_anim_count)
			t->we_anim_num = 0;
	}
}

static void	ft_update_ea(t_texture *t)
{
	if (t->ea_anim && t->ea_anim_count > 1)
	{
		t->ea_anim_num++;
		if (t->ea_anim_num >= t->ea_anim_count)
			t->ea_anim_num = 0;
	}
}
