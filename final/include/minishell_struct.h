/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:06:30 by matorgue          #+#    #+#             */
/*   Updated: 2024/03/12 14:50:45 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_token_type
{
	HEREDOC, // >>
	APPEND, // <<
	GREAT, // >
	LESS, // <
	PIPE, // |
	S_QUOTE, // '
	D_QUOTE, // "
	WORD, // mots
	SEP, // espace
	NEWL, // \n
	NONE, // rien
	CMD, // commande qui ne commance pas part un /
	CMD_ABS, // commande absolu qui commance par un /
	CMD_BULT, // commande builtins
	SEMI, // ;
	ARG, // file1
	OPT, // -l
}					t_token_type;

typedef struct s_token
{
	int				index;
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_parser
{
	t_token			*lexer_list;
	t_token			redirs;
	int				nb_redirs;
	struct s_tools	*tools;
}					t_parser;

typedef struct s_env
{
	char *value;
	char *name;
	char *content;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

typedef struct s_data
{
	char **envp;
	t_env *env;
	char			*args;
	t_token		*lexer_list;
	int	itoa;
	int	f1;
	int std_out;
	int	std_int;
	int nb_pipe;
	int	**pipe_fd;
	int	nb_cmd;
	int	fd_in;
	int	fd_out;
	int pid;
}	t_data;

#endif
