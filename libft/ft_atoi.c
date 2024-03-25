/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2023/09/26 19:32:34 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/26 14:41:51 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_check_atoi(const char *nptr, int *i, int *sign)
{
	while (nptr[*i] == ' ' || nptr[*i] == '\f' || nptr[*i] == '\n'
		|| nptr[*i] == '\r' || nptr[*i] == '\t' || nptr[*i] == '\v')
		(*i)++;
	if (nptr[*i] == '-' || nptr[*i] == '+')
	{
		if (nptr[*i] == '-')
			*sign = -1;
		(*i)++;
	}
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	res = 0;
	sign = 1;
	if (!nptr)
		return (0);
	ft_check_atoi(nptr, &i, &sign);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (res > INT_MAX / 10 || (res == INT_MAX / 10 && nptr[i]
				- '0' > INT_MAX % 10))
		{
			if (sign == -1)
				return (INT_MIN);
			else
				return (INT_MAX);
		}
		res = res * 10 + (nptr[i] - '0');
		i++;
	}
	return (sign * res);
}
