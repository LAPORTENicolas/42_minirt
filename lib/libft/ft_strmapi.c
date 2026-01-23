/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:57:03 by jodde             #+#    #+#             */
/*   Updated: 2025/05/19 07:00:22 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*result;
	size_t			len;

	i = 0;
	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	while (s[i])
	{
		result[i] = (char )f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
/*
char	ft_upper(unsigned int i, char c)
{
	if (i % 2 == 0 && c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}

#include <stdio.h>

int	main(void)
{
	char const	*s1 = "hghjgh";
	
	printf("%s \n", ft_strmapi(s1, &ft_upper));
	return (0);	
}*/
