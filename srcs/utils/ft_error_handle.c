/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_handle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:03:58 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/11 20:12:40 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_error_handle(char *error, char *str, int status)
{
	if (str)
		ft_printf_error("%s%s\n", error, str);
	else
		ft_printf_error("%s\n", error);
	exit(status);
}