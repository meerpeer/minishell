/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/03 15:25:40 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/10/18 10:35:31 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>

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


// int	main(int argc, char **argv, char **env)
// {
// 	(void)argv;
// 	(void)env;
// 	t_mini	data;
// 	//should not run with any arguments:
// 	if (argc != 1)
// 		exit (1);
// 	init_mini_data(&data);
// 	//1.	make sure signals don't quit the program (ctrl + C 
// 	// 		should go to next prompt not quit minishell).

// 	//2.	safe the environment variables and set the shell lvl + 1

// 	//3.	other stuff??

// 	//4.	start the loop
// 	prompt_loop();
// 	return (0);
// }

int	main(int argc, char **argv)
{
	//(void)argc;
	//(void)env;
	
	t_cmd	*cmd;
	t_mini	*mini;
	int		i = 0;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	cmd->cmd = ft_calloc(sizeof( char **), argc);
	while(i < argc - 1)
	{
		cmd->cmd[i] = ft_strdup(argv[i + 1]);
		i++;
	}
	mini = NULL;
	
	echo_builtin(cmd, mini);
	return (0);
}