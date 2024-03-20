/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 07:53:08 by matorgue          #+#    #+#             */
/*   Updated: 2024/03/20 15:37:54 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell_include.h"
#include "include/minishell_proto.h"
#include "include/minishell_struct.h"

void	ft_print_echo(t_token *token, int n)
{
	printf("%s", token->value);
	if (n == 0)
		printf("\n");
	exit(0);
}

void	ft_echo(t_token *token)
{
	int	n;

	n = 0;
	if (!token->next)
		printf("\n");
	if (token->next->type == ARG && ft_strncmp(token->next->value, "-n",
			2) == 0)
		n = 1;
	else if (!token->next && n == 0)
		printf("\n");
	if (token->next->type == WORD)
		ft_print_echo(token->next, n);
	if (token->next->type == ARG && token->next->next != NULL
		&& token->next->next->type == WORD)
		ft_print_echo(token->next->next, n);
}
