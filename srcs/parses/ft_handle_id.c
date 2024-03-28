/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_id.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:39:14 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/28 22:10:39 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Handle space between color
 * 
 * @param array_line 	splitted line
 * @param i 			current i
 * @param opt 			number of arguments.
 * 
 * @return char** of the new array
 */
char	**ft_handle_space(char **array_line, int i, int opt)
{
	char	**tmp;
	int		j;

	j = 0;
	i = 0;
	while (array_line[i])
		i++;
	if (i >= opt)
	{
		tmp = malloc(sizeof(char *) * (opt + 1));
		while (j < opt)
		{
			tmp[j] = ft_strdup(array_line[j]);
			j++;
		}
		tmp[j] = NULL;
		i = opt;
		while (array_line[i])
		{
			tmp[1] = ft_strjoin(tmp[1], array_line[i]);
			i++;
		}
	}
	return (tmp);
}

/**
 * @brief Handle the color id
 * 
 * @param map 			struct of the map
 * @param array_line 	splitted line
 * @param id 			id of the texture
 */
void	ft_handle_color_id(t_map *map, char **array_line, int id)
{
	if (ft_check_color_bonus_options(array_line, map->mp_c) == 1)
	{
		ft_free_array(&array_line);
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
		ft_free_array(&array_line);
		ft_error_handle(map, "Error\n", "Invalid id", 1);
	}
	return (array_line[1][0]);
}

/**
 * @brief Check if the default texture is valid
 * 
 * @param map 			struct of the map
 * @param array_line 	splitted line
 * @param i 			current texture index
 * 
 * @return 1 if the default texture is valid, 0 otherwise
 */
int	ft_check_default(t_map *map, char **array_line, int i)
{
	if (map->def_text == 0)
		if (ft_nb_arg(map, array_line, i) == 1)
			return (1);
	return (0);
}

/**
 * @brief Handle the id of the texture
 * 
 * @param map 			struct of the map
 * @param array_line 	splitted line
 * @param i 			index
 */
void	ft_handle_id(t_map *map, char **array_line, int i)
{
	int	id;

	if (ft_check_default(map, array_line, i) == 1)
		return ;
	id = ft_check_id(map, array_line);
	map->text[id].no_idx = id;
	if (i != 4)
	{
		ft_cut_extra_char(array_line[2]);
		if (ft_acces_texture(array_line[2], 0) == 1)
		{
			ft_free_array(&array_line);
			ft_error_handle(map, "Error\n", "Invalid texture path", 1);
		}
	}
	if (i == 0)
		ft_handle_frame(map->text[id].no, array_line);
	else if (i == 1)
		ft_handle_frame(map->text[id].so, array_line);
	else if (i == 2)
		ft_handle_frame(map->text[id].we, array_line);
	else if (i == 3)
		ft_handle_frame(map->text[id].ea, array_line);
	else if (i == 4)
		ft_handle_option(map, array_line, id);
}
