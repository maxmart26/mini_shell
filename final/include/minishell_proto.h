/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_proto.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laura <laura@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:16:36 by matorgue          #+#    #+#             */
/*   Updated: 2024/03/11 15:18:33 by laura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PROTO_H
# define MINISHELL_PROTO_H

# include "minishell_include.h"
# include "minishell_struct.h"

// pour les tests

void	init_test(t_token *token);
t_token	*init_token(t_token *prev);
int		open_file(char *s, int i);
void	open_fd(t_data *data, t_token *token);

// init_data.c

void	init_data(t_token *token, t_data *data, char **envp);
t_env	*init_env(t_data *data);
t_env	*new_env(void);

// utilitaire

char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *s, size_t n);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s);
char	*ft_strrchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);

// minishell

int		ft_main(t_data *data);

// herdoc.c

void	open_heredoc(t_data *data);

// exec.c

void	ft_exec(t_data *data, t_token *token);
void	ft_exec_abs(t_token *token, t_data *data);
void	ft_dup2(t_data *data);

// utils_bonus2.c

void	ft_close_useless(t_data *data, int i, int j);

// token_init.c

t_token	*token_init(char *str, char *st);

// les builting

void	redirection_builting(t_token *token, t_data *data);
void	ft_echo(t_token *token);
void	ft_pwd(void);
void	ft_env(t_data *data);
void	ft_cd(t_token *token, int i, t_data *data);
void	ft_export(t_token *token, t_data *data, int i);
void	ft_unset(t_token *token, t_data *data, int i);

// partie laura

t_token	*first_token(void);
void	fill_token_list(t_token *token_list, char *str);
t_token	*lexer(char *str);
void	add_token(t_token *token_list, t_token_type type, char *str, int i);
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
void	ft_print_lexer(t_token *list);
void	add_cmd(t_token *token);
void	manage_cmd(t_token *token);
void	manage_cmd_buil(t_token *token);

void	count_pipes(t_token *list, t_data *tools);
int		count_quotes(char *str);
int		find_matching_quote(char *str, int i, int *nb_q, int q);
void	list_gathering(t_data *tools);
int		ft_error(int error);
t_env	*init_env(t_data *env_tool);
t_env	*new_env(void);
void	env_var_expand(t_data *tools);
char	*replace_env_var(char *str, t_data *tools);
int		is_env_var(char *str);
char	*find_env_var(char *str, t_env *env);
char	*is_still_env_var(char *str, t_data *tools);
void	ft_signal_handler(int signal);
void	ft_destroy_env(t_env *env_list);

void	add_args(t_token *token);
void	add_cmdbuilt_args(t_token *token);
void	add_cmd_args(t_token *token);
void	add_ls_args(t_token *token);
void	add_wc_args(t_token *token);
void	add_awk_args(t_token *token);
void	add_cat_args(t_token *token);
void	add_cd_args(t_token *token);
void	add_echo_args(t_token *token);
void	add_exp_args(t_token *token);
void	add_unset_args(t_token *token);
void	word_to_arg(t_token *token);
#endif
