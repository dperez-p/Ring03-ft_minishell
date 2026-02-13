/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:39:55 by dperez-p          #+#    #+#             */
/*   Updated: 2025/05/17 08:48:46 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* List clear */
void	ft_lstclear(t_list **lst, void (*del)(void	*))
{
	t_list	*temp;
	t_list	*prev;

	if (lst && *lst && del)
	{
		prev = (t_list *)*lst;
		while (prev)
		{
			temp = prev->next;
			ft_lstdelone(prev, del);
			prev = temp;
		}
		*lst = 0;
	}
}
