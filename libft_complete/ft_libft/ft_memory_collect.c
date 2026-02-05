/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory_collect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 19:38:07 by dperez-p          #+#    #+#             */
/*   Updated: 2026/02/05 20:40:19 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Returns a pointer to the static memory tracking list */
t_list	**get_memory_ptr(void)
{
	static t_list	*ptr;

	return (&ptr);
}

/* Add allocated memory to the tracking list */
void	collect_mem(void *content)
{
	ft_lstadd_front(get_memory_ptr(), ft_lstnew(content));
}

/* Allocates memory and tracks it for later deallocation */
void	*allocate_mem(size_t nmemb, size_t size)
{
	void	*p;

	p = ft_calloc(nmemb, size);
	collect_mem(p);
	return (p);
}

/* Frees all tracked memory and clears the tracking list */
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

/* Frees all tracked memory and clears the tracking list */
void	clear_mem(void)
{
	ft_lstclear(get_memory_ptr(), &free);
}
