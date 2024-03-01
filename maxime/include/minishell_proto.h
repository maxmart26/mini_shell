/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_proto.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:16:36 by matorgue          #+#    #+#             */
/*   Updated: 2024/02/28 21:13:23 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_include.h"
#include "minishell_struct.h"

#ifndef MINISHELL_PROTO_H
# define MINISHELL_PROTO_H

// pour les test

void	init_test(t_token *token);
t_token	*init_token(t_token *prev);
int	open_file(char *s, int i);
void	open_fd(t_data *data, t_token *token);

// init_data.c

void	init_data(t_token *token, t_data *data, char **envp);
t_env	*init_env(t_data *data);
t_env	*new_env();

//utilitaire

char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *s, size_t n);
size_t	ft_strlen(const char *s);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s);
char	*ft_strrchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);


// minishell

int	ft_main(t_token *token, char **env);

// exec.c

void	ft_exec(t_data *data, t_token *token);

// utils_bonus2.c

void	ft_close_useless(t_data *data, int i, int j);

// les builting

void	redirection_builting(t_token *token, t_data *data);
void	ft_echo(t_token *token);
void	ft_pwd(void);
void	ft_env(t_data *data);
void	ft_cd(t_token *token);
void	ft_export(t_token *token, t_data *data);

//partie laura

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
