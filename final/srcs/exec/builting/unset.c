/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:52:41 by matorgue          #+#    #+#             */
/*   Updated: 2024/05/10 12:08:02 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_include.h"
#include "../../../include/minishell_proto.h"
#include "../../../include/minishell_struct.h"

t_env	*ft_unset_next(t_env *env)
{
	t_env *(tmp) = env;
	if (env->next && env->prev)
	{
		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
		env = env->prev;
	}
	else if (env->next && !env->prev)
	{
		tmp->next->prev = NULL;
		env = env->next;
	}
	else if (!env->next && !env->prev)
		env = NULL;
	else
	{
		tmp->prev->next = NULL;
		env = env->prev;
	}
	free(tmp->value);
	free(tmp);
	while (env && env->prev)
		env = env->prev;
	return (env);
}

void	ft_unset_end(char **str, t_data *data, int i)
{
	t_env	*tmp;
	t_env	*env;

	env = data->env;
	while (env)
	{
		if (ft_strncmp(str[i], env->value, ft_strlen(str[i])) == 0
			&& env->value[ft_strlen(str[i])] == '=')
		{
			data->env = ft_unset_next(env);
			break ;
		}
		else
		{
			if (!env->next)
			{
				break ;
			}
		}
		tmp = env->next;
		env = tmp;
	}
	data->exit = 0;
}

void	ft_unset(char **str, t_data *data, int i)
{
	if (i == 0)
	{
		ft_end(data);
		exit(155);
	}
	data->exit = 0;
	if (!str[1])
	{
		return ;
	}
	else
	{
		i = 1;
		while (str[i])
		{
			if (ft_strncmp(str[i], "PATH", 5) == 0)
				data->r_path = FALSE;
			ft_unset_end(str, data, i);
			i++;
		}
	}
}
