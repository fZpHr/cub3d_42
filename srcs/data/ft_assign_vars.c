/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assign_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:37:15 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/28 18:45:07 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"

static void	ft_assign_init(t_cub *cub);

void	ft_assign_vars(t_cub *cub)
{
	cub->frames = 0;
	cub->minimap = BONUS;
	cub->info = FALSE;
	cub->border_c = 0;
	ft_assign_init(cub);
	cub->textures[(int) '1'].map_color = 0xFF000000;
}

static void	ft_assign_init(t_cub *cub)
{
	static int	i = -1;

	while (++i < 128)
	{
		cub->textures[i].empty = TRUE;
		cub->textures[i].no = NULL;
		cub->textures[i].no_anim_count = 0;
		cub->textures[i].no_anim_num = 0;
		cub->textures[i].no_anim = TRUE;
		cub->textures[i].so = NULL;
		cub->textures[i].so_anim_count = 0;
		cub->textures[i].so_anim_num = 0;
		cub->textures[i].so_anim = TRUE;
		cub->textures[i].we = NULL;
		cub->textures[i].we_anim_count = 0;
		cub->textures[i].we_anim_num = 0;
		cub->textures[i].we_anim = TRUE;
		cub->textures[i].ea = NULL;
		cub->textures[i].ea_anim_count = 0;
		cub->textures[i].ea_anim_num = 0;
		cub->textures[i].ea_anim = TRUE;
		cub->textures[i].anim_delay = 16;
		cub->textures[i].anim_counter = 0;
		cub->textures[i].map_color = 0x00000000;
	}
}
