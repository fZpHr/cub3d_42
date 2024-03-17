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

# include "parsing.h"
# include "mlx.h"
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <math.h>

# define PI			3.14159265358979323846
# define PI_2		1.57079632679489661923
# define PI_3		1.04719755119659774615
# define PI_4		0.78539816339744830962
# define PI_6		0.52359877559829887308
# define PI_12		0.26179938779914943654

/**
 * @brief Name of the window
*/
# define	NAME			"Cub3D"

/**
 * @brief Height of the window (in pixels)
*/
# define	HEIGHT			720

/**
 * @brief Width of the window (in pixels)
*/
# define	WIDTH			1080

/**
 * @brief Field of view (in radian)
*/
# define	FOV				PI_3

/**
 * @brief Number of rays
*/
# define	RAYS			200

/**
 * @brief Walking speed (in pixels per frame)
*/
# define	WALK_SPEED		0.07

/**
 * @brief Rotation speed (in radian per frame)
*/
# define	ROT_SPEED		PI_12 / 10

typedef unsigned long long	t_ull;

typedef enum e_direction
{
	NORTH,
	SOUTH,
	WEST,
	EAST
}	t_direction;

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

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

typedef struct s_keys
{
	t_bool	forward;
	t_bool	backward;
	t_bool	rot_left;
	t_bool	rot_right;
}	t_keys;

/**
 * @brief Structure for the game
 * 
 * @param mlx 			Pointer to the mlx instance
 * @param mlx_win 		Pointer to the mlx window
 * @param frame 		Canvas of the game (for optimization purpose)
 * 
 * @param map_array 	2D array of the map:
 * 						1 = wall, 0 = empty space
 * @param map_size 		Size of the map (int, int)
 * 
 * @param floor_c 		Color of the floor (ARGB)
 * @param ceiling_c 	Color of the ceiling (ARGB)
 * @param no 			north texture (see t_texture)
 * @param so 			south texture (see t_texture)
 * @param we 			west texture (see t_texture)
 * @param ea 			east texture (see t_texture)
 * 
 * @param orientation 	Orientation of the player (in radian)
 * @param position 		Position of the player (float, float)
 * @param keys 			Keys pressed by the player
 * 
 * @param frames 		Number of frames
*/
typedef struct s_cub
{
	void		*mlx;
	void		*mlx_win;
	t_texture	frame;

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
	t_keys		keys;

	t_ull		frames;
}	t_cub;

void	ft_assign_to_cube(t_cub *cub, t_map *map);
void	ft_parse_checker(t_cub *cub, int ac, char **av);

void	ft_rendering(t_cub *cub);

// UTILS

void	ft_init(t_map *map);
void	ft_error_handle(t_map *map, char *error, char *str, int status);
void	ft_error_handle_color(t_map *map, char *line);
void	ft_skip_spaces(char *line, int *i, int *count);
void	ft_cut_extra_char(char *str);
void	ft_fill_line(char *line, int size);

// DATA

void	ft_cp_array(t_map *map);
void	ft_map_into_array(t_map *map, char *map_file);

#endif