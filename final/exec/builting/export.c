/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:13:28 by matorgue          #+#    #+#             */
/*   Updated: 2024/03/12 15:02:46 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

void	ft_export_modif(t_token *token, t_env *env, char **str)
{
	env->value = token->next->value;
	free(env->name);
	free(env->content);
	env->content = str[1];
	env->name = str[0];
	free(str);
}

int	ft_export_ex(t_token *token, t_data *data, char **str)
{
	t_env	*init;

	init = data->env;
	// printf("%s\n",init->value);
	while (init->next)
	{
		if (ft_strncmp(init->name, str[0], ft_strlen(str[0])) == 0
			&& ft_strlen(str[0]) == ft_strlen(init->name))
		{
			// printf("\n\n\n\n\t\ttest\n");
			ft_export_modif(token, init, str);
			return (0);
		}
		init = init->next;
	}
	while (init->prev)
		init = init->prev;
	return (1);
}

void	ft_modif(char **str)
{
	long	nb;
	long	result;

	result = 0;
	printf("%s\n", str[1]);
	nb = ft_atol(str[1]);
	while (1)
	{
		if (nb > 2147483647)
		{
			result = -2147483648;
			nb -= 2147483647;
			result += nb;
		}
		//if (nb <= 2147483647 && nb >= -2147483648)
			//return (result);
	}
	printf("%ld\n", nb);
}
void	ft_export(t_token *token, t_data *data, int i)
{
	char	**str;

	if (i == 0)
		exit(156);
	str = ft_split(token->next->value, '=');
	// if (ft_strncmp(str[0], "SHLVL", 5) == 0 && ft_strlen(str[0]) == 5)
	// 	ft_modif(str);
	if (ft_export_ex(token, data, str) == 1)
	{
		if (!data->env)
		{
			data->env = new_env();
			data->env->value = token->next->value;
			data->env->content = str[1];
			data->env->name = str[0];
			free(str);
		}
		else
		{
			while (data->env->next)
				data->env = data->env->next;
			data->env->next = new_env();
			data->env->next->value = token->next->value;
			data->env->next->prev = data->env;
			data->env->next->content = str[1];
			data->env->next->name = str[0];
			free(str);
			while (data->env->prev)
				data->env = data->env->prev;
		}
	}
	if (i > 0)
		exit(0);
}
