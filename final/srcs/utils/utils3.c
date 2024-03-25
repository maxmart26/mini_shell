/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:06:05 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/03/25 17:57:31 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

int	is_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	return (0);
}

int	is_quote(char c, char d)
{
	if ((c == '\'' || c == '\"') && d != '\\')
		return (1);
	return (0);
}

int	is_spe_char(char c, char d)
{
	if ((c == '|' || c == '<' || c == '>' || c == ';' || c == '&')
		&& d != '\\')
		return (1);
	return (0);
}

int	is_char(char c, char d)
{
	if (c > ' ' && c < 127 && !is_spe_char(c, d) && !is_quote(c, d))
		return (1);
	return (0);
}
