/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:37:49 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/03/06 18:24:19 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"


/*void	add_env_list(t_env **env_list, t_env *var)
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
	t_env	*new;

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
}*/
t_env	*new_env(void)
{
	t_env *new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->next = NULL;
	return (new);
}

t_env	*init_env(t_data *env_tool)
{
	t_env	*env;
	t_env	*tmp;
	t_env	*result;
	char	**str;
	int		i;

	/*if (!data->envp[0])
		return (init_env_i());*/
	env = new_env();
	i = 0;
	result = env;
	env->prev = NULL;
	while (env_tool->envp[i])
	{
		env->value = env_tool->envp[i];
		str = ft_split(env->value, '=');
		env->name = str[0];
		env->content = str[1];
		free(str);
		if (env_tool->envp[i + 1])
		{
			env->next = new_env();
			tmp = env->next;
			tmp->prev = env;
			env = tmp;
		}
		i++;
	}
	return (result);
}
