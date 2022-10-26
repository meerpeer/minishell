/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_data.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 09:14:18 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/10/26 11:42:24 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_files(t_file *start_list)
{
	t_file	*previous;

	while (start_list)
	{
		free(start_list->file_name);
		previous = start_list;
		start_list = start_list->next;
		free (previous);
	}
}

void	free_2d_array_(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	printf("hello\n");
	while(array[i])
	{
		printf("trying to free %s", array[i]);
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_cmds(t_cmd	**cmds)
{
	t_cmd	*prev_cmd;

	while (cmds[0])
	{
		free_files(cmds[0]->out_files);
		free_2d_array_(cmds[0]->cmd);
		free_files(cmds[0]->in_files);
		prev_cmd = cmds[0];
		cmds[0] = cmds[0]->next;
		free(prev_cmd);
	}
}

void	free_mini_data(t_mini	*mini)
{
	//t_cmd	*prev_cmd;


	printf("starting to free env, env[0] = %s\n", mini->env[1]);
	
	free_2d_array_(mini->env);
	printf("freed env\n");
	free_cmds(&mini->cmds);
	// while (mini->cmds)
	// {
	// 	printf("starting to free cmds\n");
	// 	free_files(mini->cmds->out_files);
	// 	printf("freed out files\n");
	// 	free_files(mini->cmds->in_files);
	// 	printf("freed infiles\n");
	// 	free_2d_array_(mini->cmds->cmd);
	// 	printf("freed cmds\n");
	// 	prev_cmd = mini->cmds;
	// 	mini->cmds = mini->cmds->next;
	// 	free(prev_cmd);
	// }
	free(mini);
}
