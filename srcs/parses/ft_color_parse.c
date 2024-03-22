/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:47:53 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/22 16:33:40 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_end_color(int *color)
{
	if (color[0] < 0 || color[0] > 255 || color[1] < 0 || color[1] > 255
		|| color[2] < 0 || color[2] > 255)
		return (1);
	return (0);
}

/**
 * @brief Check if the color is valid
 *
 * @param line line to check
 * @param color array of the color
 * @return int 1 if the color is invalid, 0 otherwise
 */
int	ft_check_color_bonus_options(char **line, int *color)
{
	int	i;

	i = 0;
	line = ft_handle_space(line, i, 3);
	color[0] = ft_atoi(line[2] + i);
	ft_loop_color_bonus(line[2], &i);
	if (line[2][i] != ',')
		return (1);
	i++;
	color[1] = ft_atoi(line[2] + i);
	ft_loop_color_bonus(line[2], &i);
	if (line[2][i] != ',')
		return (1);
	i++;
	if (line[2][i] == '\n' || line[2][i] == '\0')
		return (1);
	color[2] = ft_atoi(line[2] + i);
	ft_loop_color_bonus(line[2], &i);
	if ((line[2][i] != '\n' && line[2][i] != '\0') || line[2][i] != '\0'
		|| line[2][i] == ' ')
		return (1);
	ft_free_array(&line);
	if (ft_end_color(color) == 1)
		return (1);
	return (0);
}

void	ft_loop_color_bonus(char *line, int *i)
{
	while ((line[(*i)] >= '0' && line[(*i)] <= '9') || line[(*i)] == ' ')
		(*i)++;
}

/**
 * @brief Handle the option MP, SP, TY of the texture
 * 
 * @param map struct of the map
 * @param array_line splitted line
 * @param id id of the texture
 * 
 * @return void
*/
void	ft_handle_option(t_map *map, char **array_line, int id)
{
	if (ft_handle_strncmp(map, array_line, "MP", 2) == 1)
		ft_handle_color_id(map, array_line, id);
	else if (ft_handle_strncmp(map, array_line, "SP", 2) == 1)
	{
		map->text[id].sp = ft_atoi(array_line[2]);
		if (map->text[id].sp < 0 || map->text[id].sp > 1000)
		{
			ft_free_array(&array_line);
			ft_error_handle(map, "Error\n", "Invalid speed", 1);
		}
	}
	else if (ft_handle_strncmp(map, array_line, "TY", 1) == 1)
	{
		map->text[id].ty = ft_atoi(array_line[2]);
		if (map->text[id].ty < 0 || map->text[id].ty > 1)
		{
			ft_free_array(&array_line);
			ft_error_handle(map, "Error\n", "Invalid type", 1);
		}
	}
}

/**
 * @brief Check if the color is valid
 *
 * @param line line to check
 * @param color array of the color
 * @return int 1 if the color is invalid, 0 otherwise
 */
int	ft_check_color_bonus(char **line, int *color)
{
	int	i;

	i = 0;
	line = ft_handle_space(line, i, 2);
	color[0] = ft_atoi(line[1] + i);
	ft_loop_color_bonus(line[1], &i);
	if (line[1][i] != ',')
		return (1);
	i++;
	color[1] = ft_atoi(line[1] + i);
	ft_loop_color_bonus(line[1], &i);
	if (line[1][i] != ',')
		return (1);
	i++;
	if (line[1][i] == '\n' || line[1][i] == '\0')
		return (1);
	color[2] = ft_atoi(line[1] + i);
	ft_loop_color_bonus(line[1], &i);
	if ((line[1][i] != '\n' && line[1][i] != '\0') || line[1][i] != '\0'
		|| line[1][i] == ' ')
		return (1);
	ft_free_array(&line);
	if (ft_end_color(color) == 1)
		return (1);
	return (0);
}
