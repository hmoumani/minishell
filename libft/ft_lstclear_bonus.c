/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 17:05:07 by ojoubout          #+#    #+#             */
/*   Updated: 2019/10/10 17:05:08 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *p;
	t_list *temp;

	p = *lst;
	while (p != NULL)
	{
		temp = p->next;
		ft_lstdelone(p, del);
		p = temp;
	}
	*lst = NULL;
}
