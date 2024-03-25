/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:23:28 by matorgue          #+#    #+#             */
/*   Updated: 2024/03/25 15:23:57 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_include.h"
#include "../../../include/minishell_proto.h"
#include "../../../include/minishell_struct.h"

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
