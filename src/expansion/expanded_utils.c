/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanded_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 09:54:54 by dperez-p          #+#    #+#             */
/*   Updated: 2026/01/10 19:09:31 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_env_value(t_list *lev, const char *var_name)
{
	t_lev	*env_var;

	env_var = findlev(lev, var_name);
	if (!env_var || !env_var->value)
		return (NULL);
	return (env_var->value);
}
