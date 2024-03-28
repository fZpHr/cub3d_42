/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assign_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:26:45 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/28 19:20:01 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"

static void	ft_assign_no(t_cub *cub, t_map *map, int i);
static void	ft_assign_so(t_cub *cub, t_map *map, int i);
static void	ft_assign_we(t_cub *cub, t_map *map, int i);
static void	ft_assign_ea(t_cub *cub, t_map *map, int i);

void	ft_assign_textures(t_cub *cub, t_map *map)
{
	int	i;

	i = 0;
	while (i < 128)
	{
		ft_assign_no(cub, map, i);
		ft_assign_so(cub, map, i);
		ft_assign_we(cub, map, i);
		ft_assign_ea(cub, map, i);
		cub->textures[i].empty = FALSE;
		if (i == '0' || i == 'O'
			|| i == 'N' || i == 'S' || i == 'E' || i == 'W')
			cub->textures[i].type = 0;
		else
			cub->textures[i].type = 1;
		i++;
	}
}

static void	ft_assign_no(t_cub *cub, t_map *map, int i)
{
	cub->textures[i].no = ft_calloc(MAX_FRAME + 1, sizeof(t_frame));
	cub->textures[i].no_anim_count = 1;
	cub->textures[i].no[0] = ft_load_texture(cub, map->no);
	if (cub->textures[i].no[0].img == NULL)
	{
		ft_error_handle(map, "Error\n", "Can't load texture", -42);
		ft_game_quit(cub, 1);
	}
}

static void	ft_assign_so(t_cub *cub, t_map *map, int i)
{
	cub->textures[i].so = ft_calloc(MAX_FRAME + 1, sizeof(t_frame));
	cub->textures[i].so_anim_count = 1;
	cub->textures[i].so[0] = ft_load_texture(cub, map->so);
	if (cub->textures[i].so[0].img == NULL)
	{
		ft_error_handle(map, "Error\n", "Can't load texture", -42);
		ft_game_quit(cub, 1);
	}
}

static void	ft_assign_we(t_cub *cub, t_map *map, int i)
{
	cub->textures[i].we = ft_calloc(MAX_FRAME + 1, sizeof(t_frame));
	cub->textures[i].we_anim_count = 1;
	cub->textures[i].we[0] = ft_load_texture(cub, map->we);
	if (cub->textures[i].we[0].img == NULL)
	{
		ft_error_handle(map, "Error\n", "Can't load texture", -42);
		ft_game_quit(cub, 1);
	}
}

static void	ft_assign_ea(t_cub *cub, t_map *map, int i)
{
	cub->textures[i].ea = ft_calloc(MAX_FRAME + 1, sizeof(t_frame));
	cub->textures[i].ea_anim_count = 1;
	cub->textures[i].ea[0] = ft_load_texture(cub, map->ea);
	if (cub->textures[i].ea[0].img == NULL)
	{
		ft_error_handle(map, "Error\n", "Can't load texture", -42);
		ft_game_quit(cub, 1);
	}
}
