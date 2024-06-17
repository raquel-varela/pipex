/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvarela- <rvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:19:12 by rvarela-          #+#    #+#             */
/*   Updated: 2024/06/17 19:12:32 by rvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	error_msg(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	error_free_pipes(char *str, int **pipes)
{
	if (!pipes)
		return ;
	perror(str);
	ft_free_tab((void **)pipes);
	exit(EXIT_FAILURE);
}

void	cmd_exec(char *av, char **envp, int **pipes)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(av, ' ');
	path = get_path(cmd[0], envp);
	if (!pipes)
		return ;
	if (!path)
	{
		ft_free_tab((void **)cmd);
		error_free_pipes("Error getting command path!\n", pipes);
	}
	if (execve(path, cmd, envp) == -1)
		error_free_pipes("Error executing command!\n", pipes);
}

char	*get_path(char *cmd, char **envp)
{
	char	**paths;
	char	*tmp;
	char	*path;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(paths[i]);
		free(tmp);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	free(paths);
	return (0);
}

int	count_cmds(int ac, char **av)
{
	int	cmds;

	if (strncmp(av[1], "here_doc", 8) == 0)
		cmds = ac - 4;
	else
		cmds = ac - 3;
	return (cmds);
}
