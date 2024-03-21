/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:22:23 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/21 07:14:24 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_bonus(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 128)
	{
		j = -1;
		while (++j < MAX_FRAME)
		{
			map->text[i].no[j] = NULL;
			map->text[i].so[j] = NULL;
			map->text[i].we[j] = NULL;
			map->text[i].ea[j] = NULL;
		}
		map->text[i].no_idx = -1;
		map->text[i].so_idx = -1;
		map->text[i].we_idx = -1;
		map->text[i].ea_idx = -1;
		map->text[i].mp = -1;
		map->text[i] = (t_text){0};
	}
	map->mp_c[0] = -1;
	map->mp_c[1] = -1;
	map->mp_c[2] = -1;
}

void	ft_init(t_map *map)
{
	if (BONUS)
		ft_init_bonus(map);
	map->map_array = NULL;
	map->map_array_copy = NULL;
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->floor_c[0] = -1;
	map->ceiling_c[0] = -1;
	map->player_direction[0] = 0;
	map->player_direction[1] = 0;
	map->player_direction[2] = 0;
	map->player_direction[3] = 0;
	map->player_position[0] = 0;
	map->player_position[1] = 0;
	map->map_size_y = 0;
	map->map_size_x = 0;
	map->map_position = 0;
}
