/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rendering.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:38:37 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/28 22:08:06 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

static void		ft_putstr(char *str);
static void		ft_print_help(void);

/**
 * @brief Initialize the MLX and start the rendering loop.
 * 
 * @param cub 	The game structure
 */
void	ft_rendering(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < cub->map_size.y)
	{
		j = 0;
		while (j < cub->map_size.x)
		{
			if (cub->map_array[i][j].type == 'N'
				|| cub->map_array[i][j].type == 'S'
				|| cub->map_array[i][j].type == 'W'
				|| cub->map_array[i][j].type == 'E')
				cub->map_array[i][j].type = '0';
			cub->map_array[i][j].is_solid = !!cub->textures \
				[(int) cub->map_array[i][j].type].type;
			j++;
		}
		i++;
	}
	ft_print_help();
	mlx_loop(cub->mlx);
}

static void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

static void	ft_print_help(void)
{
	ft_putstr("Commands :\n");
	ft_putstr("\n");
	ft_putstr("  > Esc        : Quit\n");
	ft_putstr("\n");
	ft_putstr("  > W or Up    : Move forward\n");
	ft_putstr("  > S or Down  : Move backward\n");
	ft_putstr("  > A or Left  : Rotate left\n");
	ft_putstr("  > D or Right : Rotate right\n");
	if (BONUS && HIDE_MOUSE)
		ft_putstr("  > Mouse (X)  : Rotate\n");
	if (BONUS)
		ft_putstr("\n  > E or Space : Open/Close doors\n");
	ft_putstr("\n");
	ft_putstr("  > I          : Toggle info\n");
	if (BONUS)
		ft_putstr("  > M or Tab   : Toggle minimap\n");
	ft_putstr("\n");
	ft_putstr("---\n");
}
