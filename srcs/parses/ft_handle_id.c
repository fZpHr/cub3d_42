/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_id.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:39:14 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/21 16:31:40 by hbelle           ###   ########.fr       */
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
 * 
 * @param map 			struct of the map
 * @param array_line 	splitted line
 * 
 * @return The id (otherwise it exits)
 */
int	ft_check_id(t_map *map, char **array_line)
{
	if (array_line[1] == NULL || array_line[1][1] != '\0')
	{
		ft_free_array(array_line);
		ft_error_handle(map, "Error\n", "Invalid id", 1);
	}
	return (array_line[1][0]);
}

/**
 * @brief add frame to the arrayls
 * @param frame frame to handle
 * @param array_line splitted line
 * @return void
 */
void	ft_handle_frame(t_map *map, char **frame, char **array_line)
{
	int	i;
	int j;

	j = 0;
	(void)map;
	while (array_line[j] != NULL)
		j++;
	i = 0;
	while (i < MAX_FRAME)
	{
		if (frame[i] != NULL)
			i++;
		else if (j == 2)
		{
			frame[i] = ft_strdup(array_line[1]);
			break ;
		}
		else if (j == 3)
		{
			frame[i] = ft_strdup(array_line[2]);
			break ;
		}

	}
}

void	ft_handle_option(t_map *map, char **array_line, int id)
{
	if (ft_handle_strncmp(map, array_line, "MP", 2) == 1)
		ft_handle_color_id(map, array_line, id);
	else if (ft_handle_strncmp(map, array_line, "SP", 2) == 1)
	{
		map->text[id].sp = ft_atoi(array_line[2]);
		if (map->text[id].sp < 0 || map->text[id].sp > 1000)
		{
			ft_free_array(array_line);
			ft_error_handle(map, "Error\n", "Invalid speed", 1);
		}
	}
	else if (ft_handle_strncmp(map, array_line, "TY", 1) == 1)
	{
		map->text[id].ty = ft_atoi(array_line[2]);
		if (map->text[id].ty < 0 || map->text[id].ty > 1)
		{
			ft_free_array(array_line);
			ft_error_handle(map, "Error\n", "Invalid type", 1);
		}
	}
}



int	ft_nb_arg(t_map *map, char **array_line, int i)
{
	int	j;

	j = 0;
	while (array_line[j] != NULL)
		j++;
	if (j < 2)
	{
		ft_free_array(array_line);
		ft_error_handle(map, "Error\n", "Invalid desc content", 1);
	}
	else if (j == 2)
	{
		ft_cut_extra_char(array_line[1]);
		if (ft_acces_texture(array_line[1], 0) == 1)
		{
			ft_free_array(array_line);
			ft_error_handle(map, "Error\n", "Invalid texture path", 1);
		}
		if (i == 0)
			ft_handle_frame(map, map->text['1'].no, array_line);
		else if (i == 1)
			ft_handle_frame(map, map->text['1'].so, array_line);
		else if (i == 2)
			ft_handle_frame(map, map->text['1'].we, array_line);
		else if (i == 3)
			ft_handle_frame(map, map->text['1'].ea, array_line);
		else if (i == 4)
			ft_handle_option(map, array_line, '1');
		return (1);
	}
	return (0);
}

/**
 * @brief Handle the id
 * @param map struct of the map
 * @param array_line splitted line
 * @param i parameter to know which texture to handle
 * @return void
 */
void	ft_handle_id(t_map *map, char **array_line, int i)
{
	int	id;

	if (map->def_text == 0)
		if (ft_nb_arg(map, array_line, i) == 1)
			return;
	id = ft_check_id(map, array_line);
	map->text[id].no_idx = id;
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
		ft_handle_frame(map, map->text[id].no, array_line);
	else if (i == 1)
		ft_handle_frame(map, map->text[id].so, array_line);
	else if (i == 2)
		ft_handle_frame(map, map->text[id].we, array_line);
	else if (i == 3)
		ft_handle_frame(map, map->text[id].ea, array_line);
	else if (i == 4)
		ft_handle_option(map, array_line, id);
}
