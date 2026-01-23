/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:04:31 by nlaporte          #+#    #+#             */
/*   Updated: 2026/01/21 16:13:11 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_texture(void *p)
{
	t_texture	*texture;
	t_img		*tmp;

	texture = (t_texture *)p;
	if (!texture)
		return ;
	if (texture->img)
	{
		tmp = texture->img;
		free(tmp->image);
		free(tmp);
	}
	if (texture->img_n)
	{
		tmp = texture->img_n;
		free(tmp->image);
		free(tmp);
	}
	free(texture->name);
	free(texture);
}
