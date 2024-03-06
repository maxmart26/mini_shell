/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:09:46 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/03/06 17:58:24 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/get_next_line/get_next_line.h"
# include "../libs/libft/libft.h"
# include "error.h"
# include "lexer.h"
# include "messages.h"
# include "parser.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

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
	char			*value;
	char			*name;
	char			*content;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

typedef struct s_tools
{
	char			**envp;
	char			*args;
	t_token			*lexer_list;
	t_env			*env;
	int				pid;
	int				nb_pipes;
}					t_tools;

t_token				*first_token(void);
void				fill_token_list(t_token *token_list, char *str);
t_token				*lexer(char *str);
void				add_token(t_token *token_list, t_token_type type, char *str,
						int i);
void				destroy_token_list(t_token *token_list);
void				get_token(t_token *token_list, char *str, int *i, int *j);
void				get_word(t_token *token_list, char *str, int *i,
						int *index);
char				*get_str(char *line, int *j, char *word, int *nb_quote);
char				*get_nq_word(char *line, int *j);
char				*get_dq_word(char *line, int *j, int i);
char				*get_q_word(char *line, int *j, int nb_quote);
char				*what_type(t_token *list);
char				*other_type(t_token *list, char *type);
t_token				*remove_sep(t_token *list);
void				def_index(t_token *list);
void				ft_print_lexer(t_token *list);
void				manage_type(t_token *token);
void				manage_cmd(t_token *token);
void				manage_cmd_buil(t_token *token);

void				count_pipes(t_token *list, t_tools *tools);
int					count_quotes(char *str);
int					find_matching_quote(char *str, int i, int *nb_q, int q);
void				list_gathering(t_tools *tools);
int					ft_error(int error);
t_env				*init_env(t_tools *env_tool);
t_env				*new_env(void);
void				init_tools(t_tools *tools, char **envp);
void				env_var_expand(t_tools *tools);
char				*replace_env_var(char *str);
int					is_env_var(char *str);

#endif
