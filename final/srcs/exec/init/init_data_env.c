/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:35:52 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/24 14:22:24 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_include.h"
#include "../../../include/minishell_proto.h"
#include "../../../include/minishell_struct.h"

void	free_env_str(char **str)
{
	int	i;

	i = 2;
	if (!str[2])
		return ;
	if (str[i][0])
	{
		while (str[i])
		{
			if (str[i] == NULL)
				break ;
			free(str[i]);
			i++;
		}
	}
	free(str);
}

void	init_env_while(t_data *data, int i, t_env *env, t_env *result)
{
	t_env	*tmp;

	while (data->envp[i])
	{
		env->value = ft_strdup(data->envp[i]);
		if (data->envp[i + 1])
		{
			env->next = new_env();
			if (!env->next)
			{
				ft_destroy_env(result);
				return ;
			}
			tmp = env->next;
			tmp->prev = env;
			env = tmp;
		}
		i++;
	}
}

t_env	*init_env(t_data *data, int i)
{
	t_env	*env;
	t_env	*result;
	char	**str;

	env = NULL;
	env = new_env();
	str = NULL;
	if (!env)
		return (NULL);
	result = env;
	env->prev = NULL;
	init_env_while(data, i, env, result);
	return (result);
}
