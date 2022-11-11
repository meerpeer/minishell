/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/09 17:39:34 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/11/09 17:59:52 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

//main function for in the prompt loop
//overrides the ctrl \ ctrl c to exit
void	handle_signals(void)
{
	struct sigaction	action;

	sigemptyset(&action.sa_mask); //do we need this?
	quit_signal_off(); // ctrl '\'
	ft_bzero(&action, sizeof(action));
	action.sa_handler = &clear_prompt; // input to a blank line
	sigaction(SIGINT, &action, NULL); //ctrl -c
}