/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_file_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 22:34:42 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/19 01:09:39 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_check_color_bonus(char *line, int *color)
{
    int i;

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

int    ft_check_id(t_map *map, char **array_line)
{
    int tmp;

    tmp = ft_atoi(array_line[1]);
    if (array_line[1] == NULL)
    {
        ft_free_array(array_line);
        ft_error_handle(map, "Error\n", "Invalid id", 1);
    }
    if (tmp < 1 || tmp > 128)
    {
        ft_free_array(array_line);
        ft_error_handle(map, "Error\n", "Invalid id", 1);
    }
    if (array_line[1][1] != '\0')
    {
        ft_free_array(array_line);
        ft_error_handle(map, "Error\n", "Invalid id", 1);
    }
    return (tmp);
}

void    ft_handle_id(t_map *map, t_cub *cube, char **array_line, int i)
{
    int tmp[3];
    int id;

    id = ft_check_id(map, array_line);
    ft_acces_texture(map, array_line[2], 0);
    if (i == 0)
        map->text[id].no = ft_strdup(array_line[2]);
    else if (i == 1)
        map->text[id].so = ft_strdup(array_line[2]);
    else if (i == 2)
        map->text[id].we = ft_strdup(array_line[2]);
    else if (i == 3)
        map->text[id].ea = ft_strdup(array_line[2]);
    else if (i == 4)
    {
        ft_check_color_bonus(array_line[2], tmp);
        map->text[id].mp = (tmp[0] << 16) + (tmp[1] << 8) + tmp[2];
    }
    (void)cube;
    /*if (i == 0)
        cube->textures[id].no.img = ft_strdup(array_line[2]);
    else if (i == 1)
        cube->textures[id].so = ft_strdup(array_line[2]);
    else if (i == 2)
        cube->textures[id].we = ft_strdup(array_line[2]);
    else if (i == 3)
        cube->textures[id].ea = ft_strdup(array_line[2]);
    else if (i == 4)
    {
        ft_check_color_bonus(array_line[2], &tmp);
        cube->textures[array_line[1][0]].map_color = (tmp[0] << 16) + (tmp[1] << 8)
		+ tmp[2];
    }*/
}

int ft_check_texture_bonus(t_map *map, t_cub *cube, char **array_line)
{
    printf("array_line[0] = %s\n", array_line[0]);
    printf("array_line[1] = %s\n", array_line[1]);
    printf("array_line[2] = %s\n", array_line[2]);
    if (ft_strncmp(array_line[0], "NO", 2) == 0)
        ft_handle_id(map, cube, array_line, 0);
    else if (ft_strncmp(array_line[0], "SO", 2) == 0)
        ft_handle_id(map, cube, array_line, 1);
    else if (ft_strncmp(array_line[0], "WE", 2) == 0)
        ft_handle_id(map, cube, array_line, 2);
    else if (ft_strncmp(array_line[0], "EA", 2) == 0)
        ft_handle_id(map, cube, array_line, 3);
    else if (ft_strncmp(array_line[0], "MP", 2) == 0)
        ft_handle_id(map, cube, array_line, 4);
    else if (ft_strncmp(array_line[0], "F", 1) == 0)
    {
        if (ft_check_color_bonus(array_line[1], map->floor_c) == 1)
            return (1);
    }
    else if (ft_strncmp(array_line[0], "C", 1) == 0)
    {
        if (ft_check_color_bonus(array_line[1], map->ceiling_c) == 1)
            return (1);
    }
    else
        return (1);
    return (0);
}

void   ft_loop_map_bonus(t_map *map, t_cub *cube, int fd, int full)
{
    char **array_line;
    char *line;

    (void)full;
    line = get_next_line(fd);
    array_line = ft_split(line, " ");
    while (line)
    {
        printf("line = %s\n", line);
        map->map_position++;
        if (ft_check_texture_bonus(map, cube, array_line) == 1)
        {
            free(line);
            ft_error_handle(map, "Error\n", "Invalid description content", 1);
        }
        free(line);
        ft_free_array(array_line);
        line = get_next_line(fd);
        array_line = ft_split(line, " ");
    }
    free(line);
    ft_check_map_content(map, fd);
    close(fd);
}

/**
 * @brief Check if the map file is valid
 * 
 * @param map struct of the map
 * @param line line of the map
 * @return void
 */
void    ft_check_map_file_bonus(t_map *map, t_cub *cube, char *file)
{
    int     fd;
    int     full;

    full = 0;
    if (ft_strcmp(file + (ft_strlen(file) - 4), ".cub") != 0)
        ft_error_handle(map, "Invalid file format : ", file, 1);
    fd = open(file, O_RDWR);
    if (fd < 0)
    {
        ft_error_handle(map, "Error\n", "Invalid file", 1);
    }
    ft_loop_map_bonus(map, cube, fd, full);
}