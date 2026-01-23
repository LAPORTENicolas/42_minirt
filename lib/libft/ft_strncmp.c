/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:00:04 by jodde             #+#    #+#             */
/*   Updated: 2025/05/19 05:27:38 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (n-- && (*s1 == *s2) && (*s1 != '\0' || *s2 != '\0'))
	{
		if (n == 0)
			return (0);
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
/*#include <stdio.h>
#include <string.h>

int	main(void)
{
	const char	*s1 = "zyxbcdefgh";
	const char	*s2 = "";
	size_t size = 0;

	printf("strncmp = %d \n", strncmp(s1, s2, size));
	printf("ma fonction = %d \n", ft_strncmp(s1, s2, size));
	return (0);
}*/
