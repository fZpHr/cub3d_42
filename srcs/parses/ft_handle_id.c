/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_id.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:39:14 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/19 17:41:55 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Check if the color is valid
 *
 * @param line line to check
 * @param color array of the color
 * @return int 1 if the color is invalid, 0 otherwise
 */
int	ft_check_color_bonus(char *line, int *color)
{
	int	i;

	i = 0;
	color[0] = ft_atoi(line + i);
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	if (line[i] != ',')
		return (1);
	i++;
	color[1] = ft_atoi(line + i);
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	if (line[i] != ',')
		return (1);
	i++;
	color[2] = ft_atoi(line + i);
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	if ((line[i] != '\n' && line[i] != '\0') || line[i] != '\0'
		|| line[i] == ' ')
		return (1);
	if (color[0] < 0 || color[0] > 255 || color[1] < 0 || color[1] > 255
		|| color[2] < 0 || color[2] > 255)
		return (1);
	return (0);
}

void	ft_handle_color_id(t_map *map, char **array_line, int id)
{
	if (ft_check_color_bonus(array_line[2], map->mp_c) == 1)
	{
		ft_free_array(array_line);
		ft_error_handle(map, "Error\n", "Invalid color", 1);
	}
	map->text[id].mp = (map->mp_c[0] << 16) + (map->mp_c[1] << 8)
		+ map->mp_c[2];
}

/**
 * @brief Check if the id is valid
 * @param map struct of the map
 * @param array_line split of the line
 * @return int 1 if the texture/color is invalid, 0 otherwise
 */
int	ft_check_id(t_map *map, char **array_line)
{
	int	tmp;

	tmp = ft_atoi(array_line[1]);
	if (array_line[1] == NULL)
	{
		ft_free_array(array_line);
		ft_error_handle(map, "Error\n", "Invalid id", 1);
	}
	if (array_line[1][1] != '\0')
	{
		ft_free_array(array_line);
		ft_error_handle(map, "Error\n", "Invalid id", 1);
	}
	if (tmp < 0 || tmp > 128)
	{
		ft_free_array(array_line);
		ft_error_handle(map, "Error\n", "Invalid id", 1);
	}
	return (tmp);
}

/**
 * @brief Handle the id
 * @param map struct of the map
 * @param array_line split of the line
 * @param i parameter to know which texture to handle
 * @return void
 */
void	ft_handle_id(t_map *map, char **array_line, int i)
{
	int	id;

	id = ft_check_id(map, array_line);
	if (i != 4)
	{
		ft_cut_extra_char(array_line[2]);
		if (ft_acces_texture(array_line[2], 0) == 1)
		{
			ft_free_array(array_line);
			ft_error_handle(map, "Error\n", "Invalid texture path", 1);
		}
	}
	if (i == 0)
		map->text[id].no = ft_strdup(array_line[2]);
	else if (i == 1)
		map->text[id].so = ft_strdup(array_line[2]);
	else if (i == 2)
		map->text[id].we = ft_strdup(array_line[2]);
	else if (i == 3)
		map->text[id].ea = ft_strdup(array_line[2]);
	else if (i == 4)
		ft_handle_color_id(map, array_line, id);
}
