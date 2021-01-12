/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 16:52:03 by ojoubout          #+#    #+#             */
/*   Updated: 2019/10/14 17:07:36 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *p;

	p = *alst;
	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	while (p->next != NULL)
		p = p->next;
	p->next = new;
}
