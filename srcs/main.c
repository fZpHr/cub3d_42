/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:48:24 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/15 12:54:35 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;

	t_cub	cub;

	ft_parse_checker(&cub, ac, av);
	
	ft_rendering(&cub);

	return (0);
}
