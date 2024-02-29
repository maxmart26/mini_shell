/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:16:49 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/02/29 19:27:41 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	lexer_and_parser(t_tools *tools)
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
		printf("\n%s\n\n", LEGEND);
		manage_type(tools->lexer_list);
		ft_print_lexer(tools->lexer_list);
		printf("\n%s\n\n", LEGEND);
		list_gathering(tools);
		ft_print_lexer(tools->lexer_list);
		free(tools->args);
		tools->args = NULL;
	}
	/*if (tools->lexer_list)
		parser(tools);*/
}

int	minishell(t_tools *tools, char **env)
{
	t_env	*env_list;

	init_env(&env_list, env);
	//printf("%s\n", env_list->name);
	while (1)
	{
		tools->args = readline("matorgue:~$ ");
		if (!tools->args)
			exit(EXIT_SUCCESS);
		add_history(tools->args);
		if (!count_quotes(tools->args))
			return (ft_error(0));
		lexer_and_parser(tools);
	}
	return (EXIT_SUCCESS);
}

int	main(int ac, char **argv, char **env)
{
	t_tools	tools;

	(void)argv;
	if (ac != 1)
	{
		printf("No arguments accepted.\n");
		exit(0);
	}
	minishell(&tools, env);
	return (0);
}
