/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 19:31:33 by nlaporte          #+#    #+#             */
/*   Updated: 2026/01/18 15:15:02 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"
#include "../minirt.h"
#include <stdio.h>

int	get_vector_int(char **split, t_vec3 *r)
{
	int	rr;
	int	g;
	int	b;

	rr = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	ft_free_split(split);
	if (rr >= 0 && rr <= 255)
		r->x = rr;
	else
		return (printf("Error: red value between 0-255 inclued\n"), 1);
	if (g >= 0 && g <= 255)
		r->y = g;
	else
		return (printf("Error: green value between 0-255 inclued\n"), 1);
	if (b >= 0 && b <= 255)
		r->z = b;
	else
		return (printf("Error: blue value between 0-255 inclued\n"), 1);
	return (0);
}

/**
 * @brief parse_vector_int
 *
 * Pour une chaine de caractere s,
 * attribut les valeurs dans *r
 * return 0 si ok sinon 1
 *
 * @param char *s 
 * @param t_vec3 *r 
 * @return int code 
 */
int	parse_vector_int(char *s, t_vec3 *r, int line)
{
	char	**split;
	int		i;

	i = 0;
	while (s[i] && (ft_isdigit(s[i]) || s[i] == ',' || s[i] == '-'))
			i++;
	if (i != (int)ft_strlen(s))
	{
		printf("Error (line %i): bad char in expression\n", line);
		return (1);
	}
	split = ft_split(s, ',');
	if (!split)
	{
		perror("Error: ");
		return (1);
	}
	if (split[0] && split[1] && split[2] && !split[3])
		return (get_vector_int(split, r));
	printf("Error (line %i): need 3 value\n", line);
	ft_free_split(split);
	return (1);
}

int	get_vector_float(char **split, t_vec3 *r, float n[2], int line)
{
	float	rr;
	float	g;
	float	b;

	rr = ft_atof(split[0]);
	g = ft_atof(split[1]);
	b = ft_atof(split[2]);
	ft_free_split(split);
	if (rr >= n[0] && rr <= n[1])
		r->x = rr;
	else
		return (printf("Error (line %i): x value between %f >= N \
					<= %f\n", line, n[0], n[1]), 1);
	if (g >= n[0] && g <= n[1])
		r->y = g;
	else
		return (printf("Error (line %i): y value between %f >= N \
					<= %f\n", line, n[0], n[1]), 1);
	if (b >= n[0] && b <= n[1])
		r->z = b;
	else
		return (printf("Error (line %i): z value between %f >= N \
					<= %f\n", line, n[0], n[1]), 1);
	return (0);
}

/**
 * @brief parse_vector_float
 *
 * Pour une chaine de caractere s,
 * attribut les valeurs dans *r,
 * pour une range entre n_min n_max inclus
 * return 0 si ok sinon 1
 *
 * @param char *string
 * @param t_vec3 *response
 * @param float n_min
 * @param float n_max
 *
 * @return code
 */
int	parse_vector_float(char *s, t_vec3 *r, float n[2], int line)
{
	int		i;
	char	**split;

	i = 0;
	if (!s)
		return (printf("Error (line %i): no str\n", line), 1);
	while (s[i] && (ft_isdigit(s[i]) || s[i] == ',' || \
				s[i] == '.' || s[i] == '-'))
		i++;
	if (i != (int)ft_strlen(s))
	{
		printf("Error (line %i): bad char in expression\n", line);
		return (1);
	}
	split = ft_split(s, ',');
	if (!split)
		return (perror("Error: "), 1);
	if (split[0] && split[1] && split[2] && split[3] == 0)
		return (get_vector_float(split, r, n, line));
	printf("Error (line %i): need 3 value\n", line);
	ft_free_split(split);
	return (1);
}
