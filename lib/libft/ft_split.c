/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:40:22 by jodde             #+#    #+#             */
/*   Updated: 2026/01/21 21:43:53 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_next(char *str, char c)
{
	size_t	j;

	j = 0;
	if (*str == c)
	{
		while (*str)
		{
			if (*str++ == c)
				j++;
			else
				break ;
		}
	}
	else
	{
		while (*str)
		{
			if (*str++ != c)
				j++;
			else
				break ;
		}
	}
	return (j);
}

static void	ft_abort(char **split, int size)
{
	if (!split)
		return ;
	while (size >= 0)
		free(split[size--]);
	free(split);
}

static size_t	ft_split_size(char *str, char c)
{
	unsigned int	i;
	size_t			size;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (str[i] == c)
			i += ft_next(&str[i], c);
		else
		{
			i += ft_next(&str[i], c);
			size++;
		}
	}
	return (size);
}

char	**ft_split(char *str, char c)
{
	char	**split;
	int		k;

	k = 0;
	split = malloc(sizeof(char *) * (ft_split_size(str, c) + 1));
	if (split == NULL)
		return (NULL);
	while (*str)
	{
		if (*str == c)
			str++;
		else
		{
			split[k] = ft_strndup(str, ft_next(str, c));
			if (split[k++] == NULL)
			{
				ft_abort(split, k - 1);
				return (NULL);
			}
			str += ft_next(str, c);
		}
	}
	split[k] = 0;
	return (split);
}
