/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:40:31 by jodde             #+#    #+#             */
/*   Updated: 2025/05/19 00:23:53 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *str, int fd)
{
	size_t	len;

	if (!str)
		return ;
	len = ft_strlen((const char *)str);
	write (fd, str, len);
	write (fd, "\n", 1);
	return ;
}
