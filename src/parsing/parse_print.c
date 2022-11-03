/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_print.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: merel <merel@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 14:56:25 by merel         #+#    #+#                 */
/*   Updated: 2022/11/03 15:59:51 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void print_cmd_files(t_list *files)
{
	t_list	*curr_file;
	t_file	*file;

	curr_file = files;
	while (curr_file)
	{
		file = curr_file->content;
		printf("%s, ", file->file_name);
		curr_file = curr_file->next;
	}
	printf("\n");
}

static void	print_cmd_word(char **words)
{
	int	i;

	i = 0;

	while (words[i])
	{
		printf("%s, ", words[i]);
		i++;
	}
	printf("\n");
}


void	print_cmds(t_mini *mini_data)
{
	t_cmd	*cmd;

	cmd = mini_data->cmds;
	printf("printing %i cmds: \n", mini_data->cmd_count);
	while (cmd)
	{
		printf("-------------------\n");
		printf("CMD %i\n", cmd->cmd_index);
		printf(G41"cmds: \t\t"RESET);print_cmd_word(cmd->cmd);
		printf("infiles:\t");
		print_cmd_files(cmd->in_files);
		printf("outiles:\t");
		print_cmd_files(cmd->out_files);
		cmd = cmd->next;
		printf("-------------------\n");
	}
}
