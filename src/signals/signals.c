/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/09 17:39:34 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/11/17 13:34:47 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/readline.h>
#include <termios.h>
#include <signal.h>

void	clear_prompt(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status = 1;
	}
}

void	default_signals(int id)
{
	if (id == 1)
		signal(SIGINT, SIG_IGN);
	if (id == 2)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	if (id == 3)
		signal(SIGINT, SIG_DFL);
}

void	handle_signals(void)
{
	struct termios	attributes;

	tcgetattr(STDIN_FILENO, &attributes);
	attributes.c_lflag |= ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &attributes);
	signal(SIGINT, clear_prompt);
	signal(SIGQUIT, SIG_IGN);
	if (signal(SIGINT, &clear_prompt) == SIG_ERR
		|| signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit(1);
}