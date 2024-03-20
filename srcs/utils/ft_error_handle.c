/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_handle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:03:58 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/20 15:56:46 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_end(t_map *map, int status)
{
	int	i;
	int j;
	
	j = 0;
	i = 0;
	if (BONUS)
	{
		while (i < 128)
		{
			while (j < MAX_FRAME)
			{
				free(map->text[i].no[j]);
				free(map->text[i].so[j]);
				free(map->text[i].we[j]);
				free(map->text[i].ea[j]);
				j++;
			}
			i++;
			j = 0;
		}
	}
	free(map->ea);
	free(map->we);
	free(map->so);
	free(map->no);
	if (map->map_array)
		ft_free_array(map->map_array);
	if (map->map_array_copy)
		ft_free_array(map->map_array_copy);
	while (i <= 1023)
		close(i++);
	exit(status);
}

void	ft_error_handle(t_map *map, char *error, char *str, int status)
{
	if (str)
		ft_printf_error("%s%s\n", error, str);
	else
		ft_printf_error("%s\n", error);
	ft_free_end(map, status);
}

void	ft_error_handle_color(t_map *map, char *line)
{
	free(line);
	ft_error_handle(map, "Error\n", "Invalid color content", 1);
}
