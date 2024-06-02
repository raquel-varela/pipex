/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvarela <rvarela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 12:23:50 by rvarela           #+#    #+#             */
/*   Updated: 2024/05/23 17:35:08 by rvarela          ###   ########.fr       */
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

static void	open_infile(char *infile)
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

static void	child_process(char **av, char **envp, int *pipes)
{
	close(pipes[0]);
	dup2(pipes[1], STDOUT_FILENO);
	close(pipes[1]);
	cmd_exec(av[2], envp);
}

static void	parent_process(char **av, char **envp, int *pipes)
{
	int	fd_out;

	fd_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_out == -1)
		error_msg("Error opening OUTFILE!\n");
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	close(pipes[1]);
	dup2(pipes[0], STDIN_FILENO);
	close(pipes[0]);
	cmd_exec(av[3], envp);
}

	//check input file (file, permissions, redirect to STDIN FD1)
	//open INFILE and check
int	main(int ac, char **av, char **envp)
{
	int	pipes[2];
	int	pid;

	if (ac != 5)
		error_msg("Input should be: INFILE cmd1 cmd2 OUTFILE!\n");
	open_infile(av[1]);
	if (pipe(pipes) == -1)
		error_msg("Error creating pipe!\n");
	pid = fork();
	if (pid == -1)
		error_msg("Error creating child process!\n");
	if (pid == 0)
		child_process(av, envp, pipes);
	waitpid(pid, NULL, 0);
	parent_process(av, envp, pipes);
	return (0);
}
