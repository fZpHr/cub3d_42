/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_doors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:27:07 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/18 17:11:54 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

/**
 * @brief Handle the doors opening
 * 
 * @param cub 	The game structure
 */
void	ft_handle_doors(t_cub *cub)
{
	int			i;
	int			j;
	t_texture	*t;

	i = 0;
	while (i < cub->map_size.y)
	{
		j = 0;
		while (j < cub->map_size.x)
		{
			if (cub->map_array[i][j].type == '-')
			{
				t = &cub->textures['-'];
				if (t->empty)
				{
					cub->map_array[i][j].type = 'O';
					cub->map_array[i][j].is_solid = FALSE;
				}
			}
			j++;
		}
		i++;
	}
}
