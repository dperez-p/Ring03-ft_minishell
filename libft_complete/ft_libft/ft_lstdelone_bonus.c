/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:34:50 by dperez-p          #+#    #+#             */
/*   Updated: 2025/05/17 08:49:03 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/* del one list */
void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst)
	{
		return ;
	}
	if (del)
	{
		del(lst->content);
	}
	free(lst);
}
