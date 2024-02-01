/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:47:18 by matorgue          #+#    #+#             */
/*   Updated: 2024/02/01 16:18:32 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell_include.h"
#include "include/minishell_proto.h"
#include "include/minishell_struct.h"

int main(int ac, char **av, char **env)
{
	s_data *data;

	data = malloc(sizeof(s_data));
	if (!data)
		return(1);
	data->env = env;
	
}
