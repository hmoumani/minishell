/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoumani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 14:21:04 by hmoumani          #+#    #+#             */
/*   Updated: 2021/01/01 14:21:09 by hmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int customized_len(char *s)
{
    int len;

    len = 0;
    while (s[len] && s[len] != '=')
    {
        len++;
    }
    return (len);
}

void deleteNode(char *s) 
{ 
    // Store head node 
    t_list *temp = g_env.env_head, *prev; 
  
    // If head node itself holds the key to be deleted 
    if (temp != NULL && !strncmp(temp->content, s, customized_len(temp->content))) 
    { 
        g_env.env_head = temp->next;   // Changed head 
        ft_lstdelone(temp, free);
        return; 
    } 
  
    // Search for the key to be deleted, keep track of the 
    // previous node as we need to change 'prev->next' 
    while (temp != NULL && strncmp(temp->content, s, customized_len(temp->content))) 
    {
        prev = temp; 
        temp = temp->next; 
    } 
  
    // If key was not present in linked list 
    if (temp == NULL) return; 
  
    // Unlink the node from linked list 
    prev->next = temp->next; 
  
    ft_lstdelone(temp, free);  // Free memory 
}

void ft_unset(char **argv)
{
    deleteNode(argv[1]);
}