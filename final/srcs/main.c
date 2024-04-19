/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:16:49 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/04/19 15:38:22 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_include.h"
#include "../include/minishell_proto.h"
#include "../include/minishell_struct.h"

int		g_status;

void	lexer_and_parser(t_data *tools)
{
	t_token	*tmp;

	if (tools->args)
	{
		tools->lexer_list = lexer(tools->args);
		tmp = tools->lexer_list->next;
		free(tools->lexer_list->value);
		free(tools->lexer_list);
		tools->lexer_list = tmp;
		tools->lexer_list = remove_sep(tools->lexer_list);
		env_var_expand(tools);
		remove_quotes(tools->lexer_list);
		ft_print_lexer(tools->lexer_list);
		tools->std_out = 1;
		tools->std_int = 0;
		open_fd(tools, tools->lexer_list);
		open_heredoc(tools);
		if (g_status == 258)
			return ;
		if (tools->std_int > 2 || tools->std_out > 2)
			tools->lexer_list = new_token_after_fd(tools->lexer_list);
		list_gathering(tools);
		def_index(tools->lexer_list);
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
		init_env_shlvl(tools->env, tools);
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
