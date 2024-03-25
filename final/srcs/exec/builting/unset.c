/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:52:41 by matorgue          #+#    #+#             */
/*   Updated: 2024/03/25 15:24:13 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_include.h"
#include "../../../include/minishell_proto.h"
#include "../../../include/minishell_struct.h"

void	ft_unset_next(t_data *data)
{
	t_env	*tmp;

	if (!data->env->prev)
	{
		data->env->next->prev = NULL;
		tmp = data->env;
		data->env = data->env->next;
	}
	else if (!data->env->next)
	{
		data->env->prev->next = NULL;
		tmp = data->env;
	}
	else
	{
		tmp = data->env;
		data->env->prev->next = data->env->next;
		data->env->next->prev = data->env->prev;
	}
	free(tmp->content);
	free(tmp->name);
	free(tmp);
}

void	ft_unset(t_token *token, t_data *data, int i)
{
	if (i == 0)
		exit(155);
	while (data->env)
	{
		if (ft_strncmp(token->next->value, data->env->value,
				ft_strlen(token->next->value)) == 0
			&& data->env->value[ft_strlen(token->next->value)] == '=')
		{
			ft_unset_next(data);
			break ;
		}
		else
		{
			if (!data->env->next)
				break ;
			data->env = data->env->next;
		}
	}
	while (data->env->prev)
		data->env = data->env->prev;
	if (i > 0)
		exit(0);
}
