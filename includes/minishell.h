/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/03 15:23:57 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/10/16 10:37:29 by mevan-de      ########   odam.nl         */
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

# define READ_END = 0;
# define WRITE_END = 1;
# define PROMPT = "minishell$ ";

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
	char	**envp; // I'll need these to get the path for the commands
	char	builtin[7][7];
	int		cmd_count; // to see how many pipes there are
	int		cmd_index; // to see on which command we're currently at (last and first are important for pipe reasons?)
	int		exit_status; //will take the exit status off the last child process :)
	
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
	int		fd_int;
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

//init
void	init_mini_data(t_mini *data);

//execute
int		open_infiles(t_file *in_files);
int		open_outfiles(t_cmd *cmd);
void	redirect_in(t_cmd *cmd, t_mini *data);
void	close_unused_fds();
bool	is_builtin(char *cmd);

//builtins
void	cd_builtin(t_mini *data);
void	echo_builtin(t_mini *data);
void	env_builtin(t_mini *data);
void	exit_builtin(t_mini *data);
void	export_builtin(t_mini *data);
void	pwd_builtin(t_mini *data);
void	unset_builtin(t_mini *data);




#endif
