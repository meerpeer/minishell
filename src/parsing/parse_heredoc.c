/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_heredoc.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/07 13:10:00 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/11/17 13:39:12 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	here_doc_write(char *delimit)
{
	char	*input;
	int		delimit_len;
	int		heredoc_fd;

	heredoc_fd = open(HERE_DOC_LOCATION, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (heredoc_fd == -1)
		exit (1);
	delimit_len = ft_strlen(delimit);
	default_signals(3);
	while ("ants exist")
	{
		input = readline("> ");
		if (!input)
			exit(g_exit_status);
		if (!ft_strncmp(input, delimit, delimit_len) && !input[delimit_len])
		{
			close(heredoc_fd);
			exit (0);
		}
		write(heredoc_fd, input, ft_strlen(input));
		write(heredoc_fd, "\n", 1);
		free(input);
	}
	handle_signals();
}

void	create_heredoc(char *delimit)
{
	int	pid;
	int status;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		error_exit(strerror(errno), NULL, NULL, 1);
	if (pid == 0)
		here_doc_write(delimit);
	waitpid(pid, &status, 0);
	if (WTERMSIG(status) == SIGINT)
	{
		g_exit_status = 1;
		ft_putstr_fd("\n", STDOUT_FILENO);
		return ;
	}
}
