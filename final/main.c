/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:16:49 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/03/12 15:27:43 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell_include.h"
#include "include/minishell_proto.h"
#include "include/minishell_struct.h"


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
		def_index(tools->lexer_list);
		//printf("\n%s\n\n", LEGEND);
		//ft_print_lexer(tools->lexer_list);
		//printf("\n%s\n\n", LEGEND);
		env_var_expand(tools);
		add_cmd(tools->lexer_list);
		add_args(tools->lexer_list);
		//ft_print_lexer(tools->lexer_list);
		//printf("\n%s\n\n", LEGEND);
		list_gathering(tools);
		ft_print_lexer(tools->lexer_list);
		free(tools->args);
		tools->args = NULL;
	}
	/*if (tools->lexer_list)
		parser(tools);*/
}


int	minishell(t_data *tools, char **env)
{
	//signal(SIGINT, &ft_signal_handler);
	//signal(SIGQUIT, &ft_signal_handler);
	tools->envp = env;
	tools->env = init_env(tools);
	//printf("%s\n", env_list->name);
	while (1)
	{
		tools->args = readline("matorgue:~$ ");
		if (!tools->args)
			exit(EXIT_SUCCESS);
		//add_history(tools->args);
		if (!count_quotes(tools->args))
			return (ft_error(0));
		lexer_and_parser(tools);
		init_data(tools->lexer_list, tools, env); // malloc la tools
		ft_main(tools);
	}
	ft_destroy_env(tools->env);
	return (EXIT_SUCCESS);
}

int	main(int ac, char **argv, char **env)
{
	t_data	*tools;

	(void)argv;
	tools = malloc(sizeof(t_data));
	if (!tools)
		return(EXIT_FAILURE);
	if (ac != 1)
	{
		printf("No arguments accepted.\n");
		exit(0);
	}
	minishell(tools, env);
	return (0);
}
