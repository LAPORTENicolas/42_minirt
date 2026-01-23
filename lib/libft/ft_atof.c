/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:00:32 by jodde             #+#    #+#             */
/*   Updated: 2026/01/22 06:48:29 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

#include <stdio.h>

void	set_sign(const char **str, int *sign)
{
	if (**str == '-')
			*sign *= -1;
	(*str)++;
}

float	ft_atof(const char *str)
{
	int		n;
	float	r;
	char	*p;
	size_t	i;
	
	n = ft_atoi(str);
	p = ft_strchr(str, '.');
	if (!p)
		return (n);
	p++;
	if (!*p)
		return (n);
	i = 0;
	r = 0;
	while (i < ft_strlen(p) && i < 10 && ft_isdigit(*(p + i)))
	{
		r += (float)(*(p + i) - '0') / pow(10, i + 1);
		i++;
	}
	if (n < 0)
		return -1 * (r + abs(n));
	else
		return r + n;
}
