/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:00:16 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/12 20:54:40 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_loop_map(t_map *cube, char *line, int fd)
{
	int full;

	full = 0;
	while (line)
	{
		cube->map_position++;
		ft_check_texture(cube, line);
		free(line);
		if (cube->no && cube->so && cube->we && cube->ea
			&& cube->floor[0] != -1 && cube->ceiling[0] != -1)
		{
			full = 1;
			break;
		}
		line = get_next_line(fd);
		cut_extra_char(line);
	}
	if (full == 0)
		ft_error_handle("Error\n", "Invalid map", 1);
	ft_check_map_content(cube, fd);
	close(fd);
}

void	ft_check_map_file(t_map *cube, char *map)
{
	int		fd;
	char	*line;

	if (ft_strcmp(map + (ft_strlen(map) - 4), ".cub") != 0)
		ft_error_handle("Invalid file format : ", map, 1);
	fd = open(map, O_RDONLY);
	if (fd < 0)
		ft_error_handle("Invalid file : ", map, 1);
	line = get_next_line(fd);
	cut_extra_char(line);
	if (!line)
	{
		free(line);
		close(fd);
		ft_error_handle("Error\n", "Empty file", 1);
	}
	else
	{
		ft_loop_map(cube, line, fd);
		close(fd);
	}
}

