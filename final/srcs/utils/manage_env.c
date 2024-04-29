/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:37:49 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/04/29 16:42:15 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

void	ft_destroy_env(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		temp = env;
		env = env->next;
		free(temp->value);
		free(temp);
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
	home = is_still_env_var("$HOME", tools, NULL);
	str = is_still_env_var("$PWD", tools, NULL);
	if (!home)
	{
		path = str;
		return (path);
	}
	while (str[i] == home[i])
		i++;
	path = ft_substr(str, i, ft_strlen(str) - i + 1);
	free(home);
	free(str);
	return (path);
}
