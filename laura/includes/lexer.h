/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:43:51 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/02/22 15:50:26 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libs/libft/libft.h"
# include "../libs/get_next_line/get_next_line.h"

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
	SEMI,
	ARG,
}	t_token_type;

typedef struct s_token
{
	int				index;
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

t_token	*first_token(void);
void	fill_token_list(t_token *token_list, char *str);
t_token	*lexer(char *str);
void	add_token(t_token *token_list, t_token_type type,
			char *str, int i);
void	destroy_token_list(t_token *token_list);
void	get_token(t_token *token_list, char *str, int *i, int *j);
void	get_word(t_token *token_list, char *str, int *i, int *index);
char	*get_str(char *line, int *j, char *word, int *nb_quote);
char	*get_nq_word(char *line, int *j);
char	*get_dq_word(char *line, int *j, int i);
char	*get_q_word(char *line, int *j, int nb_quote);
char	*what_type(t_token *list);
char	*other_type(t_token *list, char *type);
t_token	*remove_sep(t_token *list);
void	def_index(t_token *list);

#endif
