/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rendering.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:38:37 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/20 05:04:25 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

/**
 * @brief Initialize the MLX and start the rendering loop.
 * 
 * @param cub 	The game structure
*/
void	ft_rendering(t_cub *cub)
{


	for (int i = 0; i < cub->map_size.y; i++)
	{
		for (int j = 0; j < cub->map_size.x; j++)
		{
			if (cub->map_array[i][j].type == 'N'
				|| cub->map_array[i][j].type == 'S'
				|| cub->map_array[i][j].type == 'W'
				|| cub->map_array[i][j].type == 'E')
				cub->map_array[i][j].type = '0';
			cub->map_array[i][j].is_solid = cub->textures[(int) cub->map_array[i][j].type].no != NULL;
		}
	}

	printf("Commands :\n");
	printf("\n");
	printf("  > Esc        : Quit\n");
	printf("\n");
	printf("  > W or Up    : Move forward\n");
	printf("  > S or Down  : Move backward\n");
	printf("  > A or Left  : Rotate left\n");
	printf("  > D or Right : Rotate right\n");
	if (BONUS && HIDE_MOUSE)
		printf("  > Mouse (X)  : Rotate\n");
	if (BONUS)
		printf("\n  > E or Space : Open/Close doors\n");
	printf("\n");
	printf("  > I          : Toggle info\n");
	if (BONUS)
		printf("  > M or Tab   : Toggle minimap\n");
	printf("\n");
	printf("---\n");

	mlx_loop(cub->mlx);
}


