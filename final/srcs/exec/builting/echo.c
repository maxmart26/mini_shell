/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 07:53:08 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/24 14:53:51 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_include.h"
#include "../../../include/minishell_proto.h"
#include "../../../include/minishell_struct.h"

void	ft_print_echo(char **str, int n)
{
	int	nb;

	nb = n;
	while (str[n + 1])
	{
		printf("%s", str[n + 1]);
		if (str[n + 2])
			printf(" ");
		n++;
	}
	if (nb == 0)
		printf("\n");
}

int	ft_verif_echo(char *str)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] == '-')
			nb++;
		if ((str[i] != '-' && str[i] != 'n') || nb > 1)
			return (-1);
		i++;
	}
	return (0);
}

void	ft_echo(char **str, t_data *data)
{
	int	n;

	n = 0;
	ft_dup2(data);
	if (str[1] == NULL)
		printf("\n");
	while (ft_verif_echo(str[n + 1]) == 0 && str[n + 1])
	{
		n++;
	}

	if (str[n + 1])
		ft_print_echo(str, n);
	else
	{
		ft_end(data, str);
		exit(1);
	}
	ft_end(data, str);
	exit(0);
}
