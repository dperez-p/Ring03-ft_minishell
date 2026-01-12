/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory_collect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 19:38:07 by dperez-p          #+#    #+#             */
/*   Updated: 2026/01/12 12:21:15 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	**get_memory_ptr(void)
{
	static t_list	*ptr;

	return (&ptr);
}

void	collect_mem(void *content)
{
	ft_lstadd_front(get_memory_ptr(), ft_lstnew(content));
}

void	*allocate_mem(size_t nmemb, size_t size)
{
	void	*p;

	p = ft_calloc(nmemb, size);
	collect_mem(p);
	return (p);
}

void	deallocate_mem(void *content)
{
	t_list	**mem_list;
	t_list	*prev;
	t_list	*curr;

	if (!content)
		return ;
	mem_list = get_memory_ptr();
	curr = *mem_list;
	prev = NULL;
	while (curr)
	{
		if (curr->content == content)
		{
			if (prev)
				prev->next = curr->next;
			else
				*mem_list = curr->next;
			curr->next = NULL;
			free(curr->content);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	clear_mem(void)
{
	ft_lstclear(get_memory_ptr(), &free);
}
