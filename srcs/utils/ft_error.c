/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:31:08 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/17 11:31:54 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Print an error message and return `1`.
 * 
 * @param str 	The error message
 * 
 * @return int 	Always `1`
*/
int	ft_error(char *str)
{
	printf("Error: %s\n", str);
	return (1);
}
