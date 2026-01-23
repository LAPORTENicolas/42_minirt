/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 14:42:43 by jodde             #+#    #+#             */
/*   Updated: 2025/05/19 04:26:17 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;
	t_list	*head;

	if (!lst || !del)
		return ;
	head = *lst;
	while (head != NULL)
	{
		current = head;
		del((void *)current->content);
		head = head->next;
		free (current);
	}
	*lst = NULL;
}
