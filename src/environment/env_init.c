/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 12:38:14 by dperez-p          #+#    #+#             */
/*   Updated: 2026/02/05 20:42:42 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Create environment variable node */
t_lev	*create_env_node(char **arr_ev)
{
	t_lev	*new_node;
	char	*value;
	char	*temp;
	int		i;

	new_node = malloc(sizeof(t_lev));
	if (!new_node)
		handle_error(MALLOC);
	new_node->key = ft_strdup(arr_ev[0]);
	new_node->value = ft_strdup("");
	i = 1;
	while (arr_ev[i])
	{
		value = ft_strdup(arr_ev[i]);
		if (i > 1)
			temp = ft_strjoin(new_node->value, "=");
		else
			temp = ft_strdup(new_node->value);
		deallocate_mem(new_node->value);
		new_node->value = ft_strjoin_free(temp, value);
		i++;
	}
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

/* Get the last node of the environment variable list */
static t_lev	*levlast(t_lev *lev)
{
	if (!lev)
		return (NULL);
	while (lev->next)
		lev = lev->next;
	return (lev);
}

/* Append environment variable node to the list */
void	append_env_node(t_lev **lev, t_lev *new_node)
{
	t_lev	*last;

	if (!new_node)
		return ;
	if (!*lev)
	{
		*lev = new_node;
		return ;
	}
	last = levlast(*lev);
	last->next = new_node;
	new_node->prev = last;
	return ;
}

/* Separate environment variable into key and value */
char	**separate_ev(char *ev)
{
	char	**arr_ev;
	char	*equal_sign;
	char	*key;
	int		len_key;

	len_key = 0;
	while (ev[len_key] && ev[len_key] != '=')
		len_key++;
	key = allocate_mem(len_key + 2, sizeof(char));
	ft_strlcpy(key, ev, len_key + 1);
	if (ev[len_key] == '=')
	{
		equal_sign = ft_strdup(ev + len_key + 1);
		if (!equal_sign)
			handle_error(MALLOC);
	}
	else
		equal_sign = NULL;
	arr_ev = allocate_mem(3, sizeof(char *));
	arr_ev[0] = key;
	arr_ev[1] = equal_sign;
	arr_ev[2] = NULL;
	return (arr_ev);
}

/* Initialize environment variable list */
t_lev	**init_env_list(t_data *minishell)
{
	int		i;
	char	**arr_ev;
	t_lev	**lev;
	t_lev	*new_node;

	i = 0;
	minishell->ev_num = ft_array_len(minishell->ev);
	lev = malloc(sizeof(t_lev *));
	if (!lev)
		handle_error(MALLOC);
	*lev = NULL;
	i = 0;
	while (minishell->ev[i] != NULL)
	{
		arr_ev = separate_ev(minishell->ev[i]);
		new_node = create_env_node(arr_ev);
		ft_free_matrix(arr_ev);
		append_env_node(lev, new_node);
		i++;
	}
	return (lev);
}
