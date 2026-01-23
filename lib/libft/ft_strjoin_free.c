/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_join_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:00:32 by jodde             #+#    #+#             */
/*   Updated: 2025/05/19 20:45:51 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*result;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	result = malloc(len);
	if (!result)
		return (free(s1), NULL);
	ft_strlcpy(result, s1, len);
	ft_strlcat(result, s2, len);
	free(s1);
	return (result);
}
