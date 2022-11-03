/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merel <merel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 10:57:17 by merel             #+#    #+#             */
/*   Updated: 2022/11/03 12:29:24 by merel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	try_parse_redirect(t_list **tokens, t_cmd *cmd)
{
	t_token	*redirect_token;
	t_token	*file_token;
	t_file	*file;

	redirect_token = (*tokens)->content;
	*tokens = (*tokens)->next;
	if (!*tokens)
		return(printf("syntax error near unexpected token `newline'\n"),
			false);
	file_token = (*tokens)->content;
	if (file_token->type != IS_WORD)
		return(printf("syntax error near unexpected token `%s'", 
				file_token->value), false);
	file = protect_check(ft_calloc(1, sizeof(t_file)));
	file->file_name = file_token->value;
	file->file_type = file_token->type;
	if (redirect_token->type == IS_REDIRECT_IN)
		ft_lstadd_back(cmd->in_files, file);
	else if (redirect_token->type == IS_REDIRECT_OUT_APPEND
			|| redirect_token->type == IS_REDIRECT_OUT_APPEND)
		ft_lstadd_back(cmd->out_files, file);
	else
	{
		free (file->file_name);
		free (file);
		return (false);
	}
	
	return (true);
}
