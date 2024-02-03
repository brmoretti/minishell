/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmoretti <brmoretti@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:18:15 by bmoretti          #+#    #+#             */
/*   Updated: 2024/02/03 11:23:20 by brmoretti        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern char	**environ;

int	env(const char **args)
{
	int		i;
	char	**env_vars;

	if (args[1])
	{
		ft_putendl_fd("minishell: env doesn't accept arguments or flags", 2);
		return (EXIT_FAILURE);
	}
	env_vars = environ_holder(NULL, 0);
	i = -1;
	while (env_vars[++i])
	{
		if (env_vars[i][0])
			ft_putendl_fd(env_vars[i], 1);
	}
	return (EXIT_SUCCESS);
}
