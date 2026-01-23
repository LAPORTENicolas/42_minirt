/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 14:55:49 by jodde             #+#    #+#             */
/*   Updated: 2025/05/19 00:43:28 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*current;
	t_list	*newlist;
	t_list	*new;
	void	*newcont;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	new = NULL;
	current = lst;
	newlist = new;
	while (current != NULL)
	{
		newcont = f((void *)current->content);
		new = ft_lstnew(newcont);
		if (!new)
		{
			del(newcont);
			ft_lstclear(&newlist, del);
			return (NULL);
		}
		ft_lstadd_back(&newlist, new);
		current = current->next;
	}
	return (newlist);
}
