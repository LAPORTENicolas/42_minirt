/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:40:22 by jodde             #+#    #+#             */
/*   Updated: 2026/01/05 16:42:02 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_next(char *str)
{
	size_t	j;

	j = 0;
	if (ft_isspace(*str))
	{
		while (*str)
		{
			if (ft_isspace(*str))
				j++;
			else
				break ;
		}
	}
	else
	{
		while (*str)
		{
			if (!ft_isspace(*str))
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

static size_t	ft_split_size(char *str)
{
	unsigned int	i;
	size_t			size;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]))
			i += ft_next(&str[i]);
		else
		{
			i += ft_next(&str[i]);
			size++;
		}
	}
	return (size);
}

char	**ft_split_space(char *str)
{
	char	**split;
	int		k;

	k = 0;
	split = malloc(sizeof(char *) * (ft_split_size(str) + 1));
	if (split == NULL)
		return (NULL);
	while (*str)
	{
		if (ft_isspace(*str))
			str++;
		else
		{
			split[k] = ft_strndup(str, ft_next(str));
			if (split[k++] == NULL)
			{
				ft_abort(split, k - 1);
				return (NULL);
			}
			str += ft_next(str);
		}
	}
	split[k] = 0;
	return (split);
}
