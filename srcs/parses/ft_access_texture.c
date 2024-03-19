/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_access_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:24:32 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/17 09:38:27 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Check if the texture extension is valid
 * 
 * @param map struct of the map
 * @param line current line of the file, content of the texture path
 * @return void
*/
void	ft_check_extension(t_map *map, char *line)
{
	if (ft_strncmp(line + (ft_strlen(line) - 4), ".xpm", 6) == 0)
		return ;
	else
	{
		printf("line = %s\n", line);
		free(line);
		ft_error_handle(map, "Error\n", "Invalid texture extension", 1);
	}
}

/**
 * @brief Check if the texture path is valid
 * 
 * @param map struct of the map
 * @param line current line of the file, content of the texture path
 * @param i index of the line
 * @return void
 */
void	ft_acces_texture(t_map *map, char *line, int i)
{
	int	fd;

	fd = open(line + i, __O_DIRECTORY);
	if (fd > 0)
	{
		free(line);
		ft_error_handle(map, "Error\n", "Invalid texture path", 1);
	}
	else
	{
		ft_check_extension(map, line);
		fd = open(line + i, O_RDONLY);
		if (fd < 0)
		{
			free(line);
			ft_error_handle(map, "Error\n", "Invalid texture path", 1);
			return ;
		}
		close(fd);
	}
}
