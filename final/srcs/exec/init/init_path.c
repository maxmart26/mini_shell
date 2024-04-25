/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:32:35 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/25 16:25:43 by matorgue         ###   ########.fr       */
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
	(void)env;
}

void	init_env_shlvl(t_env *env, t_data *data, char *str, char *stt)
{
	int		a;
	char	**st;

	if (!env)
	{
		ft_destroy_env(env);
		return ;
	}
	while (env)
	{
		if (ft_strncmp(env->value, "SHLVL", 6) == 0)
		{
			a = ft_atoi(&env->value[6]);
			if (a < 0)
				return ;
			a++;
			stt = ft_itoa(a);
			str = ft_strjoin("SHLVL=", stt);
			st = token_init("export", str);
			free(stt);
			free(str);
			ft_export(st, data, -1, NULL);
		}
		env = env->next;
	}
}
