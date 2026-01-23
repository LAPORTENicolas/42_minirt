/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:55:25 by jodde             #+#    #+#             */
/*   Updated: 2025/05/20 15:16:01 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_compchar(const char *set, char const c)
{
	while (*set != '\0')
		if (c == *set++)
			return (0);
	return (1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*result;
	size_t			len;

	if (!s1)
		return (NULL);
	while (*s1 != '\0' && ft_compchar(set, *s1) == 0)
		s1++;
	len = ft_strlen(s1);
	while (len && ft_compchar (set, s1[len - 1]) == 0)
		len--;
	if (len == 0)
		return (ft_strdup(""));
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	ft_memcpy(result, s1, len);
	return (result[len] = '\0', result);
}
/*#include <stdio.h>

int	main(void)
{
	char const	*s1 = "lorem ipsum dolor sit amet";
	char const	*set = "te";

	printf("%s \n", ft_strtrim(s1, set));
	return (0);
}*/