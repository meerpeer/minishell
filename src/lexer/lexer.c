/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 07:48:40 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/11/09 13:40:47 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* this fuction preps the cmd_input by counting operators and
	isololates them. The cmd_ipit is split on white spaces and returns
	seperate tokens. We create a list of the tokens 
	and sign them a type 
*/
void	lexer(t_mini *mini_data)
{
	int		index;
	int		operator_count;
	char	**chunk;
	t_token *token_value;
	char	*str;

	printf(G50"in lexer_input\n"RESET);
	operator_count = count_operator(mini_data->cmd_input);
	str = prep_line(mini_data->cmd_input, operator_count);
	chunk = NULL;
	token_value = NULL;
	if (str == NULL)
		return ;
	//printf("terug in lexer input\n str = [%s]\n", str);
	chunk = split(str);
	if (str)
		free(str);
	//system("leaks minishell");
	index = 0;
	while (chunk[index])
	{
		token_value = new_token_node(chunk[index]);
		//printf("[%s]token value\n", token_value->value);
		//printf("token type = [%d]\n", token_value->type);
		ft_lstadd_back(&mini_data->tokens, protect_check(ft_lstnew((void *)token_value)));
		index++;
	}
	free_2d_array_(chunk);
	printf("freeing worked!\n");
	//print_list(mini_data->tokens);
	return ;
}

