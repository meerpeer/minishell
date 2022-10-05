/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/03 15:25:40 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/10/05 09:30:35 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

# include <readline/readline.h>
int	prompt_loop()
{
	char	*line = NULL;
	//char	**args;
	int		status = 1;

	while (status)
	{
		// I guess this reads from the prompt:
		line = readline("minishell$ ");
		add_history(line);
		free(line);
	}
	return (status);
}

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	(void)env;
	//should not run with any arguments:
	if (argc != 1)
		exit (1);
	//1.	make sure signals don't quit the program (ctrl + C 
	// 		should go to next prompt not quit minishell).

	//2.	safe the environment variables and set the shell lvl + 1

	//3.	other stuff??

	//4.	start the loop
	prompt_loop();
	return (0);
}
