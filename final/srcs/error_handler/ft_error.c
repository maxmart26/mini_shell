/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:43:26 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/03/06 18:24:19 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"


int	ft_error(int error)
{
	if (error == 0)
		ft_putstr_fd(SYNTAX_ERR, 2);
	return (EXIT_FAILURE);
}
