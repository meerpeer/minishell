/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_data.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: merel <merel@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 09:14:18 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/11/09 13:26:53 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_files(t_list *start_list)
{
	t_list	*previous;
	t_file	*file;

	while (start_list)
	{
		file = start_list->content;
		if (file)
		{
			free(file->file_name);
			free(file);
		}
		previous = start_list;
		start_list = start_list->next;
		free (previous);
	}
}

void	free_2d_array_(char **array)
{
	int	i;

	i = 0;
	printf("staring to free\n");
	if (!array)
		return ;
	while(array[i])
	{
		printf("oi\n");
		free(array[i]);
		i++;
	}
	printf("trying to free chunk\n");
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

void	reset_mini_data(t_mini *mini_data)
{
	free_cmds(&mini_data->cmds);
	mini_data->cmds = NULL;
	mini_data->cmd_count = 0;
	ft_lstclear(&mini_data->tokens, delete_token_list);
	mini_data->tokens = NULL;
}

void	free_mini_data(t_mini	*mini)
{
	//t_cmd	*prev_cmd;


	printf("starting to free env, env[0] = %s\n", mini->env[1]);
	
	free_2d_array_(mini->env);
	printf("freed env\n");
	free_cmds(&mini->cmds);
	free(mini);
}
