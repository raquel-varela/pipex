/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvarela- <rvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:54:26 by rvarela-          #+#    #+#             */
/*   Updated: 2024/06/14 14:45:38 by rvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	error_msg(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

/*void	error_freetab(char **tab, char *str)
{
	ft_free_tab(tab);
	error_msg(str);
}*/

void	cmd_exec(char *av, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(av, ' ');
	path = get_path(cmd[0], envp);
	if (!path)
	{
		ft_free_tab(cmd);
		error_msg("Error getting command path!\n");
	}
	if (execve(path, cmd, envp) == -1)
		error_msg("Error executing command!\n");
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

