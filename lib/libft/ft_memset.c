/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 22:50:52 by jodde             #+#    #+#             */
/*   Updated: 2025/05/19 02:11:51 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	void	*debut_s;

	debut_s = s;
	while (n--)
	{
		*(unsigned char *)s = (unsigned char)c;
		s++;
	}
	return (debut_s);
}
