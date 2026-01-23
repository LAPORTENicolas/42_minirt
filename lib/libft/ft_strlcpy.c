/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 21:03:02 by jodde             #+#    #+#             */
/*   Updated: 2025/05/19 03:33:43 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	lens;
	size_t	i;

	i = 0;
	lens = ft_strlen(src);
	if (!dest || !src)
		return (0);
	if (size == 0)
		return (lens);
	while (*src != '\0' && i < (size - 1))
	{
		*dest = *(char *)src;
		dest++;
		src++;
		i++;
	}
	*dest = '\0';
	return (lens);
}
/*#include <stdio.h>
#include <bsd/string.h>

int	main(void)
{
	char	dest[20];
	char	src[] = "lorem ipsum dolor sit amet";
	size_t	n = 15;
	
	printf("stlcpy = %zu \n", strlcpy(dest, src, n));
	printf("dest = %s \n", dest);
	printf("ft_stlcpy = %zu \n", strlcpy(dest, src, n));
	printf("dest = %s \n", dest);
	return (0);	
}*/