/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:57:19 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/28 22:09:11 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Check if the number of arguments is correct
 * 
 * @param ac 	number of arguments
 */
void	ft_check_args(int ac)
{
	if (ac <= 1)
	{
		ft_printf_error("Too few arguments\n");
		ft_printf_error("Usage: ./cub3d \"nameofamap.cub\"\n");
		exit(1);
	}
	else if (ac > 2)
	{
		ft_printf_error("Too many arguments\n");
		ft_printf_error("Usage: ./cub3d \"nameofamap.cub\"\n");
		exit(1);
	}
}
