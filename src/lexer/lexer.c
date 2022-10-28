/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 07:48:40 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/10/28 15:17:07 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**lexer_input(char *input)
{
	int		index;
	int		operator_count;
	char	**token;
	char	*str;

	printf(G50"in lexer_input\n"RESET);
	operator_count = count_operator(input);
	str = prep_line(input, operator_count);
	token = NULL;
	if (str == NULL)
	{
		return (NULL);
	}
	index = 0;
	printf("terug in lexer input\n str = [%s]\n", str);
	token = split(str);
	while (token[index])
	{
		printf(B23"tokens: [%s]\n"RESET, token[index]);
		index++;
	}
	return (token);
}

void	lexer(t_mini *mini_data)
{
	int		index;
	char	*result;
	char	**tokens;
	int		len;

	len = ft_strlen(mini_data->cmd_input);
	index = 0;
	
	result = mini_data->cmd_input;
	printf("len[%d]\n", len);
	while (result[index])
	{
		printf(B17"LINE: [%c]------[%d]\n"RESET, result[index], index);
		index++;
	}
	printf("[%s]\n", result);
	printf("[%c]last of line\n", result[index]);
	tokens = lexer_input(result);
	index = 0;
	while (tokens[index])
	{
		ft_lstadd_back(&mini_data->tokens, ft_lstnew(tokens[index]));
		printf(B23"tokens: [%s]\n"RESET, tokens[index]);
		index++;
	}
	//print_list(mini_data->tokens);
	free(tokens);
}

