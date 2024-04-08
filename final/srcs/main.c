/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:16:49 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/04/07 19:40:06 by lnunez-t         ###   ########.fr       */
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
		free(tools->lexer_list);
		tools->lexer_list = tmp;
		tools->lexer_list = remove_sep(tools->lexer_list);
		env_var_expand(tools);
		tools->std_out = 1;
		tools->std_int = 0;
		open_fd(tools, tools->lexer_list);
		tools->lexer_list = new_token_after_fd(tools->lexer_list);
		list_gathering(tools);
		def_index(tools->lexer_list);
		remove_quotes(tools->lexer_list);
		parsing(tools);
		ft_print_lexer(tools->lexer_list);
		free(tools->args);
		tools->args = NULL;
	}
}

void	init_minishell(t_data *tools, char **env)
{
	tools->envp = env;
	tools->env = init_env(tools);
	tools->status = 1;
	tools->exit_status = 0;
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
		str = show_prompt(tools);
		tools->args = readline(str);
		free(str);
		if (!tools->args)
			ctrl_d();
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
		printf("No arguments accepted.\n");
		free(tools);
		exit(0);
	}
	minishell(tools, env);
	return (0);
}
