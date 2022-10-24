/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/03 15:25:40 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/10/24 08:09:30 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>

t_file	*create_placeholder_file_list(char *first, char *second, bool are_infiles)
{
	t_file	*first_file;
	t_file	*second_file;

	first_file = ft_calloc(2, sizeof(t_list *) + 1);
	second_file = ft_calloc(2, sizeof(t_list *) + 1);

	first_file->file_name = ft_strdup(first);
	if (are_infiles)
		first_file->file_type = INPUT;
	else
		first_file->file_type = OUTPUT_TRUNC;
	first_file->next = second_file;

	second_file->file_name = ft_strdup(second);
	if (are_infiles)
		second_file->file_type = INPUT;
	else
		second_file->file_type = OUTPUT_TRUNC;
	second_file->next = NULL;
	
	return (first_file);
}

t_cmd	*create_placeholder_cmd(char *cmd, char *options, t_cmd *next, t_file *in_files, t_file *out_files, int index)
{
	t_cmd	*new_cmd = ft_calloc(1, sizeof(t_cmd));
	new_cmd->cmd = ft_calloc(3, sizeof(char *));
	new_cmd->cmd[0] = ft_strdup(cmd);
	
	new_cmd->cmd[1] = NULL;
	if (options)
		new_cmd->cmd[1] = ft_strdup(options);
	new_cmd->cmd_index = index;
	new_cmd->next = NULL;
	new_cmd->cmd_path = NULL;
	new_cmd->in_files = NULL;
	new_cmd->out_files = NULL;
	if (in_files)
		new_cmd->in_files = in_files;
	if (out_files)
		new_cmd->out_files = out_files;
	if (next)
		new_cmd->next = next;
	
	return(new_cmd);
}

void	init_placeholder_data(t_mini *data)
{
	t_file	*in_files1 = NULL; //create_placeholder_file_list("Makefile", ".gitignore", true);
	t_file	*in_files2 = NULL;
	t_file	*out_files1 = create_placeholder_file_list("outfile", "out", false);
	t_cmd	*cmd3;
	t_cmd	*cmd2;
	t_cmd	*cmd1;
	
	cmd3 = create_placeholder_cmd("ls", NULL, NULL, in_files2, NULL, 2);
	cmd2 = create_placeholder_cmd("wc", NULL, cmd3, in_files2, out_files1, 1);
	cmd1 = create_placeholder_cmd("ls", NULL, cmd2, in_files1, NULL, 0);
	data->cmds = cmd1;
	data->cmd_count = 3;
}

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

void	f()
{
	system("leaks -q minishell");
}

int	main()
{
	t_mini *mini;
	int	i = 0;

	atexit(f);

//	init_placeholder_data(&mini);
	mini = init_mini_data();
	//execute_cmds(&mini);
	set_key_value(mini->env, "TERM", "200");
	set_key_value(mini->env, "PWD", "kaasbroodje");
	set_key_value(mini->env, "SHLVL", "200");
	//printf("%s\n", get_env_var_value(mini.env, "SHLVL"));
	
	env_builtin(mini);
//	mini = init_mini_data();
printf("INIT COMPLETe\n");
//	env_builtin(mini);
	while (mini->env[i])
	{
		free(mini->env[i]);
		i++;
	}
	free(mini->env);
	free(mini);
	return (0);
}