/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:22:23 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/12 19:07:55 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_init(t_map *cube)
{
	cube->map_array = NULL;
	cube->no = NULL;
	cube->so = NULL;
	cube->we = NULL;
	cube->ea = NULL;
	cube->floor[0] = -1;
	cube->ceiling[0] = -1;
	cube->player_direction[0] = 0;
	cube->player_direction[1] = 0;
	cube->player_direction[2] = 0;
	cube->player_direction[3] = 0;
	cube->player_position[0] = 0;
	cube->player_position[1] = 0;
	cube->map_size_y = 0;
	cube->map_size_x = 0;
	cube->map_position = 0;
}