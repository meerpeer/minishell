/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: merel <merel@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/27 13:30:21 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/11/11 13:59:18 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redirect(t_token_type type)
{
	if (type == IS_REDIRECT_IN
		|| type == IS_REDIRECT_OUT_APPEND
		|| type == IS_REDIRECT_OUT_TRUNC
		|| type == HEREDOC)
		return (true);
	return (false);
}

bool	try_fill_cmd(t_list **tokens, t_cmd *cmd, t_mini *mini_data)
{
	t_token	*current_token;
	bool	success;

	success = true;
	current_token = (*tokens)->content;
	while (current_token->type != IS_PIPE)
	{
		if (is_redirect(current_token->type))
			success = try_parse_redirect(tokens, cmd);
		else if (current_token->type == IS_WORD)
			success = try_parse_word(current_token->value, cmd, mini_data);
		if (!success)
			return (false);
		if (!(*tokens))
			break ;
		current_token = (*tokens)->content;
		*tokens = (*tokens)->next;
		if (!(*tokens))
			break ;
		current_token = (*tokens)->content;
	}
	return (true);
}

t_cmd	*create_new_cmd(t_mini *mini_data, int index)
{
	t_cmd	*cmd;
	t_cmd	*first;

	cmd = protect_check(ft_calloc(1, sizeof(t_cmd)));
	cmd->cmd_index = index;
	cmd->cmd = NULL;
	cmd->files = NULL;
	mini_data->cmd_count++;
	first = mini_data->cmds;
	if (!first)
	{
		mini_data->cmds = cmd;
		return (cmd);
	}
	while (mini_data->cmds->next)
		mini_data->cmds = mini_data->cmds->next;
	mini_data->cmds->next = cmd;
	mini_data->cmds = first;
	return (cmd);
}

bool	try_parsing(t_mini *mini_data)
{
	t_list	*tokens;
	t_token	*current_token;
	t_cmd	*cmd;
	int		i;

	i = 0;
	tokens = mini_data->tokens;
	if (!tokens)
		return (false);
	while (tokens)
	{
		cmd = create_new_cmd(mini_data, i);
		i++;
		current_token = tokens->content;
		if (current_token->type == IS_PIPE)
			return (print_error("syntax error near unexpected token `|'",
				NULL, NULL), false);
		if (tokens && !try_fill_cmd(&tokens, cmd, mini_data))
			return (false);
		if (!tokens)
			break ;
		tokens = tokens->next;
		if (!tokens)
			return(print_error("Multiline pipe not handled", NULL, NULL), false);
	}
	return (true);
}
