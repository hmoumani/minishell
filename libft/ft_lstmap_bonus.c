/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 17:32:33 by ojoubout          #+#    #+#             */
/*   Updated: 2019/10/21 16:32:04 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *p;
	t_list *temp;
	t_list *head;

	if (!lst || !f)
		return (NULL);
	head = NULL;
	temp = NULL;
	while (lst != NULL)
	{
		p = ft_lstnew(f(lst->content));
		if (!p)
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		if (head == NULL)
			head = p;
		if (temp != NULL)
			temp->next = p;
		temp = p;
		lst = lst->next;
	}
	return (head);
}
