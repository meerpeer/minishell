/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: merel <merel@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/03 15:23:57 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/11/17 16:38:09 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <sys/errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include <string.h>
# include "../libft/libft.h"

//COLORS
# define R124 "\e[38;5;196m"
# define B17 "\e[38;5;202m"
# define B18 "\e[38;5;209m"
# define B19 "\e[38;5;214m"
# define B20 "\e[38;5;216m"
# define B21 "\e[38;5;21m"
# define G22 "\e[38;5;22m"
# define B23 "\e[38;5;23m"
# define Y185 "\e[38;5;185m"
# define G40 "\e[38;5;40m"
# define G41 "\e[38;5;41m"
# define G42 "\e[38;5;42m"
# define G43 "\e[38;5;43m"
# define G46 "\e[38;5;46m"
# define G47 "\e[38;5;47m"
# define G48 "\e[38;5;48m"
# define G49 "\e[38;5;49m"
# define G50 "\e[38;5;50m"
# define RESET "\e[0m"

# define SPACE ' '
# define READ_END 0
# define WRITE_END 1
# define PROMPT "minishell$ "
# define HERE_DOC_LOCATION "/tmp/here-document"

struct					s_mini;
struct					s_cmd;
struct					s_file;

typedef struct s_mini	t_mini;
typedef struct s_cmd	t_cmd;
typedef struct s_file	t_file;
typedef struct s_token	t_token;

int						g_exit_status;

/*
	--------------------------------------------------
	--------------------- ENUMS ----------------------
	--------------------------------------------------
*/
/*
	Enum to check the redirection type when opening the files
*/
typedef enum e_redirect_type{
	NO_REDIRECT,
	INPUT,
	INPUT_HEREDOC,
	OUTPUT_TRUNC,
	OUTPUT_APPEND
}			t_redirect_type;

/*
	Enum for token types!
*/
typedef enum e_token_type{
	NOTHING,
	IS_PIPE,
	IS_REDIRECT_IN,
	IS_REDIRECT_OUT_TRUNC,
	IS_REDIRECT_OUT_APPEND,
	HEREDOC,
	ERROR,
	IS_WORD
}			t_token_type;

/*
	Enum for quote_types
*/
typedef enum e_quote
{
	NO_QUOTE,
	SINGLE,
	DOUBLE,
	BACKSLASH,
	END
}			t_quote;

/*
	--------------------------------------------------
	-------------------- STRUCTS ---------------------
	--------------------------------------------------
*/

//Struct for General data for minishell
typedef struct s_mini {
	char	*cmd_input;
	t_list	*tokens;
	t_cmd	*cmds;
	char	**env;
	int		cmd_count;
	int		cmd_index;
	pid_t	last_pid;
	int		std_backup[2];
}				t_mini;

//Struct to save the tokens value and type
typedef struct s_token
{
	char			*value;
	t_token_type	type;
}				t_token;

typedef struct s_word
{
	char	*word;
	int		word_length;
	int		malloced;
}				t_word;

// Struct to check file type and name for every command
typedef struct s_file {
	char			*file_name;
	t_redirect_type	file_type;
}				t_file;

// Struct for every cmd, includes the files with their types 
typedef struct s_cmd {
	char	**cmd;
	char	*cmd_path;
	t_list	*files;
	int		cmd_index;
	int		pipe_fd[2];
	int		fd_in;
	int		fd_out;
	t_cmd	*next;
}				t_cmd;

/*
	--------------------------------------------------
	------------------- FUNCTIONS --------------------
	--------------------------------------------------
*/
//general
void	prompt_loop(t_mini *mini_data);

//error
void	error_exit(char *s1, char *s2, char *s3, int errorCode);
void	*protect_check(void *ptr);
void	print_error(char *s1, char *s2, char *s3);
void	fork_error(void);
int		exit_program(char *message, int id);

//clean
void	reset_mini_data(t_mini *mini_data);
void	free_mini_data(t_mini	*mini);
void	free_cmds(t_cmd	**cmds);
void	free_2d_array_(char **array);

//utils
t_quote	get__quote_type(char c);
t_quote	update_quote_type(t_quote quote_type, char c);
void	add_to_2d_array(char ***array, char *word);
bool	is_white_space(char c);
char	*join_3_strings(char *s1, char *s2, char *s3);
void	free_files(t_list *start_list);

//init
t_mini	*init_mini_data(void);

//environment variables
void	add_new_env_entry(t_mini *mini_data, char *key, char *value);
void	delete_env_entry(char **env, char *key);
void	set_key_value(char **env, char *key, char *value);
int		get_count_env_vars(char **env);
int		get_env_var_index(char **env, char *key);
bool	key_exists(char **env, char *key);
bool	is_variable_set(char *env_variable);
char	*get_env_var_value(char **env, char *key);
char	*get_key_from_full_env_var(char *full_str);
char	*get_value_from_full_env_var(char *full_str);

//execute
void	backup_std_in_and_out(int backup[2]);
void	restore_std_in_and_out(int backup[2]);
void	redirect(t_cmd *cmd, t_mini	*mini_data);
void	save_read_fd(t_cmd *current_command, int pipe_read_end);
void	execute_cmds(t_mini *data);
void	wait_for_cmds(int *exit_status, pid_t pid, bool set_exit);
void	execute_builtin(t_cmd *cmd_data, t_mini *mini_data);
void	open_files(int *fd_out, int *fd_in, t_list *file_list);
bool	is_builtin(char *cmd);
char	*get_cmd_path(char *cmd, char **envp);

//builtins
void	cd_builtin(t_cmd *cmd_data, t_mini *mini_data);
void	echo_builtin(t_cmd *cmd);
void	env_builtin(t_mini *mini_data, char **cmd);
void	exit_builtin(char **cmd);
void	pwd_builtin(void);
void	unset_builtin(t_cmd *cmd_data, t_mini *mini_data);
void	export_builtin(t_cmd *cmd, t_mini *data);
void	print_export(char **env);
char	**get_alphabetized_env(char **env);

//lexer
void	lexer(t_mini *mini_data);
void	chop_loop(char **strptr, int x, char *str, int *index);
void	isolate_operater(char *new_line, char *line, int *temp, int *index);
void	print_list(t_list *tokens);
void	delete_token_list(void *content);
int		count_quote(char *line, char c);
int		found_operator(char *line, int index);
int		count_operator(char *input);
int		check_token_type(char *content);
int		word_len(char *str, int tracker);
int		word_count(char *str);
int		find_char(char c);
char	*prep_line(char *line, int operator_count);
char	**split(char *str);
t_quote	get_quote_type(char c);
t_token	*new_token_node(char *content);

//parser
bool	try_parsing(t_mini *mini_data);
bool	try_parse_word(char *word, t_cmd *cmd, t_mini *mini_data);
bool	try_parse_redirect(t_list **tokens, t_cmd *cmd);
void	print_cmds(t_mini *mini_data);
void	add_char_to_word_copy(char c, t_word *word_copy);
void	expand_env(char *word, int *i, t_word *word_copy, t_mini *mini_data);
void	loop_quote(char *word, int *i, t_word *word_copy, t_mini *mini_data);
void	create_heredoc(char *delimit);

//signals
void	handle_signals(void);
void	default_signals(int id);
void	clear_prompt(int num);

#endif
