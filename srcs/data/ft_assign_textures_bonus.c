/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assign_textures_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:50:18 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/28 19:19:42 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"

static void	ft_assign_no(t_cub *cub, t_map *map, int i);
static void	ft_assign_so(t_cub *cub, t_map *map, int i);
static void	ft_assign_we(t_cub *cub, t_map *map, int i);
static void	ft_assign_ea(t_cub *cub, t_map *map, int i);

void	ft_assign_textures_bonus(t_cub *cub, t_map *map)
{
	int	i;

	i = -1;
	while (++i < 128)
	{
		ft_assign_no(cub, map, i);
		ft_assign_so(cub, map, i);
		ft_assign_we(cub, map, i);
		ft_assign_ea(cub, map, i);
		cub->textures[i].empty = cub->textures[i].no_anim_count == 0
			&& cub->textures[i].so_anim_count == 0
			&& cub->textures[i].we_anim_count == 0
			&& cub->textures[i].ea_anim_count == 0;
		if (map->text[i].sp != -1)
			cub->textures[i].anim_delay = map->text[i].sp;
		if (map->text[i].mp != -1)
			cub->textures[i].map_color = map->text[i].mp;
		if (map->text[i].ty != -1)
			cub->textures[i].type = !!map->text[i].ty;
		else if (i == '0' || i == 'O'
			|| i == 'N' || i == 'S' || i == 'E' || i == 'W')
			cub->textures[i].type = 0;
		else
			cub->textures[i].type = 1;
	}
}

static void	ft_assign_no(t_cub *cub, t_map *map, int i)
{
	int	j;

	cub->textures[i].no = ft_calloc(MAX_FRAME + 1, sizeof(t_frame));
	cub->textures[i].no_anim_count = 0;
	j = -1;
	while (++j < MAX_FRAME)
	{
		if (!map->text[i].no[j])
			continue ;
		cub->textures[i].no[j] = ft_load_texture(cub, map->text[i].no[j]);
		if (cub->textures[i].no[j].img == NULL)
		{
			ft_error_handle(map, "Error\n", "Can't load texture", -42);
			ft_game_quit(cub, 1);
		}
		cub->textures[i].no_anim_count++;
	}
}

static void	ft_assign_so(t_cub *cub, t_map *map, int i)
{
	int	j;

	cub->textures[i].so = ft_calloc(MAX_FRAME + 1, sizeof(t_frame));
	cub->textures[i].so_anim_count = 0;
	j = -1;
	while (++j < MAX_FRAME)
	{
		if (!map->text[i].so[j])
			continue ;
		cub->textures[i].so[j] = ft_load_texture(cub, map->text[i].so[j]);
		if (cub->textures[i].so[j].img == NULL)
		{
			ft_error_handle(map, "Error\n", "Can't load texture", -42);
			ft_game_quit(cub, 1);
		}
		cub->textures[i].so_anim_count++;
	}
}

static void	ft_assign_we(t_cub *cub, t_map *map, int i)
{
	int	j;

	cub->textures[i].we = ft_calloc(MAX_FRAME + 1, sizeof(t_frame));
	cub->textures[i].we_anim_count = 0;
	j = -1;
	while (++j < MAX_FRAME)
	{
		if (!map->text[i].we[j])
			continue ;
		cub->textures[i].we[j] = ft_load_texture(cub, map->text[i].we[j]);
		if (cub->textures[i].we[j].img == NULL)
		{
			ft_error_handle(map, "Error\n", "Can't load texture", -42);
			ft_game_quit(cub, 1);
		}
		cub->textures[i].we_anim_count++;
	}
}

static void	ft_assign_ea(t_cub *cub, t_map *map, int i)
{
	int	j;

	cub->textures[i].ea = ft_calloc(MAX_FRAME + 1, sizeof(t_frame));
	cub->textures[i].ea_anim_count = 0;
	j = -1;
	while (++j < MAX_FRAME)
	{
		if (!map->text[i].ea[j])
			continue ;
		cub->textures[i].ea[j] = ft_load_texture(cub, map->text[i].ea[j]);
		if (cub->textures[i].ea[j].img == NULL)
		{
			ft_error_handle(map, "Error\n", "Can't load texture", -42);
			ft_game_quit(cub, 1);
		}
		cub->textures[i].ea_anim_count++;
	}
}
