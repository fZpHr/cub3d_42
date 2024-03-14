/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:47:27 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/14 11:18:25 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef enum e_direction
{
	NORTH,
	SOUTH,
	WEST,
	EAST
}	t_direction;

typedef struct s_pos
{
	float	x;
	float	y;
}	t_pos;

typedef struct s_ipos
{
	int	x;
	int	y;
}	t_ipos;

typedef struct s_texture {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_size;
	int		width;
	int		height;
	int		endian;
}	t_texture;

/**
 * @brief Structure for the game
 * 
 * @param map_array		2D array of the map \
 * 						1 = wall, 0 = empty space
 * @param map_size		Size of the map (int, int)
 * @param orientation	Orientation of the player (in radian)
 * @param pos			Position of the player (float, float)
 * @param no			north texture
 * @param so			south texture
 * @param we			west texture
 * @param ea			east texture
 * @param floor_c		Color of the floor (ARGB)
 * @param ceiling_c		Color of the ceiling (ARGB)
*/
typedef struct s_cub
{
	void		*mlx;
	void		*mlx_win;

	char		**map_array;
	t_ipos		map_size;

	int			floor_c;
	int			ceiling_c;
	t_texture	no;
	t_texture	so;
	t_texture	we;
	t_texture	ea;

	float		orientation;
	t_pos		position;
}	t_cub;

void ft_parse();

// UTILS

void	ft_init(t_map *cube);
void	ft_error_handle(t_map *cube, char *error, char *str, int status);
void	ft_error_handle_color(t_map *cube, char *line);
void	ft_skip_spaces(char *line, int *i, int *count);
void	cut_extra_char(char *str);
void	ft_fill_line(char *line, int size);

// DATA

void	ft_cp_array(t_map *cube);
void	ft_map_into_array(t_map *cube, char *map);

#endif