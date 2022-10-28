/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/28 09:12:16 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/10/28 09:56:58 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	printf("counter operator[%d]\n", counter);
	return (counter);
}

static int	next_in_line(int *x)
{
	return (*x = *x + 1);
}
static void	isolate_operator(char *new_line, char *str, int *index, int *x)
{	
	printf(G47"bij binnenkomst: line[%s]\n"RESET, new_line);
	if (found_operator(str, *index) == 1)
	{
		new_line[*x] = ' ';
		next_in_line(x);
		new_line[*x] = str[*index];
		printf("x[%c] i[%c]\n",new_line[*x], str[*index]);
		next_in_line(x);
		next_in_line(index);
		new_line[*x] = ' ';
		next_in_line(x);
		printf("next - x[%c] i[%c]\n",new_line[*x], str[*index]);
		printf("0line[%s]\n", new_line);
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
		printf("1line[%s]\n", new_line);
		return ;
	}
}

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
			printf(R124"in if statement found operater\n"RESET);
		}
		new_line[x] = str[index];
		x++;
		index++;
	}
	printf("line after going tru whitespace [%s]\n", new_line);
	return (new_line);
}