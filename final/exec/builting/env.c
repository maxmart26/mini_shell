/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:23:28 by matorgue          #+#    #+#             */
/*   Updated: 2024/03/27 06:10:24 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

void	ft_env(t_data *data)
{
	t_env *tmp;
	t_env *init;

	init = data->env;
	ft_export(token_init("export", "_=env"), data, -1);
	while (data->env->prev != NULL)
		data->env = data->env->prev;
	if (!data->env)
		exit(0);
	ft_dup2(data);
	while (init)
	{
		printf("%s\n", init->value);
		// printf("%s\n", init->name);
		// printf("%s\n", init->content);
		tmp = init->next;
		init = tmp;
	}
	exit(0);
}
