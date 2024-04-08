/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:25:03 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/04/07 19:49:29 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

int	copy_value(int len, t_char_list **origin, t_char_list **tmp)
{
	(*tmp)->value = (*origin)->value;
	(*tmp)->len = (*origin)->len;
	(*tmp)->next = NULL;
	len--;
	*origin = (*origin)->next;
	return (len);
}

int	get_len(t_char_list *origin)
{
	int	i;

	i = 0;
	if (origin == NULL)
		return (i);
	else
	{
		while (origin)
		{
			i++;
			origin = origin->next;
		}
		return (i);
	}
}

t_char_list	*copy_char_list(t_char_list *list)
{
	int			len;
	t_char_list	*tmp;
	t_char_list	*copy;
	t_char_list	*origin;

	origin = list;
	copy = NULL;
	len = get_len(origin);
	if (len == 0)
		return (NULL);
	else
	{
		copy = (t_char_list *)malloc(sizeof(t_char_list));
		tmp = copy;
		while (len > 0)
		{
			len = copy_value(len, &origin, &tmp);
			if (len > 0)
			{
				tmp->next = (t_char_list *)malloc(sizeof(t_char_list));
				tmp = tmp->next;
			}
		}
		return (copy);
	}
}

void	delete_char_list(t_char_list *list)
{
	t_char_list	*tmp;
	t_char_list	*tmp1;

	tmp = list;
	while (tmp)
	{
		tmp1 = tmp;
		tmp = tmp->next;
		free(tmp1);
		tmp1 = NULL;
	}
}

char	*show_prompt(t_data *tools)
{
	char	*str;
	char	*user;
	char	*session;
	char	*path;

	user = is_still_env_var("$USER", tools);
	if (!user)
		return (NULL);
	str = ft_strjoin(user, "@");
	free(user);
	session = prompt_get_sess();
	if (session == NULL)
	{
		ft_putstr_fd("Error : no session_manager variabe in env", 1);
		free(str);
		return (NULL);
	}
	str = ft_strjoin(str, session);
	str = ft_strjoin(str, ":~");
	free(session);
	path = prompt_get_path(tools);
	if (path == NULL)
	{
		ft_putstr_fd("Error : no path variable in env", 1);
		free(str);
		return (NULL);
	}
	str = ft_strjoin(str, path);
	str = ft_strjoin(str, "$ ");
	return (str);
}
