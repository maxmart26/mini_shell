/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:30:58 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/03/13 15:57:55 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

char	*ft_get_input(t_rdline rdline, int *status, struct termios old_term)
{
	long	c;
	t_list	*current;
	int		newline_stop;

	current = ft_init_history(&c, &newline_stop);
	while (newline)
	{
		
	}
}
