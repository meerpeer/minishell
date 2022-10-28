/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/03 15:23:57 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/10/28 11:37:05 by mevan-de      ########   odam.nl         */
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

struct s_mini;
struct s_cmd;
struct s_file;

typedef struct s_mini	t_mini;
typedef struct s_cmd	t_cmd;
typedef struct s_file	t_file;
typedef struct s_token	t_token;

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
	OUTPUT_TRUNC,
	OUTPUT_APPEND
}			t_redirect_type;

/*
	Enum for token types!
*/
typedef enum e_token_type{
	IS_PIPE,
	IS_REDIRECT_IN,
	IS_REDIRECT_OUT_TRUNC,
	IS_REDIRECT_OUT_APPEND,
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
	char	**env; // I'll need these to get the path for the commands
	int		cmd_count; // to see how many pipes there are
	int		cmd_index; // to see on which command we're currently at (last and first are important for pipe reasons?)
	int		exit_status; //will take the exit status off the last child process :)
	pid_t	last_pid;
	int		std_backup[2];
}				t_mini;

//Struct to save the tokens value and type
typedef struct s_token
{
	char			*value;
	t_token_type	type;
}				t_token;


// Struct to check file type and name for every command
typedef struct s_file {
	char	*file_name;
	int		file_type;
	t_file	*next;
}				t_file;

// Struct for every cmd, includes the files with their types 
typedef struct s_cmd {
	char	**cmd;
	t_file	*in_files;
	t_file	*out_files;
	char	*cmd_path;
	int		pipe_fd[2];
	int		fd_in;
	int		fd_out;
	int		cmd_index;
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
void	error_exit(char *message, int errorCode);
void	*protect_check(void *ptr);
int		exit_program(char *message, int id);

//clean
void	free_mini_data(t_mini	*mini);
void	free_cmds(t_cmd	**cmds);

//init
t_mini	*init_mini_data(void);

//environment variables
int		get_count_env_vars(char **env);
char	*get_env_var_value(char **env, char *key);
void	add_new_env_entry(char ***env, char *key, char *value);
void	delete_env_entry(char **env, char *key);
void	set_key_value(char **env, char *key, char *value);
int		get_env_var_index(char **env, char *key);
char	*join_3_strings(char *s1, char *s2, char *s3);
bool	key_exists(char **env, char *key);
char	*get_key_from_full_env_var(char *full_str);
char	*get_value_from_full_env_var(char *full_str);
bool	is_variable_set(char *env_variable);

//execute
void	backup_std_in_and_out(int backup[2]);
void	restore_std_in_and_out(int backup[2]);
void	redirect_in(int *fd_in, t_file *in_files);
void	redirect_out(t_cmd *cmd, t_mini *mini_data);
void	save_read_fd(t_cmd *current_command, int pipe_read_end);
bool	is_builtin(char *cmd);
void	execute_cmds(t_mini *data);
char	*get_cmd_path(char *cmd, char **envp);
void	wait_for_cmds(int *exit_status, pid_t pid);
void	execute_builtin(t_cmd *cmd_data, t_mini *mini_data);

//builtins
void	cd_builtin(t_cmd *cmd_data, t_mini *mini_data);
void	echo_builtin(t_cmd *cmd, t_mini *data);
void	env_builtin(t_mini *mini_data);
void	exit_builtin(t_cmd *cmd, t_mini *data);
void	export_builtin(t_cmd *cmd, t_mini *data);
void	pwd_builtin(t_mini *mini_data);
void	unset_builtin(t_cmd *cmd_data, t_mini *mini_data);

//lexer
void	lexer(t_mini *input);
int		count_quote(char *line, char c);
int		found_operator(char *line, int index);
int		count_operator(char *input);
void	isolate_operater(char *new_line, char *line, int *temp, int *index);
char	*prep_line(char *line, int operator_count);
char	**split(char *str);
t_token	*add_new_token_back(t_token *token_node, char *command, int token_type);
t_token	*new_token_lst(char *command, int token_type);

#endif
