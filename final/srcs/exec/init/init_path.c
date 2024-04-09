/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:32:35 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/09 18:04:27 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_include.h"
#include "../../../include/minishell_proto.h"
#include "../../../include/minishell_struct.h"

void	init_path(t_data *data)
{
	data->r_path = TRUE;
	data->init_path = "/home/matorgue/bin:/home/matorgue/bin:/usr/local/sbin:/usr/loc\
	al/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin";
}

char	*exec_path(t_data *data)
{
	int	i;

	i = 0;
	data->path = ft_split(data->init_path, ':');
	while (data->path[i])
	{
		data->path_temp = ft_strjoin(data->path[i], "/");
		data->path_def = ft_strjoin(data->path_temp, data->mycmdargs[0]);
		free(data->path_temp);
		if (access(data->path_def, 0) == 0)
			return (data->path_def);
		else
		{
			free(data->path_def);
		}
		i++;
	}
	return (NULL);
}

void	init_end(t_env *env)
{
	env->name = "PWD";
	env->content = getcwd(env->content, _SC_PASS_MAX);
	env->next->name = "SHLVL";
	env->next->content = "1";
	env->next->next->name = "_";
	env->next->next->content = "/usr/bin/env";
}

void	init_env_shlvl(t_env *env, t_data *data)
{
	int		a;
	char	*str;
	char	**tab_str;

	while (env)
	{
		if (strncmp(env->name, "SHLVL", 6) == 0)
		{
			a = ft_atoi(env->content);
			a++;
			str = ft_strjoin("SHLVL=", ft_itoa(a));
			ft_export(token_init("export", str), data, -1);
			free(str);
		}
		env = env->next;
	}
}
