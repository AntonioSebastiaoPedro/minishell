/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 02:17:44 by ansebast          #+#    #+#             */
/*   Updated: 2024/11/06 13:04:41 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_str_tab(char **tab, int size)
{
	int		i;
	char	*temp;

	i = 0;
	while (i < (size - 1))
	{
		if (ft_strcmp(tab[i], tab[i + 1]) > 0)
		{
			temp = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = temp;
			i = 0;
		}
		else
			i++;
	}
}

void	ft_export(t_command *cmd, char **env)
{
	char	*var;
	char	*value;
	char	**env_dup;
	int		i;
	int		j;
	int		iqual;

	env_dup = (char **)ft_calloc(ft_tablen(env) + 1, sizeof(char *));
	ft_matcpy(env_dup, env);
	i = 0;
	if (!cmd->args || !cmd->args[0])
	{
		sort_str_tab(env_dup, ft_tablen(env_dup));
		while (env_dup[i])
		{
			iqual = 0;
			j = 0;
			ft_putstr_fd("declare -x ", 1);
			while (env_dup[i][j])
			{
				write(1, &env_dup[i][j++], 1);
				if (env_dup[i][j - 1] == '=')
					iqual = write(1, "\"", 1);
			}
			if (iqual)
				write(1, "\"\n", 2);
			i++;
		}
	}
	// else
	// {
	// 	var = strtok(cmd->args[0], "=");
	// 	value = strtok(NULL, "=");
	// 	if (var && value)
	// 		setenv(var, value, 1);
	// }
	ft_freearray(env_dup);
}
