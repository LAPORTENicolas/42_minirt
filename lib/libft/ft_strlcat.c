/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:40:24 by jodde             #+#    #+#             */
/*   Updated: 2025/05/19 04:30:35 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	lens;
	size_t	lend;
	size_t	len;

	len = 0;
	lens = ft_strlen(src);
	lend = ft_strlen(dest);
	if (!dest || size < lend)
		return (size + lens);
	while (*dest != '\0' && len <= size)
	{
		dest++;
		len++;
	}
	if (len == size)
		return (size + lens);
	while (*src != '\0' && (len + 1) < size)
	{
		*dest = *(char *)src;
		dest++;
		src++;
		len++;
	}
	*dest = '\0';
	return (lend + lens);
}
/*
#include <stdio.h>
int	main(void)
{
	char	dest[15] = "rrrrrrrrrrrrrrr";
	const char	src[] = "lorem ipsum dolor sit amet";
	size_t	n = 5;

	printf("%zu \n", ft_strlcat(dest, src, n));
	printf("%s \n", dest);
	return (0);
}*/
