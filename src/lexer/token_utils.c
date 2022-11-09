/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/02 18:12:33 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/11/09 15:22:11 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int 	check_token_type(char *content)
{
	t_token_type	type;
	int				index;

	index = 0;
	type = NOTHING;
	if (content[index] == '|')
		type = IS_PIPE;
	else if (content[index] == '<' && content[index + 1] != '<')
		type = IS_REDIRECT_IN;
	else if (content[index] == '>' && content[index + 1] != '>')
		type = IS_REDIRECT_OUT_TRUNC;
	else if (content[index] == '>' && content[index + 1] == '>')
		type = IS_REDIRECT_OUT_APPEND;
	else if (content[index] == '<' && content[index + 1] == '<')
		type = HEREDOC;
	else
		type = IS_WORD;
	return (type);
}

t_token	*new_token_node(char *content)
{
	t_token	*new_input;

	new_input = protect_check((t_token*)malloc(sizeof(t_token)));
	new_input->value = protect_check(ft_strdup(content));
	new_input->type = check_token_type(content);
	return (new_input);
}

void	delete_token_list(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	free(token->value);
	free(content);
	content = NULL;
}
