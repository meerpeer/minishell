/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_path.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 11:20:00 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/11/16 12:59:39 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
# include <sys/stat.h>

bool	cmd_is_dir(char *cmd)
{
	struct stat cmd_stat;

	ft_memset(&cmd_stat, 0, sizeof(cmd_stat));
	stat(cmd, &cmd_stat);
	return(S_ISDIR(cmd_stat.st_mode));
}

void	check_if_path_error(char **envp, char *cmd)
{
	if (ft_strchr(cmd, '/') == NULL
		&& key_exists(envp, "PATH"))
		error_exit(cmd, ": command not found", NULL, 127);
	else if (cmd_is_dir(cmd))
		error_exit(cmd, ": is a directory", NULL, 126);
	else if (access(cmd, F_OK) != 0)
		error_exit(cmd, ": ", strerror(errno), 127);
	else if (access(cmd, F_OK | X_OK) != 0)
		error_exit(cmd, ": ", strerror(errno), 126);
}

char	*get_path_str(char **envp, char *cmd)
{
	char	*path_str;
	int		i;

	i = 0;
	path_str = NULL;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			path_str = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
			if (!path_str)
				exit (1);
			break ;
		}
		i++;
	}
	if (!path_str)
		error_exit(cmd, ": No such file or directory\n", NULL, 1);
	return (path_str);
}

void	append_strs(char **path, char *str, char *str2)
{
	char	*tmp;

	tmp = *path;
	*path = ft_strjoin(*path, str);
	if (!*path)
		exit (1);
	free (tmp);
	if (str2)
		append_strs(path, str2, NULL);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	char	*path_str;
	char	**paths;
	char	*path;
	int		i;

	if (access(cmd, F_OK | X_OK) == 0)
	{
		check_if_path_error(envp, cmd);
		return (cmd);
	}
	path_str = get_path_str(envp, cmd);
	paths = ft_split(path_str, ':');
	path = NULL;
	i = 0;
	while (paths[i])
	{
		append_strs(&paths[i], "/", cmd);
		if (access(paths[i], F_OK | X_OK) == 0)
			path = ft_strdup(paths[i]);
		i++;
	}		
	free (path_str);
	free_2d_array_(paths);
	if (path)
		return (path);
	check_if_path_error(envp, cmd);
	return (NULL);
}
