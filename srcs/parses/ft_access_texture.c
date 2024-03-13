/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_access_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:24:32 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/13 17:43:59 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_check_extension(t_map *cube, char *line)
{
	if (ft_strncmp(line + (ft_strlen(line) - 4), ".xpm", 4) == 0)
		return ;
	else if (ft_strncmp(line + (ft_strlen(line) - 4), ".png", 4) == 0)
		return ;
	else if (ft_strncmp(line + (ft_strlen(line) - 4), ".bmp", 4) == 0)
		return ;
	else
	{
		free(line);
		ft_error_handle(cube, "Error\n", "Invalid texture extension", 1);
	}
}

void	ft_acces_texture(t_map *cube, char *line, int i)
{
	int	fd;

	fd = open(line + i, __O_DIRECTORY);
	if (fd > 0)
	{
		free(line);
		ft_error_handle(cube, "Error\n", "Invalid texture path", 1);
	}
	else
	{
		close(fd);
		ft_check_extension(cube, line);
		fd = open(line + i, O_RDONLY);
		if (fd < 0)
		{
			free(line);
			ft_error_handle(cube, "Error\n", "Invalid texture path", 1);
		}
		close(fd);
	}
}
