/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 07:53:08 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/05 19:34:28 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_include.h"
#include "../../../include/minishell_proto.h"
#include "../../../include/minishell_struct.h"

void	ft_print_echo(char **str, int n)
{
	int nb;

	nb = n;
	while(str[n + 1])
	{
		printf("%s", str[n + 1]);
		if(str[n + 2])
			printf(" ");
		n++;
	}
	if (nb == 0)
		printf("\n");
	exit(0);
}

int	ft_verif_echo(char *str)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while(str[i])
	{
		if (str[i] == '-')
			nb++;
		if ((str[i] != '-' && str[i] != 'n' ) || nb > 1)
			return (-1);
		i++;
	}
	return(0);
}
void	ft_echo(char **str)
{
	int	n;

	n = 0;
	if (str[1] == NULL)
		printf("\n");
	while(ft_verif_echo(str[n + 1]) == 0 && str[n + 1])
	{
		//printf("test\n");
		n++;
	}
	if(str[n + 1])
		ft_print_echo(str, n);
	// if (ft_verif_echo(str[1]) == 0)
	// 	n = 1;
	// else if (!token->next && n == 0)
	// 	printf("\n");
	// if (token->next->type == ARG)
	// 	ft_print_echo(token->next, n);
	// if (token->next->type == OPT && token->next->next != NULL && \
	// token->next->next->type == ARG)
	// 	ft_print_echo(token->next->next, n);
	exit(0);
}
