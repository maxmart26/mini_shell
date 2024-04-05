/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:47:18 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/05 12:24:50 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_include.h"
#include "../include/minishell_proto.h"
#include "../include/minishell_struct.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

void	ft_tmp(t_data *data, t_token *token)
{
	pid_t	pid;
	t_token	*tmp;
	int		result;
	int		result2;
	t_token	*tmp2;

	tmp2 = token;
	result = -23;
	while (token)
	{
		if (token->type == CMD || token->type == CMD_BULT
			|| token->type == CMD_ABS)
		{
			pid = fork();
			if (pid == 0)
			{
				redirection_builting(token, data);
			}
			data->nb_cmd++;
		}
		tmp = token->next;
		token = tmp;
	}
	while (tmp2)
	{
		if (tmp2->type == CMD || tmp2->type == CMD_BULT
			|| tmp2->type == CMD_ABS)
		{
			//sleep(2);
			waitpid(0, &result, 2);
			//printf("\t\ttest\n");
			result2 = WEXITSTATUS(result);
			if (result2 == 155)
				ft_unset(tmp2, data, -1);
			else if (result2 == 156)
				ft_export(tmp2, data, -1);
			else if (result2 == 157)
				ft_cd(tmp2, -1, data);
			else if (result2 == 158)
				ft_exit(-1);
		}
		tmp = tmp2->next;
		tmp2 = tmp;
	}
}

void	new_token_after_fd(t_token *token)
{
	t_token	*tmp;
	t_token	*tmp2;

	while (token->next != NULL)
	{
		if (token->type == GREAT || token->type == LESS)
		{
			tmp = token;
			tmp2 = token->next;
			token->prev->next = token->next->next;
			token->next->next->prev = token->prev;
			token = token->next->next;
			free(tmp);
			free(tmp2);
		}
		else
			token = token->next;
	}
	while (token != NULL)
		token = token->prev;
}
void	free_pipe(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_pipe)
	{
		free(data->pipe_fd[i]);
		i++;
	}
	free(data->pipe_fd);
}
int	ft_main(t_data *data)
{
	open_fd(data, data->lexer_list);
	//new_token_after_fd(data->lexer_list);
	open_heredoc(data);
	ft_print_lexer(data->lexer_list);
	if (data->std_int < 0 || data->std_out < 0)
		return (printf("probleme d"), 0);
	ft_tmp(data, data->lexer_list);
	printf("\t\tici%d\n",data->std_out);
	printf("\t\tici%d\n",data->std_int);
	if (data->std_out > 2)
		close(data->std_out);
	if (data->std_int > 2)
	{
		printf("\t\ttestee\n");
		close(data->std_int);
	}
	if (data->nb_pipe > 0)
		free_pipe(data);
	return (0);
}

int	open_file(char *s, int i)
{
	int	fd;

	fd = 0;
	if (i == 1)
		fd = open(s, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (i == 0)
		fd = open(s, O_RDONLY);
	return (fd);
}

void	open_fd(t_data *data, t_token *token)
{
	t_token	*tmp;

	tmp = token->next;
	while (token)
	{
		if (token->type == GREAT)
		{
			if (data->std_out != 1)
			{
				close(data->std_out);
				data->std_out = 1;
			}
			data->std_out = open_file(token->next->value, 1);
		}
		else if (token->type == LESS)
			data->std_int = open_file(token->next->value, 0);
		if (data->std_int == -1 || data->std_out == -1)
		{
			printf("bash: %s: No such file or directory\n", token->next->value);
			if (data->nb_pipe == 0)
				exit(1);
		}
		tmp = token->next;
		token = tmp;
	}
}
