/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:46:28 by jodde             #+#    #+#             */
/*   Updated: 2025/05/20 15:12:37 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*result;
	size_t	taille;

	if (size != 0 && (SIZE_MAX / size) < count)
		return (NULL);
	taille = count * size;
	result = (void *)malloc(taille);
	if (!result)
		return (NULL);
	ft_memset(result, 0, taille);
	return (result);
}
