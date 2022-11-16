/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/28 09:12:16 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/11/16 09:56:11 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* checks if an operator is present in cmd_line. It return a 1 or 2 if this is
	the case and 0 if no operator is present
*/
int	found_operator(char *line, int index)
{
	if (line[index] != '\0' && line[index] == '|' && line[index +1] != '|')
		return (1);
	if (line[index] != '\0' && line[index] == '>' && line[index +1] != '>')
		return (1);
	else if (line[index] != '\0' && line[index] == '>' && line[index +1] == '>')
		return (2);
	if (line[index] != '\0' && line[index] == '<' && line[index +1] != '<')
		return (1);
	else if (line[index] != '\0' && line[index] == '<' && line[index +1] == '<')
		return (2);
	return (0);
}

/*counts the amount of operators present*/
int	count_operator(char *input)
{
	int		index;
	int		counter;
	char	*line;

	index = 0;
	counter = 0;
	line = input;
	while (line[index])
	{
		if (found_operator(line, index) == true)
		{
			counter++;
		}
		index++;
	}
	return (counter);
}

static int	next_in_line(int *x)
{
	return (*x = *x + 1);
}

/* this functions sets space around an operator to isolate it. This is to 
	split the input later on white space 
*/
static void	isolate_operator(char *new_line, char *str, int *index, int *x)
{	
	if (found_operator(str, *index) == 1)
	{
		new_line[*x] = ' ';
		next_in_line(x);
		new_line[*x] = str[*index];
		next_in_line(x);
		next_in_line(index);
		new_line[*x] = ' ';
		next_in_line(x);
		return ;
	}
	if (found_operator(str, *index) == 2)
	{
		new_line[*x] = ' ';
		next_in_line(x);
		new_line[*x] = str[*index];
		next_in_line(x);
		next_in_line(index);
		new_line[*x] = str[*index];
		next_in_line(x);
		next_in_line(index);
		new_line[*x] = ' ';
		next_in_line(x);
		return ;
	}
}

/*We prep the line for splitting it on white space to get separate tokens
	calloc for a new_line that will hold the line with isolated operators
	we return that new_line so it can be split on white space*/
char	*prep_line(char *str, int operator_count)
{
	char	*new_line;
	int		index;
	int		x;
	t_quote	quote_type;

	index = 0;
	x = 0;
	quote_type = NO_QUOTE;
	new_line = protect_check(ft_calloc((ft_strlen(str) + operator_count) \
		+ 1, sizeof(new_line)));
	while (str[index])
	{
		if (quote_type == NO_QUOTE)
			quote_type = get_quote_type(str[index]);
		else if (quote_type == get_quote_type(str[index]))
			quote_type = NO_QUOTE;
		if (found_operator(str, index) && quote_type == NO_QUOTE)
			isolate_operator(new_line, str, &index, &x);
		new_line[x] = str[index];
		x++;
		index++;
	}
	return (new_line);
}
