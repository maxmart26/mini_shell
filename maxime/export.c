/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:13:28 by matorgue          #+#    #+#             */
/*   Updated: 2024/03/06 15:13:52 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell_include.h"
#include "include/minishell_proto.h"
#include "include/minishell_struct.h"

void	ft_export(t_token *token, t_data *data, int i)
{
	//t_env *tmp;

	if (i == 0)
		exit(156);
	if (!data->env)
	{
		data->env = new_env();
		data->env->value = token->next->value;
	}
	else
	{
		while (data->env->next)
			data->env = data->env->next;
		data->env->next = new_env();
		data->env->next->value = token->next->value;
		data->env->next->prev = data->env;
		while(data->env->prev)
			data->env = data->env->prev;
	}
	if (i > 0)
		exit(0);
}
