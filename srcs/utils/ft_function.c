/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_function.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:24:55 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/12 19:25:12 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_skip_spaces(char *line, int *i)
{
	while (line[*i] == ' ')
		(*i)++;
}

void	cut_extra_char(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i] != '\0')
		i++;
	if (str[i - 1] == '\n')
		str[i - 1] = '\0';
}

void	ft_fill_line(char *line, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		line[i] = 'A';
		i++;
	}
	line[i] = '\0';
}