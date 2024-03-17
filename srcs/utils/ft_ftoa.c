/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 12:55:19 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/17 12:55:38 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_ftoa(float n, int length)
{
	char	*str1;
	char	*str2;
	char	*str3;
	t_pos	dec;
	t_pos	whole;

	whole.x = (int) n;
	whole.y = ft_numlen(whole.x);
	dec.y = length - whole.y - 1;
	if (dec.y == 0)
		whole.y++;
	str1 = ft_lli_to_str(whole.x, whole.y);
	if (dec.y > 0)
	{
		dec.x = (n - whole.x) * pow(10, dec.y);
		str2 = ft_lli_to_str(dec.x, dec.y);
		str3 = ft_strjoin(str1, ".");
		free(str1);
		str1 = ft_strjoin(str3, str2);
		free(str2);
		free(str3);
	}
	return (str1);
}
