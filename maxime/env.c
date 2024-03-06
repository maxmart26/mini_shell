/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:23:28 by matorgue          #+#    #+#             */
/*   Updated: 2024/03/05 23:21:15 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell_include.h"
#include "include/minishell_proto.h"
#include "include/minishell_struct.h"

void	ft_env(t_data *data)
{
	t_env *tmp;
	t_env *init;

	init = data->env;
	while (data->env->prev != NULL)
		data->env = data->env->prev;
	if (!data->env)
		exit(0);
	printf("\n\n\n\n\n\n\n");
	while (init)
	{
		printf("%s\n", init->value);
		tmp = init->next;
		init = tmp;
	}
	printf("\n\n\n\n\n\n\n");
	exit(0);
}
