/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_data.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 09:14:18 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/10/24 09:15:35 by mevan-de      ########   odam.nl         */
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
	while(array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_mini_data(t_mini	*mini)
{
	t_cmd	*prev_cmd;

	free_2d_array_(mini->env);
	while (mini->cmds)
	{
		free_files(mini->cmds->out_files);
		free_2d_array_(mini->cmds->cmd);
		free_files(mini->cmds->in_files);
		prev_cmd = mini->cmds;
		mini->cmds = mini->cmds->next;
		free(prev_cmd);
	}
	free(mini);
}
