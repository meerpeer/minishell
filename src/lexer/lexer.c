/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 07:48:40 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/10/28 11:33:24 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	**lexer_input(char *input)
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
	return (0);
}

void	lexer(t_mini *mini_data)
{
	int		index;
	char	*result;
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
	lexer_input(result);
}

