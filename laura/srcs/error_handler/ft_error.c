/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:43:26 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/02/29 17:58:46 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_error(int error)
{
	if (error == 0)
		ft_putstr_fd(SYNTAX_ERR, 2);
	return (EXIT_FAILURE);
}
