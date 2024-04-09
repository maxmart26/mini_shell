/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_proto.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:16:36 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/09 15:06:53 by lnunez-t         ###   ########.fr       */
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

void	init_data(t_token *token, t_data *data);
t_env	*init_env_i(void);
t_env	*init_env(t_data *data, int i);

// init_path.c

void	init_end(t_env *env);
void	init_env_shlvl(t_env *env, t_data *data);
char	*exec_path(t_data *data);
void	init_path(t_data *data);

// env

t_env	*new_env(void);
char	*prompt_get_sess(void);
char	*prompt_get_path(t_data *tools);

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
void	after(t_data *data, t_token *token);
void	ft_retry(t_data *data, int result, char **str);
void	ft_tmp(t_data *data, t_token *token);
void	init_minishell(t_data *tools, char **env);
t_token	*new_token_after_fd(t_token *token);

// herdoc.c

void	open_heredoc(t_data *data);

// exec.c

char	*ft_exec(t_data *data, t_token *token);
void	ft_dup2(t_data *data);
void	exec(t_data *data, t_token *token);
void	ft_exec_abs(t_token *token, t_data *data);
void	ft_dup2(t_data *data);

// utils_bonus2.c

void	ft_close_useless(t_data *data, int i, int j);

// token_init.c

char	**token_init(char *str, char *st);

// les builting

void	redirection_builting(t_token *token, t_data *data);
void	ft_echo(char **str);
int		ft_pwd(char **strs);
void	ft_env(t_data *data);
int		ft_cd(char **str, int i, t_data *data);
void	ft_export(char **strs, t_data *data, int i);
void	ft_unset(char **str, t_data *data, int i);
void	ft_exit(t_data *data, int i);
void	ft_trie_export(t_data *data);
void	ft_export_modif(char *token, t_env *env, char **str);

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
t_token	*index_first(t_token *list);
void	def_index(t_token *list);
void	ft_print_lexer(t_token *list);
void	add_cmd(t_token *token);
void	manage_cmd(t_token *token);
void	manage_cmd_buil(t_token *token);

void	count_pipes(t_token *list, t_data *tools);
int		count_quotes(char *str);
char	*delete_quotes(char *str);
void	remove_quotes(t_token *lexer_list);
int		find_matching_quote(char *str, int i, int *nb_q, int q);
void	list_gathering(t_data *tools);
int		ft_error(int error);
t_env	*new_env(void);
void	env_var_expand(t_data *tools);
char	*replace_env_var(char *str, t_data *tools);
int		is_env_var(char *str, t_data *tools);
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
void	add_grep_args(t_token *token);
//void	add_tac_args(t_token *token);

// Utils

void	show_ctrl(int sig);
int		handle_signal(void);
void	ft_signal_handler(int signal);
//void	ctrl_d(t_data *tools);
void	ctrl_d();
char	*show_prompt(t_data *tools);
void	check_new_line(t_data *tools);
void	new_line_init(t_data *tools);
int		new_line_error(t_data *tools);
int		is_space(char c);
int		is_quote(char c, char d);
int		is_spe_char(char c, char d);
int		is_char(char c, char d);
int		which_quote(char *str);
int		quote_in_str(char *str);
void	free_minishell(t_data *tools);
void	first_word(char *str);
char	*delete_sep(char *str);

// Parsing

void	parsing(t_data *tools);
int		check_syntax(t_data *tools);
int		check_error_newline(t_token *tmp);
int		check_dir(t_data *tools);
int		check_error_pipe(t_token *tmp);
int		check_spe_char(t_data *tools);
int		check_word_only(t_data *tools);

// Gestion erreur

void	free_env(char **str);
void	ft_free_tab(char **str);
void	free_env_list(t_env *env);

#endif
