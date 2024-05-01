/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:52:29 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/05/01 17:47:52 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

int	find_matching_quote(char *str, int i, int *nb_q, int q)
{
	int	j;

	j = i + 1;
	*nb_q += 1;
	while (str[j] && str[j] != q)
		j++;
	if (str[j] == q)
		*nb_q += 1;
	return (j - i);
}

int	count_quotes(char *str)
{
	int	i;
	int	nb_sq;
	int	nb_dq;

	i = 0;
	nb_sq = 0;
	nb_dq = 0;
	while (str[i] && str[i + 1])
	{
		if (str[i] == 34)
			i += find_matching_quote(str, i, &nb_dq, 34);
		if (str[i] == 39)
			i += find_matching_quote(str, i, &nb_sq, 39);
		i++;
	}
	if ((nb_dq > 0 && nb_dq % 2 != 0) || (nb_sq > 0 && nb_sq % 2 != 0))
		return (0);
	return (1);
}

void	count_pipes(t_token *list, t_data *tools)
{
	t_token	*tmp;

	tmp = list;
	tools->nb_pipe = 0;
	while (tmp)
	{
		if (tmp->type == PIPE)
			tools->nb_pipe++;
		tmp = tmp->next;
	}
}

int	is_env_var(char *str, t_data *tools, char *env_var)
{
	int (start) = 0;
	int (i) = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (!str[i + 1])
				break ;
			start = i + 1;
			while (str[i] && (str[i] != ' ' || str[i] != '\"' || str[i] != '\''))
				i++;
			while (str[i - 1] == '\"' || str[i] != '\'')
				i--;
			env_var = ft_substr(str, start, i - start);
			if (!find_env_var(env_var, tools->env))
			{
				free(env_var);
				break ;
			}
			else
				return (free(env_var), 1);
		}
		i++;
	}
	return (0);
}

void	ft_signal_handler(int signal)
{
	ft_putstr_fd("Quit (core dumped)", STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	(void)signal;
}
