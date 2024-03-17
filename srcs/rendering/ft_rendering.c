/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rendering.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:38:37 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/17 11:51:51 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

/**
 * @brief Initialize the keys structure.
 * 
 * @note	Point: avoid `uninitialized values` errors.
 * 
 * @param keys 	The keys structure
*/
void	ft_keys_init(t_keys *keys)
{
	keys->forward = FALSE;
	keys->backward = FALSE;
	keys->rot_left = FALSE;
	keys->rot_right = FALSE;
}

/**
 * @brief Load a texture from a file and return all the info.
 * 
 * @param cub 	The game structure
 * @param path 	The path of the texture file
 * 
 * @note	If there is a problem, `frame.img` is `NULL`.
 * 
 * @return t_frame 	The texture
*/
t_frame ft_load_texture(t_cub *cub, char *path)
{
	t_frame	frame;
	int		width;
	int		height;
	int		bpp;
	int		endian;

	frame.img = mlx_xpm_file_to_image(cub->mlx, path, &width, &height);
	frame.addr = mlx_get_data_addr(frame.img, &bpp, &frame.line_size, &endian);
	frame.width = width;
	frame.height = height;
	frame.bits_per_pixel = bpp;
	frame.endian = endian;
	return (frame);
}

/**
 * @brief Initialize the MLX and start the rendering loop.
 * 
 * @param cub 	The game structure
*/
void	ft_rendering(t_cub *cub)
{
	(void)cub;

	cub->frames = 0;
	ft_keys_init(&cub->keys);
	if (ft_mlx_init(cub))
	{
		ft_game_quit(cub);
		return ;
	}

	cub->minimap = BONUS;
	cub->info = FALSE;

	// cub->border_c = 0xFFCCCCCC;
	cub->border_c = 0;

	for (int i = 0; i < 128; i++)
	{
		cub->textures[i].no = NULL;
		cub->textures[i].so = NULL;
		cub->textures[i].we = NULL;
		cub->textures[i].ea = NULL;
		cub->textures[i].anim_no = 0;
		cub->textures[i].anim_so = 0;
		cub->textures[i].anim_we = 0;
		cub->textures[i].anim_ea = 0;
		cub->textures[i].anim_delay = 30;
		cub->textures[i].map_color = 0x00000000;
	}

	cub->textures['0'].map_color = 0xFF000000;
	
	cub->textures['1'].no = ft_calloc(2, sizeof(t_frame));
	cub->textures['1'].no[0] = ft_load_texture(cub, "textures/bricks-blue-00.xpm");
	cub->textures['1'].so = ft_calloc(2, sizeof(t_frame));
	cub->textures['1'].so[0] = ft_load_texture(cub, "textures/bricks-blue-00.xpm");
	cub->textures['1'].we = ft_calloc(2, sizeof(t_frame));
	cub->textures['1'].we[0] = ft_load_texture(cub, "textures/bricks-blue-00.xpm");
	cub->textures['1'].ea = ft_calloc(2, sizeof(t_frame));
	cub->textures['1'].ea[0] = ft_load_texture(cub, "textures/bricks-blue-00.xpm");
	cub->textures['1'].anim_no = 1;
	cub->textures['1'].anim_so = 1;
	cub->textures['1'].anim_we = 1;
	cub->textures['1'].anim_ea = 1;
	cub->textures['1'].map_color = 0xFF0000FF;
	
	cub->textures['2'].no = ft_calloc(2, sizeof(t_frame));
	cub->textures['2'].no[0] = ft_load_texture(cub, "textures/metal-gray-00.xpm");
	cub->textures['2'].so = ft_calloc(2, sizeof(t_frame));
	cub->textures['2'].so[0] = ft_load_texture(cub, "textures/metal-gray-00.xpm");
	cub->textures['2'].we = ft_calloc(2, sizeof(t_frame));
	cub->textures['2'].we[0] = ft_load_texture(cub, "textures/metal-gray-00.xpm");
	cub->textures['2'].ea = ft_calloc(2, sizeof(t_frame));
	cub->textures['2'].ea[0] = ft_load_texture(cub, "textures/metal-gray-00.xpm");
	cub->textures['2'].anim_no = 1;
	cub->textures['2'].anim_so = 1;
	cub->textures['2'].anim_we = 1;
	cub->textures['2'].anim_ea = 1;
	cub->textures['2'].map_color = 0xFFC8C8C8;
	
	cub->textures['3'].no = ft_calloc(2, sizeof(t_frame));
	cub->textures['3'].no[0] = ft_load_texture(cub, "textures/bricks-gray-00.xpm");
	cub->textures['3'].so = ft_calloc(2, sizeof(t_frame));
	cub->textures['3'].so[0] = ft_load_texture(cub, "textures/bricks-gray-00.xpm");
	cub->textures['3'].we = ft_calloc(2, sizeof(t_frame));
	cub->textures['3'].we[0] = ft_load_texture(cub, "textures/bricks-gray-00.xpm");
	cub->textures['3'].ea = ft_calloc(2, sizeof(t_frame));
	cub->textures['3'].ea[0] = ft_load_texture(cub, "textures/bricks-gray-00.xpm");
	cub->textures['3'].anim_no = 1;
	cub->textures['3'].anim_so = 1;
	cub->textures['3'].anim_we = 1;
	cub->textures['3'].anim_ea = 1;
	cub->textures['3'].map_color = 0xFF808080;
	
	cub->textures['4'].no = ft_calloc(2, sizeof(t_frame));
	cub->textures['4'].no[0] = ft_load_texture(cub, "textures/metal-green-00.xpm");
	cub->textures['4'].so = ft_calloc(2, sizeof(t_frame));
	cub->textures['4'].so[0] = ft_load_texture(cub, "textures/metal-green-00.xpm");
	cub->textures['4'].we = ft_calloc(2, sizeof(t_frame));
	cub->textures['4'].we[0] = ft_load_texture(cub, "textures/metal-green-00.xpm");
	cub->textures['4'].ea = ft_calloc(2, sizeof(t_frame));
	cub->textures['4'].ea[0] = ft_load_texture(cub, "textures/metal-green-00.xpm");
	cub->textures['4'].anim_no = 1;
	cub->textures['4'].anim_so = 1;
	cub->textures['4'].anim_we = 1;
	cub->textures['4'].anim_ea = 1;
	cub->textures['4'].map_color = 0xFF00FF00;
	
	cub->textures['X'].no = ft_calloc(2, sizeof(t_frame));
	cub->textures['X'].no[0] = ft_load_texture(cub, "textures/exit-00.xpm");
	cub->textures['X'].so = ft_calloc(2, sizeof(t_frame));
	cub->textures['X'].so[0] = ft_load_texture(cub, "textures/exit-00.xpm");
	cub->textures['X'].we = ft_calloc(2, sizeof(t_frame));
	cub->textures['X'].we[0] = ft_load_texture(cub, "textures/exit-00.xpm");
	cub->textures['X'].ea = ft_calloc(2, sizeof(t_frame));
	cub->textures['X'].ea[0] = ft_load_texture(cub, "textures/exit-00.xpm");
	cub->textures['X'].anim_no = 1;
	cub->textures['X'].anim_so = 1;
	cub->textures['X'].anim_we = 1;
	cub->textures['X'].anim_ea = 1;
	cub->textures['X'].map_color = 0xFFFF00FF;

	cub->textures['O'].map_color = 0xFF00FFFF;

	for (int i = 0; i < cub->map_size.y; i++)
	{
		for (int j = 0; j < cub->map_size.x; j++)
		{
			if (cub->map_array[i][j].type == 'N'
				|| cub->map_array[i][j].type == 'S'
				|| cub->map_array[i][j].type == 'W'
				|| cub->map_array[i][j].type == 'E')
				cub->map_array[i][j].type = '0';
			cub->map_array[i][j].is_solid = cub->textures[(int) cub->map_array[i][j].type].no != NULL;
		}
	}

	mlx_loop(cub->mlx);
}
