/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:37:49 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/04/10 17:54:42 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

/*void	ft_destroy_env(t_env *env_list)
{
	t_env	*tmp;
	t_env	*new;

	tmp = env_list;
	if (tmp == NULL)
		return ;
	while (tmp)
	{
		free(tmp->content);
		free(tmp->name);
		//free(tmp->value);
		new = tmp->next;
		free(tmp);
		tmp = new;
	}
}*/

void	ft_destroy_env(t_env *env_list)
{
	t_env	*next;

	while (env_list)
	{
		next = env_list->next;
		if (env_list->name)
		{
			free(env_list->name);
			env_list->name = NULL;
		}
		if (env_list->content)
		{
			free(env_list->content);
			env_list->content = NULL;
		}
		if (env_list->value)
		{
			free(env_list->value);
			env_list->value = NULL;
		}
		free(env_list);
		env_list = next;
	}
}

char	*prompt_get_sess(void)
{
	char	*session;
	char	*str;
	int		i;
	int		start;

	i = 0;
	start = 0;
	str = getenv("SESSION_MANAGER");
	if (str == NULL)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '/')
		{
			i++;
			start = i;
			while (str[i] != '.')
				i++;
			session = ft_substr(str, start, i - start);
			return (session);
		}
		i++;
	}
	return (NULL);
}

char	*prompt_get_path(t_data *tools)
{
	char	*path;
	char	*home;
	char	*str;
	int		i;

	i = 0;
	path = NULL;
	home = is_still_env_var("$HOME", tools);
	str = is_still_env_var("$PWD", tools);
	if (!home)
	{
		path = str;
		//free(home);
		//free(str);
		return (path);
	}
	while (str[i] == home[i])
		i++;
	path = ft_substr(str, i, ft_strlen(str) - i + 1);
	free(home);
	free(str);
	return (path);
}
