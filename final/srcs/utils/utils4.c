/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:23:51 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/05/06 17:25:33 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

int	ft_check_symbol(int i, char *str)
{
	if (str[i] && (str[i] != ' ' && str[i] != '\"' && str[i] != '\''
			&& str[i] != '.' && str[i] != '%' && str[i] != ';' && str[i] != '$'
			&& str[i] != '!' && str[i] != ':' && str[i] != '*'))
		return (1);
	else
		return (0);
}
