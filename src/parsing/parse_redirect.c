/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_redirect.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: merel <merel@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/31 10:57:17 by merel         #+#    #+#                 */
/*   Updated: 2022/11/07 08:40:57 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	add_to_correct_list(t_file *file, t_cmd *cmd)
{
	if (file->file_type == INPUT)
	{
		ft_lstadd_back(&cmd->in_files, ft_lstnew((void *)file));
		return (true);
	}
	else if (file->file_type == OUTPUT_APPEND
		|| file->file_type == OUTPUT_TRUNC)
	{
		ft_lstadd_back(&cmd->out_files, ft_lstnew((void *)file));
		return (true);
	}
	return (false);
}

t_file	*create_file_struct(t_token *file_token, t_token *redirect_token)
{
	t_file	*file;

	file = protect_check(ft_calloc(1, sizeof(t_file)));
	file->file_name = file_token->value;
	if (redirect_token->type == IS_REDIRECT_IN)
		file->file_type = INPUT;
	if (redirect_token->type == IS_REDIRECT_OUT_TRUNC)
		file->file_type = OUTPUT_TRUNC;
	if (redirect_token->type == IS_REDIRECT_OUT_APPEND)
		file->file_type = OUTPUT_APPEND;
	return (file);
}

bool	try_parse_redirect(t_list **tokens, t_cmd *cmd)
{
	t_token	*redirect_token;
	t_token	*file_token;
	t_file	*file;

	redirect_token = (*tokens)->content;
	*tokens = (*tokens)->next;
	if (!*tokens)
		return (printf("syntax error near unexpected token `newline'\n"),
			false);
	file_token = (*tokens)->content;
	if (file_token->type != IS_WORD)
		return (printf("syntax error near unexpected token `%s'\n",
				redirect_token->value), false);
	file = create_file_struct(file_token, redirect_token);
	if (add_to_correct_list(file, cmd))
		return (true);
	free (file->file_name);
	free (file);
	return (false);
}
