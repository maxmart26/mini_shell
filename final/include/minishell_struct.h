/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:06:30 by matorgue          #+#    #+#             */
/*   Updated: 2024/03/13 16:23:17 by lnunez-t         ###   ########.fr       */
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

/*****LEXER*****/

typedef enum e_token_type
{
	HEREDOC,  // >>
	APPEND,   // <<
	GREAT,    // >
	LESS,     // <
	PIPE,     // |
	S_QUOTE,  // '
	D_QUOTE,  // "
	WORD,     // mots
	SEP,      // espace
	NEWL,     // \n
	NONE,     // rien
	CMD,      // commande qui ne commance pas part un /
	CMD_ABS,  // commande absolu qui commance par un /
	CMD_BULT, // commande builtins
	SEMI,     // ;
	ARG,      // file1
	OPT,      // -l
}						t_token_type;

typedef struct s_token
{
	int					index;
	t_token_type		type;
	char				*value;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

/*****PARSER*****/

typedef struct s_parser
{
	t_token				*lexer_list;
	t_token				redirs;
	int					nb_redirs;
	struct s_tools		*tools;
}						t_parser;

/*****GENERAL*****/

typedef struct s_env
{
	char				*value;
	char				*name;
	char				*content;
	struct s_env		*next;
	struct s_env		*prev;
}						t_env;

t_g_vars	g_vars;

typedef struct s_data
{
	char				**envp;
	t_env				*env;
	char				*args;
	t_token				*lexer_list;
	char				*itoa;
	int					f1;
	int					std_out;
	int					std_int;
	int					nb_pipe;
	int					**pipe_fd;
	int					nb_cmd;
	int					fd_in;
	int					fd_out;
	int					pid;
}						t_data;

/******READLINE*******/

# define D_KEY_ESCAPE 27
# define D_KEY_SPACE 32
# define D_KEY_UP 4283163
# define D_KEY_DOWN 4348699
# define D_KEY_RIGHT 4414235
# define D_KEY_LEFT 4479771
# define D_KEY_ENTER 10
# define D_KEY_BACKSPACE 127
# define D_KEY_CTRL_C 3
# define D_KEY_CTRL_D 4

typedef struct s_cursor
{
	int					line_postion;
	int					col_position;
}						t_cursor;

typedef struct s_char_list
{
	char				value;
	int					len;
	struct s_char_list	*next;
}						t_char_list;

typedef struct s_list
{
	char				value;
	int					history;
	int					index;
	int				up_or_down;
	t_char_list			*char_list;
	t_char_list			*origin_char_list;
	struct s_lines_list	*next;
	struct s_lines_list	*prev;
}						t_list;

typedef struct s_rdline
{
	char				*term_type;
	int					term_fd;
	int					line_count;
	int					colums_count;
	// long		c;
	char				*path;
	char				*line;
	t_cursor			cursor;
}						t_rdline;

#endif
