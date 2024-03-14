/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_function.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:24:55 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/14 21:11:42 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_skip_spaces(char *line, int *i, int *count)
{
	if (count == NULL)
	{
		while (line[*i] == ' ')
			(*i)++;
	}
	else
	{
		while (line[*i] == ' ')
		{
			(*i)++;
			(*count)++;
		}
	}
}

/**
 * @brief Cut the extra '\n' at the end of the string put by the get_next_line function
 * 
 * @param str string to cut
 * @return void
*/
void	cut_extra_char(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i] != '\0')
		i++;
	if (str[i - 1] == '\n')
		str[i - 1] = '\0';
}

/**
 * @brief Fill the line with 'A' character
 * 
 * @param line line to fill
 * @param size size of the line
 * @return void
*/
void	ft_fill_line(char *line, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		line[i] = 'A';
		i++;
	}
	line[i] = '\0';
}

void	ft_init_array(t_map *map, int l)
{
	int	j;

	j = 0;
	while (j < l)
	{
		map->map_array_copy[j] = (char *)malloc(sizeof(char)
				* (map->map_size_x + 1));
		if (!map->map_array[j])
		{
			while (j >= 0)
			{
				free(map->map_array[j]);
				j--;
			}
			free(map->map_array);
			ft_error_handle(map, "Error\n", "Malloc failed", 1);
		}
		j++;
	}
}

/**
 * @brief Copy the map array into a new array, to check if the map is close with wall with flood fill algorithm
 * 
 * @param map struct of the map
 * @return void
*/
void	ft_cp_array(t_map *map)
{
	int	i;
	int	j;
	int	l;

	l = map->map_size_y;
	j = 0;
	i = 0;
	map->map_array_copy = (char **)ft_malloc(sizeof(char *) * (l + 1));
	ft_init_array(map, l);
	while (j < map->map_size_y)
	{
		i = 0;
		while (map->map_array[j][i])
		{
			map->map_array_copy[j][i] = map->map_array[j][i];
			i++;
		}
		map->map_array_copy[j][i] = '\0';
		j++;
	}
	map->map_array_copy[j] = NULL;
}
