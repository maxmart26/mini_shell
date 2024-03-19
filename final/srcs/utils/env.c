/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:37:49 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/03/19 16:22:25 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

/*t_env	*new_env(void)
{
	t_env	*new;

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
}*/

void	ft_destroy_env(t_env *env_list)
{
	t_env	*tmp;
	t_env	*new;

	tmp = env_list;
	if (tmp == NULL)
		return ;
	while (tmp)
	{
		free(tmp->content);
		free(tmp->name);
		free(tmp->value);
		new = tmp->next;
		free(tmp);
		tmp = new;
	}
}
