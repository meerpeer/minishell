/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/28 09:12:16 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/11/02 18:39:27 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* checks if an operator is present in cmd_line. It return a 1 or 2 if this is
	the case and 0 if no operator is present
*/

int	found_operator(char *line, int index)
{
	if (line[index] != '\0' && line[index] == '|' && line[index +1] != '|')
	{
		printf("found operator [%c]\n", line[index]);
		return (1);
	}	
	if (line[index] != '\0' && line[index] == '>' && line[index +1] != '>')
	{
		printf("found operator [%c]\n", line[index]);
		return (1);
	}	
	else if (line[index] != '\0' && line[index] == '>' && line[index +1] == '>')
	{
		printf("found operator [%c]\n", line[index]);
		return (2);
	}	
	if (line[index] != '\0' && line[index] == '<' && line[index +1] != '<')
	{
		printf("found operator [%c]\n", line[index]);
		return (1);
	}	
	else if (line[index] != '\0' && line[index] == '<' && line[index +1] == '<')
	{
		printf("found operator [%c]\n", line[index]);
		return (2);
	}	
	return (0);
}

/*counts the amout of operators present*/

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
	//printf("counter operator[%d]\n", counter);
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
	//printf(G47"bij binnenkomst: line[%s]\n"RESET, new_line);
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

/*We prep the line for splitting it on white space to get seperate tokens
	calloc for a new_line that will hold the line with isolated operators
	we return that new_line so it can be split on white space*/
char	*prep_line(char *str, int operator_count)
{
	char	*new_line;
	int		index;
	int		x;

	index = 0;
	x = 0;
	new_line = ft_calloc((ft_strlen(str) + operator_count) + 1, sizeof(new_line));
	if (!new_line)
		return (NULL);
	while (str[index])
	{
		if (found_operator(str, index))
		{
			isolate_operator(new_line, str, &index, &x);
			//printf(R124"in if statement found operater\n"RESET);
		}
		new_line[x] = str[index];
		x++;
		index++;
	}
	//printf("line after going tru whitespace [%s]\n", new_line);
	return (new_line);
}