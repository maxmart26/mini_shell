/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_include.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:18:21 by matorgue          #+#    #+#             */
/*   Updated: 2024/03/06 18:29:49 by matorgue         ###   ########.fr       */
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
# include "../utilitaire/libft/libft.h"

# define MAX_PRINT 5000

# define LEGEND "\033[38;5;214mInd :\033[0m \
\033[0;92m[TYPE]\033[0m \033[0;91m[TOKEN]\033[0m"

# define SYNTAX_ERR "syntax error : no closing quote"

#endif
