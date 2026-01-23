/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:07:47 by jodde             #+#    #+#             */
/*   Updated: 2025/05/19 20:11:22 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t	len;

	len = ft_strlen(str) + 1;
	while (len--)
	{
		if (*(str + len) == (char)c)
			return ((char *)(str + len));
	}
	return (NULL);
}
/*#include <stdio.h>
#include <string.h>

int	main(void)
{
	const char	*str = "ewffwf";
	int	c = '\0';

	printf("strrchr = %s \n", strrchr(str, c));
	printf("ma fonction = %s \n", ft_strrchr(str, c));
	return (0);
}*/