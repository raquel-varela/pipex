/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvarela- <rvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 12:23:50 by rvarela           #+#    #+#             */
/*   Updated: 2024/05/17 17:47:46 by rvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*BONUS int	get_cmd_num(int ac, char **av)
{
	int	i;

	i = 0;
	while (av)
		i++;
	return (i - 3);
}*/

/*char	get_cmd_path(char *cmd)
{
	char	**cmd_split;
	char	*path;

	cmd_split = ft_split(cmd, ' ');
	path = whereis(cmd_split[0]);
	return (path);
}*/

void	open_infile(char *infile)
{
	int	fd_in;

	if (access(infile, F_OK | R_OK) == 0)
	{
		fd_in = open(infile, O_RDONLY);
		if (fd_in == -1)
			error_msg("Error opening INFILE!\n!");
	}
	else
	{
		fd_in = open(infile, O_RDONLY, 0644);
		if (fd_in == -1)
			error_msg("Error opening INFILE!\n!");
	}
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
}

//void	sendto_outfile(char *outfile, char *cmd2, char **path, char **env)

//pipex function
void	pipex(char **av, char **path, char **env)
{
	while (i <= data->cmd_count)
	{
		pipe(pipes[i]);
		if (pipe(pipes[i]) == -1)
			error_msg("Error creating pipes!\n!");
		i++;
	}
	i = 0;
	while (i < data->cmd_count)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			error_msg("Error creating child!\n!");
		if (pids[i] == 0)
		{
			j = 0;
			while (j <= data->cmd_count)
			{
				if (i != j)
					close(pipes[j][0]);
				if (i + 1 != j)
					close(pipes[j][1]);
			}

			//Child code
			
		}
		//Parent (main) code




		close(pipes[0][1]);
		close(pipes[data->cmd_count][0]);
		i = 0;
		while (i++ < data->cmd_count)
			wait(NULL);
	}
}


int	main(int ac, char **av, char **env)
{
	/*t_pipex	*data;
	int		*pids;
	int		**pipes;
	int		i;
	int		j;*/
	char	**paths;

	//check input file (file, permissions, redirect to STDIN FD1)
	if (ac != 5)
		error_msg("Input should be: INFILE cmd1 cmd2 OUTFILE!\n");
	
	//open INFILE and check
	open_infile(av[1]);
	
	//get_path
	paths = get_paths(env);
	if (!paths)
		error_msg("Error getting paths!\n");
	
	//pipex
	pipex(av, paths, env);
}

