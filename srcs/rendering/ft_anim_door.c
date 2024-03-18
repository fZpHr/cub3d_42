/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_anim_door.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:15:04 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/18 17:17:05 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

static void	ft_update_no(t_texture *t);
static void	ft_update_so(t_texture *t);
static void	ft_update_we(t_texture *t);
static void	ft_update_ea(t_texture *t);

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
	ft_update_no(t);
	ft_update_so(t);
	ft_update_we(t);
	ft_update_ea(t);
	if (!t->no_anim && !t->so_anim && !t->we_anim && !t->ea_anim)
		t->empty = TRUE;
}

static void	ft_update_no(t_texture *t)
{
	if (t->no_anim && t->no_anim_count > 1)
	{
		t->no_anim_num++;
		if (t->no_anim_num >= t->no_anim_count)
			t->no_anim = FALSE;
	}
}

static void	ft_update_so(t_texture *t)
{
	if (t->so_anim && t->so_anim_count > 1)
	{
		t->so_anim_num++;
		if (t->so_anim_num >= t->so_anim_count)
			t->so_anim = FALSE;
	}
}

static void	ft_update_we(t_texture *t)
{
	if (t->we_anim && t->we_anim_count > 1)
	{
		t->we_anim_num++;
		if (t->we_anim_num >= t->we_anim_count)
			t->we_anim = FALSE;
	}
}

static void	ft_update_ea(t_texture *t)
{
	if (t->ea_anim && t->ea_anim_count > 1)
	{
		t->ea_anim_num++;
		if (t->ea_anim_num >= t->ea_anim_count)
			t->ea_anim = FALSE;
	}
}
