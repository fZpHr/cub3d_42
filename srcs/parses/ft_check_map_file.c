/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:00:16 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/15 19:43:12 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_loop_map(t_map *map, char *line, int fd, int full)
{
	while (line)
	{
		map->map_position++;
		if (ft_check_texture(map, line) == 1)
		{
			free(line);
			ft_error_handle(map, "Error\n", "Invalid description content", 1);
		}
		if (map->no && map->so && map->we && map->ea
			&& map->floor_c[0] != -1 && map->ceiling_c[0] != -1)
		{
			full = 1;
			break ;
		}
		free(line);
		line = get_next_line(fd);
		ft_cut_extra_char(line);
	}
	free(line);
	if (full == 0)
		ft_error_handle(map, "Error\n", "Invalid description content", 1);
	ft_check_map_content(map, fd);
	close(fd);
}

/**
 * @brief Check if the file is a .cub file and open it
 * 
 * @param map struct of the map
 * @param map_file name of the file
 * @return void
*/
void	ft_check_map_file(t_map *map, char *map_file)
{
	int		fd;
	char	*line;
	int		full;

	full = 0;
	if (ft_strcmp(map_file + (ft_strlen(map_file) - 4), ".cub") != 0)
		ft_error_handle(map, "Invalid file format : ", map_file, 1);
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		ft_error_handle(map, "Invalid file : ", map_file, 1);
	line = get_next_line(fd);
	ft_cut_extra_char(line);
	if (!line)
	{
		free(line);
		close(fd);
		ft_error_handle(map, "Error\n", "Empty file", 1);
	}
	else
	{
		ft_loop_map(map, line, fd, full);
		close(fd);
	}
}
