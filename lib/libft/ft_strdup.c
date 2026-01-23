/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:00:32 by jodde             #+#    #+#             */
/*   Updated: 2025/05/19 20:45:51 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dup;
	char	*dup_beg;

	if (!src)
		return (NULL);
	dup = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!dup)
		return (NULL);
	dup_beg = dup;
	while (*src != '\0')
	{
		*dup = *(char *)src;
		dup++;
		src++;
	}
	*dup = '\0';
	return (dup_beg);
}
