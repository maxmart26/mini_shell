/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:13:47 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/03/19 17:16:09 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

void	sig_handler_sa(int signal, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		printf("\n");
		//new_line();
		rl_redisplay();
	}
	else if (signal == SIGQUIT)
	{
		printf("\033[2D  ");
		printf("\033[2D");
		return ;
	}
}

int	handle_signal(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = (void *)sig_handler_sa;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	return (0);
}

void	show_ctrl(int sig)
{
	struct termios	new;

	tcgetattr(0, &new);
	if (sig)
		new.c_lflag |= ECHOCTL;
	else
		new.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &new);
}

void	ctrl_d(void)
{
	/*int		lvl;

	lvl = check_lvl();
	if (lvl > 1)
		return (level_down());
	free_minishell();*/
	printf("exit\n");
	exit(0);
}
