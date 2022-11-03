/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merel <merel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 13:30:21 by mevan-de          #+#    #+#             */
/*   Updated: 2022/11/03 12:01:40 by merel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redirect(t_token_type type)
{
	if (type == IS_REDIRECT_IN
		|| type == IS_REDIRECT_OUT_APPEND
		|| type == IS_REDIRECT_OUT_TRUNC)
		return (true);
	return (false);
}

bool	try_fill_cmd(t_list **tokens, t_cmd *cmd, char **env)
{
	t_token	*current_token;
	bool	succes;

	succes = true;
	current_token = (*tokens)->content;
	while (current_token->type != IS_PIPE)
	{
		if (is_redirect(current_token->type))
			succes = try_parse_redirect(tokens, cmd);
		else if (current_token->type == IS_WORD)
			succes = try_parse_word(current_token->value, cmd, env);
		if (!succes)
			return (false);
		*tokens = (*tokens)->next;
		if (!*tokens)
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
			return (printf("syntax error near unexpected token `|'"), false);
		if (!try_fill_cmd(&tokens, cmd, mini_data->env))
			return (false);
		//tokens = tokens->next;
	}
	//printf("cmd->cmd[0] = %s\n", cmd->cmd[0]);
	return (true);
}
