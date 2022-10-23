/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/03 15:23:57 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/10/23 14:32:38 by mevan-de      ########   odam.nl         */
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

# define READ_END 0
# define WRITE_END 1
# define PROMPT "minishell$ "

struct s_mini;
struct s_cmd;
struct s_file;

typedef struct s_mini	t_mini;
typedef struct s_cmd	t_cmd;
typedef struct s_file	t_file;

/**
	Struct for General data for minishell
	
*/
typedef struct s_mini {
	t_cmd	*cmds;
	char	**env; // I'll need these to get the path for the commands
	int		cmd_count; // to see how many pipes there are
	int		cmd_index; // to see on which command we're currently at (last and first are important for pipe reasons?)
	int		exit_status; //will take the exit status off the last child process :)
	pid_t	last_pid;
	int		std_backup[2];
}				t_mini;

/*
	Enum to check the redirection type when opening the files
*/
typedef enum e_redirect_type{
	NONE,
	INPUT,
	OUTPUT_TRUNC,
	OUTPUT_APPEND
}			t_redirect_type;

/*
	Struct to check file type and name for every command
*/
typedef struct s_file {
	char	*file_name;
	int		file_type;
	t_file	*next;
}				t_file;

/*
	Struct for every cmd, includes the files with their types 
*/
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

typedef struct s_exec {
	t_cmd	*cmd;
	pid_t	pid;
	int		pipe_fd[2];
}				t_exec;

//error
void	error_exit(char *message, int errorCode);
void	*protect_check(void *ptr);

//init
t_mini	*init_mini_data(void);

//environment variables
int		get_count_env_vars(char **env);
char	*get_env_var_value(char **env, char *key);
void	new_env_entry(char ***env, char *key, char *value);
void	delete_env_entry(char **env, char *key);
void	set_key_value(char **env, char *key, char *value);
int		get_env_var_index(char **env, char *key);
char	*join_3_strings(char *s1, char *s2, char *s3);

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
void	unset_builtin(t_cmd *cmd, t_mini *data);

#endif
