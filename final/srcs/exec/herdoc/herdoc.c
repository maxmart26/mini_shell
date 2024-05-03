/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:06:12 by matorgue          #+#    #+#             */
/*   Updated: 2024/05/03 15:24:32 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_include.h"
#include "../../../include/minishell_proto.h"
#include "../../../include/minishell_struct.h"

void	ft_here_doc_put_in(t_data *data, char *av)
{
	char	*ret;

	while (1)
	{
		ft_putstr_fd(">", 2);
		ret = get_next_line(0);
		if (!ret)
		{
			if (g_status == 5)
				ft_printf_error("bash: warning: here-doc not delimited by end-of-file\n");
			else
				printf("\n");
			close(data->f1);
			return ;
		}
		if (ft_strncmp(ret, av, ft_strlen(av)) == 0
			&& ft_strlen(av) == ft_strlen(ret + 1))
		{
			free(ret);
			return ;
		}
		ft_putstr_fd(ret, data->f1);
		free(ret);
	}
}

int	ft_access(void)
{
	int		i;
	char	*c;
	char	*str;

	i = 0;
	while (1)
	{
		c = ft_itoa(i);
		str = ft_strjoin("/tmp/.here_doc", c);
		if (access(str, F_OK) == -1)
			break ;
		else
			i++;
		free(c);
		free(str);
	}
	free(c);
	free(str);
	return (i);
}

void	ft_herdoc(t_data *data, t_token *tmp, int i)
{
	char	*c;

	i = ft_access();
	c = ft_itoa(i);
	data->itoa = ft_strjoin("/tmp/.here_doc", c);
	data->f1 = open((data->itoa), O_CREAT | O_RDWR | O_TRUNC, 0777);
	free(c);
	if (data->f1 < 0)
		return ;
	ft_here_doc_put_in(data, tmp->next->value);
	close(data->f1);
	if (g_status != 5 && g_status != 6)
		data->f1 = open(data->itoa, O_RDONLY);
	unlink(data->itoa);
	free(data->itoa);
	data->std_int = data->f1;
}

t_token	*open_heredoc(t_data *data, t_token *token)
{
	signal(SIGQUIT, SIG_IGN);
	g_status = 5;
	ft_herdoc(data, token, 0);
	token = new_token(token);
	if (!token)
		return (NULL);
	while (token->prev && token->prev->type != PIPE)
		token = token->prev;
	if (token->fd_int == -1)
	{
		close(data->std_int);
		data->std_int = -1;
	}
	while (token->next && token->next->type != PIPE)
	{
		token->fd_int = data->std_int;
		token = token->next;
	}
	return (token);
}
