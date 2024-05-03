/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:06:30 by matorgue          #+#    #+#             */
/*   Updated: 2024/05/02 13:27:01 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCT_H
# define MINISHELL_STRUCT_H

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
	HEREDOC,
	APPEND,
	GREAT,
	LESS,
	PIPE,
	S_QUOTE,
	D_QUOTE,
	WORD,
	SEP,
	NEWL,
	NONE,
	CMD,
	CMD_ABS,
	CMD_BULT,
	SEMI,
	ARG,
	OPT,
}						t_token_type;

typedef struct s_token
{
	int					index;
	char				**str;
	t_token_type		type;
	char				*value;
	int					fd_out;
	int					fd_int;
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
	struct s_env		*next;
	struct s_env		*prev;
}						t_env;

typedef struct s_data
{
	char				**envp;
	t_env				*env;
	char				*args;
	t_token				*lexer_list;
	char				*itoa;
	char				*init_path;
	bool				r_path;
	int					f1;
	int					std_out;
	int					std_int;
	int					nb_pipe;
	int					**pipe_fd;
	char				*path_def;
	char				*path_from_envp;
	char				**path;
	char				**mycmdargs;
	char				*path_temp;
	int					nb_cmd;
	pid_t				*pid;
	int					nb_com;
	int					fd_in;
	int					fd_out;
	int					pide;
	int					k;
	int					status;
	int					exit_status;
	int					nl_error;
	int					first_call;
	int					exit;
	int					in_file;
}						t_data;

extern int				g_status;

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

typedef struct s_char_list
{
	char				value;
	int					len;
	struct s_char_list	*next;
}						t_char_list;

typedef struct s_hist_list
{
	char				value;
	int					history;
	int					index;
	int					up_or_down;
	t_char_list			*char_list;
	t_char_list			*origin_char_list;
	struct s_hist_list	*next;
	struct s_hist_list	*prev;
}						t_hist_list;
#endif
