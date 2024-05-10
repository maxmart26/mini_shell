/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 14:09:54 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/05/10 07:12:08 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_include.h"
#include "../../../include/minishell_proto.h"
#include "../../../include/minishell_struct.h"

void	ft_free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		if (env->value != NULL)
			free(env->value);
		tmp = env->next;
		free(env);
		env = tmp;
	}
}

void	ft_free_pipe(int **fd, int i)
{
	while (i > 0)
	{
		free(fd[i - 1]);
		i--;
	}
	free(fd);
}

int	verif(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if ((str[i] > '9' || str[i] < '0') && str[i] != '-' && str[i] != '+')
			return (1);
		i++;
	}
	return (0);
}

void	ft_end_exit(char **str, t_data *data, int i)
{
	if (!str[1])
		data->exit = 0;
	else if (str[1] && str[1][0] == '-')
		data->exit = ft_atoll(str[1]);
	else
		data->exit = ft_atoull(str[1]);
	i = data->exit;
	ft_end(data);
	ft_printf_error("exit\n");
	exit(i);
}

void	ft_exit(t_data *data, int i, char **str)
{
	if (i == 0)
	{
		ft_end(data);
		exit(158);
	}
	if (str[1])
	{
		if (str[2])
		{
			ft_printf_error(" too many arguments\n");
			return ;
		}
	}
	if (verif(str[1]) == 1)
	{
		ft_printf_error(" numeric argument required\n");
		ft_end(data);
		exit(2);
	}
	ft_end_exit(str, data, i);
}
