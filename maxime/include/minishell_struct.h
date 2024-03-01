/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:06:30 by matorgue          #+#    #+#             */
/*   Updated: 2024/02/28 20:17:12 by matorgue         ###   ########.fr       */
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
	ARG, // -l
}					t_token_type;

typedef struct s_token
{
	int				index;
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_env
{
	char *value;
	struct s_env	*next;
}					t_env;

typedef struct s_data
{
	char **envp;
	t_env *env;
	int std_out;
	int	std_int;
	int nb_pipe;
	int	**pipe_fd;
	int	nb_cmd;
	int	fd_in;
	int	fd_out;
}	t_data;

#endif
