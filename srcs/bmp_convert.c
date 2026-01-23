/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_convert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 16:05:55 by nlaporte          #+#    #+#             */
/*   Updated: 2026/01/19 11:44:22 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "../lib/mlx/mlx.h"
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

static void	write_header(int fd, int width, int height)
{
	int		filesize;
	char	header[54];

	filesize = 54 + 4 * width * height;
	ft_bzero(header, 54);
	header[0] = 'B';
	header[1] = 'M';
	*(int *)&header[2] = filesize;
	header[10] = 54;
	header[14] = 40;
	*(int *)&header[18] = width;
	*(int *)&header[22] = height;
	header[26] = 1;
	header[28] = 32;
	if (write(fd, header, 54) == -1)
		printf("Can't write screen shoot header %s\n", strerror(errno));
}

static char	*get_name(void)
{
	static int	j = 1;
	char		name[50];
	int			i;

	i = 0;
	name[i++] = 'S';
	name[i++] = 'c';
	name[i++] = 'r';
	name[i++] = 'e';
	name[i++] = 'e';
	name[i++] = 'n';
	name[i++] = '-';
	if (j == 0)
		j++;
	name[i++] = (unsigned char)j++;
	name[i++] = '.';
	name[i++] = 'b';
	name[i++] = 'm';
	name[i++] = 'p';
	name[i++] = '\0';
	return (ft_strdup(name));
}

void	reverse_img(t_env *env, int	*buf_to_reverse)
{
	int		tmp;
	int		size;
	int		i;
	int		j;

	i = 0;
	size = env->win.width * env->win.height;
	j = size;
	size *= .5;
	while (i < size)
	{
		tmp = buf_to_reverse[i];
		buf_to_reverse[i] = buf_to_reverse[j];
		buf_to_reverse[j] = tmp;
		i++;
		j--;
	}
}

int	make_screen_shoot(t_env *env)
{
	char	*filename;
	char	*img_data;
	int		fd;

	img_data = mlx_get_data_addr(env->win.img, &fd, &fd, &fd);
	filename = get_name();
	if (!filename)
		return (1);
	fd = open(filename, O_CREAT | O_WRONLY, 0777);
	if (fd < 0)
		return (free(filename), 1);
	write_header(fd, env->win.width, env->win.height);
	reverse_img(env, (int *)img_data);
	if (write(fd, img_data, 4 * env->win.width * env->win.height) == -1)
		printf("merde impossoble ecrrire header %s\n", strerror(errno));
	free(filename);
	close(fd);
	return (0);
}
