/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main _bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvarela- <rvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:54:17 by rvarela-          #+#    #+#             */
/*   Updated: 2024/06/07 16:48:28 by rvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	get_cmd_num(int ac, char **av)
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

static void	child_process(char *av, char **envp, int *pipes)
{
	close(pipes[0]);
	dup2(pipes[1], STDOUT_FILENO);
	close(pipes[1]);
	cmd_exec(av, envp);
}

static void	parent_process(int ac, char *av, char **envp, int *pipes)
{
	int	fd_out;

	fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_out == -1)
		error_msg("Error opening OUTFILE!\n");
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	close(pipes[1]);
	dup2(pipes[0], STDIN_FILENO);
	close(pipes[0]);
	cmd_exec(av, envp);
}

	//check input file (file, permissions, redirect to STDIN FD1)
	//open INFILE and check
int	main(int ac, char **av, char **envp)
{
	int	pipes[2];
	int	pid;
	int	i;

	i = 2;
	if (ac < 5)
		error_msg("Input should be: INFILE cmd1 cmd2 cmdx OUTFILE\n\
				OR\nhere_doc LIMITER cmd1 cmd2 cmdx OUTFILE");
	/*if (strncmp(av[1], "here_doc", 8) == 0)
	{
		exec_heredoc(av);
		i = 3;
	}
	else*/
	open_infile(av[1]);
	while (i < ac - 2)
	{
		if (pipe(pipes) == -1)
			error_msg("Error creating pipe!\n");
		pid = fork();
		if (pid == -1)
			error_msg("Error creating child process!\n");
		if (pid == 0)
			child_process(av[i], envp, pipes);
		waitpid(pid, NULL, 0);
		parent_process(ac, av[i], envp, pipes);
		i++;
	}
	return (0);
}
