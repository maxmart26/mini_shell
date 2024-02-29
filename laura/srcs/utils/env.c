/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:37:49 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/02/29 19:31:06 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_env_list(t_env **env_list, t_env *var)
{
	t_env	*list;

	if (!env_list || !var)
		return ;
	if (*env_list)
	{
		list = *env_list;
		while (list && list->next)
			list = list->next;
		list->next = var;
	}
	else
		*env_list = var;
}

t_env	*add_args(char *name, char *value)
{
	t_env	*var;

	var = malloc(sizeof(t_env));
	if (!var)
		return (NULL);
	var->name = ft_strdup(name);
	var->value = ft_strdup(value);
	var->next = NULL;
	return (var);
}

void	init_env(t_env **env_list, char **env)
{
	t_env	*new_var;
	char	**tab;
	int		i;

	new_var = NULL;
	i = 0;
	while (env[i])
	{
		tab = ft_split(env[i], '=');
		new_var = add_args(tab[0], tab[1]);
		if (!env_list)
			env_list = &new_var;
		else
			add_env_list(env_list, new_var);
		free(tab[0]);
		free(tab[1]);
		free(tab);
		i++;
	}
}
