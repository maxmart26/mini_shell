/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:23:28 by matorgue          #+#    #+#             */
/*   Updated: 2024/05/05 18:25:01 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_include.h"
#include "../../../include/minishell_proto.h"
#include "../../../include/minishell_struct.h"

void	ft_env(t_data *data, t_token *token)
{
	t_env *(tmp) = NULL;
	t_env *(init) = data->env;
	if (!init)
	{
		ft_end(data);
		exit(0);
	}
	while (data->env->prev != NULL)
		data->env = data->env->prev;
	if (!data->env)
		exit(0);
	ft_dup2(data, token);
	while (init)
	{
		if (printf("%s\n", init->value) == -1)
		{
			ft_printf_error("env: write error: No space left on device\n");
			break ;
		}
		tmp = init->next;
		init = tmp;
	}
	ft_end(data);
	exit(0);
}
