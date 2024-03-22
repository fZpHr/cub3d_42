/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_file_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 22:34:42 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/22 15:39:31 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Check if the strncmp is valid, and if the default texture is full
 *
 * @param line line to check
 * @param str string to compare
 * @param i number of characters to compare
 * @return int 1 if the strncmp is valid, 0 otherwise
 */
int	ft_handle_strncmp(t_map *map, char **line, char *str, int i)
{
	if (map->text['1'].no[0] && map->text['1'].so[0] && map->text['1'].we[0]
		&& map->text['1'].ea[0])
		map->def_text = 1;
	if (map->def_text == 1)
	{
		if (ft_strncmp(line[0], str, i) == 0
			&& (line[1] != NULL && line[2] != NULL))
			return (1);
	}
	else if (ft_strncmp(line[0], str, i) == 0 && line[1] != NULL)
		return (1);
	return (0);
}

/**
 * @brief Check if the texure/color is full
 *
 * @param map struct of the map
 * @return int 1 if the texture/color is full, 0 otherwise
 */
int	ft_check_if_full(t_map *map)
{
	if (map->text['1'].no[0] && map->text['1'].so[0] && map->text['1'].we[0]
		&& map->text['1'].ea[0] && map->floor_c[0] != -1
		&& map->ceiling_c[0] != -1)
		return (1);
	return (0);
}

/**
 * @brief Check if the texture/color is valid
 *
 * @param map struct of the map
 * @param array_line split of the line
 * @return int 1 if the texture/color is invalid, 0 otherwise
 */
int	ft_check_texture_bonus(t_map *map, char **array_line)
{
	if (ft_handle_strncmp(map, array_line, "NO", 2) == 1)
		ft_handle_id(map, array_line, 0);
	else if (ft_handle_strncmp(map, array_line, "SO", 2) == 1)
		ft_handle_id(map, array_line, 1);
	else if (ft_handle_strncmp(map, array_line, "WE", 2) == 1)
		ft_handle_id(map, array_line, 2);
	else if (ft_handle_strncmp(map, array_line, "EA", 2) == 1)
		ft_handle_id(map, array_line, 3);
	else if (ft_handle_strncmp(map, array_line, "MP", 2) == 1
		|| ft_handle_strncmp(map, array_line, "SP", 2) == 1
		|| ft_handle_strncmp(map, array_line, "TY", 2) == 1)
		ft_handle_id(map, array_line, 4);
	else if (ft_strncmp(array_line[0], "F", 1) == 0 && array_line[1] != NULL)
	{
		if (ft_check_color_bonus(array_line, map->floor_c) == 1)
			return (1);
	}
	else if (ft_strncmp(array_line[0], "C", 1) == 0 && array_line[1] != NULL)
	{
		if (ft_check_color_bonus(array_line, map->ceiling_c) == 1)
			return (1);
	}
	else
		return (1);
	return (0);
}

void	ft_loop_bonus(t_map *map, char *line, char **array_line, int fd)
{
	int	i;

	i = 0;
	while (line)
	{
		array_line = ft_split(line, " ");
		map->map_position++;
		ft_skip_spaces(line, &i, 0);
		if (line[i] != '\0')
		{
			free(line);
			line = NULL;
			if (ft_check_texture_bonus(map, array_line) == 1)
			{
				ft_free_array(&array_line);
				ft_error_handle(map, "Error\n", "Invalid desc content", 1);
			}
		}
		free(line);
		ft_free_array(&array_line);
		if (ft_check_if_full(map) == 1)
			break ;
		line = get_next_line(fd);
		ft_cut_extra_char(line);
	}
}

/**
 * @brief Check if the map file is valid
 *
 * @param map struct of the map
 * @param line line of the map
 * @return void
 */
void	ft_check_map_file_bonus(t_map *map, char *file)
{
	int		fd;
	char	**array_line;
	char	*line;

	if (ft_strcmp(file + (ft_strlen(file) - 4), ".cub") != 0)
		ft_error_handle(map, "Invalid file format : ", file, 1);
	fd = open(file, O_RDWR);
	if (fd < 0)
	{
		ft_error_handle(map, "Error\n", "Invalid file", 1);
	}
	array_line = NULL;
	line = get_next_line(fd);
	ft_cut_extra_char(line);
	ft_loop_bonus(map, line, array_line, fd);
	ft_check_map_content(map, fd);
	close(fd);
}
