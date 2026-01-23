/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:27:38 by jodde             #+#    #+#             */
/*   Updated: 2025/05/19 18:16:03 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	lens;

	lens = ft_strlen(s);
	if (start >= lens)
		return (ft_strdup(""));
	if ((lens - start) < len)
		len = lens - start;
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	ft_memcpy(result, s + start, len);
	return (result[len] = '\0', result);
}
/*#include <stdio.h>

int	main(void)
{
	char const	*s = "i just want this part #############";
	unsigned int	start = 0;
	size_t	len = 10;

	printf("%s \n", ft_substr(s, start, len));
	return (0);
}*/
