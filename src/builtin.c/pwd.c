/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:00:52 by najlghar          #+#    #+#             */
/*   Updated: 2026/02/01 13:20:43 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	pwd(t_data *minishell)
{
	char	path1[1024];
	char	*path2;

	if (!getcwd(path1, 1024))
	{
		path2 = get_key_value(*minishell->lev, "PWD");
		if (!path2)
			return (print_error(INVALID_PATH, 1, "pwd", NULL));
		else
			printf("%s\n", path2);
	}
	else
		printf("%s\n", path1);
	return (0);
}
