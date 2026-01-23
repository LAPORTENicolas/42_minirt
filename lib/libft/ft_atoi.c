/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:00:32 by jodde             #+#    #+#             */
/*   Updated: 2025/05/19 20:45:51 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(char const *str)
{
	int	nb;
	int	signe;

	nb = 0;
	signe = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' || \
			*str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			signe *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nb = nb * 10 + (*str - 48);
		str++;
	}
	return (nb * signe);
}
/*#include <stdio.h>

int	main(void)
{
	const char	*str = "\010 8";
	
	printf("atoi = %d\n", atoi(str));
	printf("ma fonction = %d\n", ft_atoi(str));
	return (0);
}*/
