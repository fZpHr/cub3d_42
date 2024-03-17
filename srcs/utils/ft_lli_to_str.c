/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lli_to_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 12:52:56 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/17 13:11:21 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_lli_to_str(long long n, int lenght)
{
	char	*str;

	str = ft_calloc(lenght + 1, sizeof(char));
	str[lenght] = 0;
	while (lenght--)
	{
		str[lenght] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}
