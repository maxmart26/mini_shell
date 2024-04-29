/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:13:47 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/04/29 16:06:11 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

void	sig_handler_sa(int signal, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (!g_status)
		ft_putstr_fd("\n", STDERR_FILENO);
	if (g_status == 2 || (g_status == 5 && signal == SIGINT))
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		if (g_status == 2)
			printf("\n");
		return ;
	}
	if (g_status == 5 && signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		printf("\n");
	}
	rl_on_new_line();
	rl_replace_line("", 0);
	printf("\n");
	rl_redisplay();
}

int	handle_signal(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = (void *)sig_handler_sa;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
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

void	ctrl_d(t_data *tools)
{
	printf("exit\n");
	free_minishell_ctrld(tools);
	exit (1);
}
