/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:52:41 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/26 16:39:40 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_include.h"
#include "../../../include/minishell_proto.h"
#include "../../../include/minishell_struct.h"

void	ft_unset_next(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	if (!env->prev)
	{
		env->next->prev = NULL;
		env = env->next;
	}
	else if (!env->next)
	{
		env->prev->next = NULL;
	}
	else
	{
		env->prev->next = env->next;
		env->next->prev = env->prev;
	}
	free(tmp->value);
	free(tmp);
}

void	ft_unset_end(char **str, t_data *data)
{
	t_env	*tmp;
	t_env	*env;

	env = data->env;
	while (env)
	{
		if (ft_strncmp(str[1], env->value, ft_strlen(str[1])) == 0
			&& env->value[ft_strlen(str[1])] == '=')
		{
			ft_unset_next(env);
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
		ft_end(data, str);
		exit(155);
	}
	data->exit = 0;
	if (!str[1])
	{
		return ;
	}
	else
	{
		if (ft_strncmp(str[1], "PATH", 5) == 0)
			data->r_path = FALSE;
		ft_unset_end(str, data);
	}
}
