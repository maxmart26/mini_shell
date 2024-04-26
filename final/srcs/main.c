/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:16:49 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/04/26 17:45:46 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_include.h"
#include "../include/minishell_proto.h"
#include "../include/minishell_struct.h"

int		g_status;

t_token	*open_fd_great(t_token *token)
{
	int	fd;

	if (token->type == GREAT)
		fd = open_file(token->next->value, 1);
	else
		fd = open_file(token->next->value, 3);
	if (fd == -1)
	{
		ft_printf_error("bash: %s: No such file or directory\n",
			token->next->value);
	}
	token = new_token(token);
	while (token->prev && token->prev->type != PIPE)
		token = token->prev;
	if (token->fd_out > 2)
		close(token->fd_out);
	if (token->fd_out == -1)
	{
		close(fd);
		fd = -1;
	}
	while (token && token->type != PIPE)
	{
		token->fd_out = fd;
		token = token->next;
	}
	return (token);
}

t_token	*open_fd_less(t_token *token)
{
	int	fd;

	fd = open_file(token->next->value, 0);
	if (fd == -1)
	{
		ft_printf_error("bash: %s: No such file or directory\n",
			token->next->value);
	}
	token = new_token(token);
	while (token->prev && token->prev->type != PIPE)
		token = token->prev;
	if (token->fd_int > 2)
		close(fd);
	if (token->fd_int == -1)
	{
		close(fd);
		fd = -1;
	}
	while (token && token->type != PIPE)
	{
		token->fd_int = fd;
		token = token->next;
	}
	return (token);
}

t_token	*open_fd_test(t_data *data)
{
	t_token	*result;
	t_token	*tmp;

	result = data->lexer_list;
	while (data->lexer_list->next)
	{
		if ((data->lexer_list->type == GREAT || data->lexer_list->type == LESS
				|| data->lexer_list->type == HEREDOC
				|| data->lexer_list->type == APPEND) && !data->lexer_list->prev)
			result = data->lexer_list->next->next;
		if (data->lexer_list->type == GREAT || data->lexer_list->type == APPEND)
			data->lexer_list = open_fd_great(data->lexer_list);
		else if (data->lexer_list->type == LESS)
			data->lexer_list = open_fd_less(data->lexer_list);
		else if (data->lexer_list->type == HEREDOC)
			data->lexer_list = open_heredoc(data, data->lexer_list);
		else if (data->lexer_list->next)
		{
			tmp = data->lexer_list->next;
			data->lexer_list = tmp;
		}
		if (!data->lexer_list || !data->lexer_list->next)
			break ;
	}
	return (result);
}
void	init_fd(t_token *token)
{
	while (token)
	{
		token->fd_int = 0;
		token->fd_out = 1;
		token = token->next;
	}
}
int	verif_open(t_token *token)
{
	while (token)
	{
		if (token->type == APPEND || token->type == GREAT || token->type == LESS
			|| token->type == HEREDOC)
			return (1);
		token = token->next;
	}
	return (0);
}
void	lexer_and_parser(t_data *tools)
{
	t_token	*tmp;

	if (tools->args)
	{
		tools->lexer_list = lexer(tools->args);
		tmp = tools->lexer_list->next;
		free(tools->lexer_list->value);
		free(tools->lexer_list);
		tmp->prev = NULL;
		tools->lexer_list = tmp;
		tools->lexer_list = remove_sep(tools->lexer_list);
		env_var_expand(tools);
		remove_quotes(tools->lexer_list);
		tools->std_out = 1;
		tools->std_int = 0;
		if (g_status == 258)
			return ;
		init_fd(tools->lexer_list);
		while (verif_open(tools->lexer_list) == 1)
			tools->lexer_list = open_fd_test(tools);
		list_gathering(tools);
		parsing(tools);
	}
}

void	init_minishell(t_data *tools, char **env)
{
	tools->envp = env;
	if (tools->envp[0] == NULL)
		tools->env = init_env_i();
	else
	{
		tools->env = init_env(tools, 0);
		init_env_shlvl(tools->env, tools, NULL, NULL);
	}
	init_path(tools);
	tools->lexer_list = NULL;
	tools->pid = NULL;
	tools->nb_pipe = 0;
	tools->std_int = 1;
	tools->lexer_list = NULL;
	tools->pid = 0;
	tools->std_out = 0;
	tools->status = 1;
	tools->exit = 0;
	tools->exit_status = 0;
	tools->exit = 0;
	g_status = 1;
	tools->first_call = 1;
	show_ctrl(1);
	signal(SIGQUIT, &ft_signal_handler);
	handle_signal();
}

int	minishell(t_data *tools, char **env)
{
	char	*str;

	init_minishell(tools, env);
	while (g_status)
	{
		str = show_prompt();
		tools->args = readline(str);
		free(str);
		if (!tools->args)
			ctrl_d(tools);
		check_new_line(tools);
		if (tools->nl_error == 0 || tools->nl_error == 2)
		{
			add_history(tools->args);
			if (tools->nl_error == 0)
			{
				lexer_and_parser(tools);
				init_data(tools->lexer_list, tools);
				if (g_status != 258)
					ft_main(tools);
			}
		}
		free(tools->args);
	}
	free_minishell(tools);
	return (EXIT_SUCCESS);
}

int	main(int ac, char **argv, char **env)
{
	t_data	*tools;

	(void)argv;
	tools = malloc(sizeof(t_data));
	if (!tools)
		return (free(tools), EXIT_FAILURE);
	if (ac != 1)
	{
		ft_printf_error("No arguments accepted.\n");
		free(tools);
		exit(0);
	}
	minishell(tools, env);
	return (0);
}
