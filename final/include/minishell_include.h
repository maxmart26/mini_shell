/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_include.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:18:21 by matorgue          #+#    #+#             */
/*   Updated: 2024/05/05 18:35:13 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_INCLUDE_H
# define MINISHELL_INCLUDE_H

# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <signal.h>
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <termcap.h>
# include <dirent.h>
# include <fcntl.h>
# include "libft/libft.h"

# define MAX_PRINT 5000

# define LEGEND "\033[38;5;214mInd :\033[0m \
\033[0;92m[TYPE]\033[0m \033[0;91m[TOKEN]\033[0m"

# define SYNTAX_ERR "bash: syntax error near unexpected token `"
# define QUOTE_ERR ": no matching quote `"
# define DIR_ERR ": Is a directory\n"
# define CMD_ERR ": command not found\n"
# define INV_OPT ": invalid option\n"
# define ERROR_WRITE "bash: warning: here-doc not delimited by end-of-file\n"

# define GREEN "\e[1;32m"
# define RESET "\e[0m"

#endif
