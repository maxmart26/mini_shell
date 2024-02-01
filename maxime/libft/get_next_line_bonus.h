/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 09:54:12 by matorgue          #+#    #+#             */
/*   Updated: 2024/01/10 14:54:44 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

char	*get_next_line(int fd);
char	*ft_new(char *ptr);
char	*ft_static(char *ptr);
char	*ft_strjoin(char const *s1, char const *buffer);
char	*ft_strnchr(char *const str, char const c, size_t const n);
size_t	ft_strlen(char const *str);
char	*ft_strjoin_suite(char *stockage, char *buffer, char *str);
char	*ft_cut(char *stockage);

#endif
