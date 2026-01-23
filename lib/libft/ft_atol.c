/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:00:32 by jodde             #+#    #+#             */
/*   Updated: 2025/07/31 13:21:36 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include <stdlib.h>

long	ft_atol(char const *str)
{
	int		signe;
	long	nb;
	long	prev;

	nb = 0;
	signe = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' || \
			*str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			signe *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		prev = nb;
		nb = nb * 10 + (*str - '0');
		if (nb < prev)
			return (LONG_MAX);
		str++;
	}
	return (nb * signe);
}
/*#include <stdio.h>

int	main(void)
{
	const char	*str = "-18446744073709551618";
	
	printf("atoi = %d\n", atoi(str));
	printf("ma fonction = %ld\n", ft_atol(str));
	return (0);
}*/
