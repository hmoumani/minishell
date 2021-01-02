/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 17:30:09 by ojoubout          #+#    #+#             */
/*   Updated: 2019/10/18 13:25:47 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *, void *), void	*param)
{
	if (!lst || !f)
		return ;
	while (lst != NULL)
	{
		f(lst->content, param);
		lst = lst->next;
	}
}
