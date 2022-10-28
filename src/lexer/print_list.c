/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_list.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/28 14:58:56 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/10/28 14:59:28 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_list(t_list *tokens)
{
	t_list	*current;
	int		index;
	int		color;

	color = 16;
	index = 1;
	current = tokens;
	if (tokens == NULL)
		printf("SHIT! no list to print\n");
	//printf("PRINT_list length of line = [%d]\n", length);
	printf("the list...: \n");
	while (current != NULL)
	{
		
		printf("\033[48;5;%im[%s]\n\033[m", color, current->content); //38 for shades
		//printf("node[%d] | x[%d] | y [%d] | component [%c]\n", index, current->x_pos, current->y_pos, current->component);
		current = current->next;
		index++;
		color++;
	}
}
