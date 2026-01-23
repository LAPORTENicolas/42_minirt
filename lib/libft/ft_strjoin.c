/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:16:50 by jodde             #+#    #+#             */
/*   Updated: 2025/05/20 15:39:11 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	char	*debut_result;

	if (!s1 && !s2)
		return (NULL);
	result = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!result)
		return (NULL);
	debut_result = result;
	while (*s1 != '\0')
	{
		*result = *(char *)s1;
		result++;
		s1++;
	}
	while (*s2 != '\0')
	{
		*result = *(char *)s2;
		result++;
		s2++;
	}
	return (*result = '\0', debut_result);
}
