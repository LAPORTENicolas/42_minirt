/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 19:45:23 by nlaporte          #+#    #+#             */
/*   Updated: 2025/12/14 18:09:33 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdint.h>

typedef struct s_file
{
	char	buf[BUFFER_SIZE + 1];
	char	*line;
	int		init;
	int		fd;
	int		status;
	int		index;
}	t_file;

void	init_file(t_file *file, int fd);
void	clear_file(t_file *file);
void	clear_buffer(t_file *file);

char	*get_next_line(int fd);
char	*ft_give_malloc(int linebreak, int size);

int		ft_getendline(char *s);
int		ft_strlen_gnl(char *s, int endl);

#endif // !GET_NEXT_LINE_BONUS_H
