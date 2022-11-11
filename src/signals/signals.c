/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/09 17:39:34 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/11/11 13:59:37 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/readline.h>
#include <termios.h>
#include <signal.h>
//signal header
void	quit_signal_off()
{
	struct sigaction action;

	ft_bzero(&action, sizeof(action));
	action.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &action, NULL);
}

void	clear_prompt(int signum)
{
	(void)signum;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_print_newline(int signal)
{
	(void)signal;
	//printf("in handle signals[3]\n");
	rl_on_new_line();
	ft_putchar_fd('\n', STDOUT_FILENO);
}

void	set_signals_noninteractive(void)
{
	struct sigaction	act;

	//printf("in handle signals[2]\n");
	ft_bzero(&act, sizeof(act));
	act.sa_handler = &signal_print_newline;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}
//main function for in the prompt loop
//overrides the ctrl \ ctrl c to exit
void	handle_signals(void)
{
	struct sigaction	action;
	struct termios		hide;

	printf("in handle signals[1]\n");
	tcgetattr(STDIN_FILENO, &hide);
	hide.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &hide);
	sigemptyset(&action.sa_mask); //do we need this?
	quit_signal_off(); // ctrl '\'
	ft_bzero(&action, sizeof(action));
	action.sa_handler = &clear_prompt; // input to a blank line
	sigaction(SIGINT, &action, NULL); //ctrl -c
}
