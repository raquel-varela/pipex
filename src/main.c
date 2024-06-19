/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvarela <rvarela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 12:23:50 by rvarela           #+#    #+#             */
/*   Updated: 2024/06/18 22:33:58 by rvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	child_process(char **av, char **envp, int *pipes, int i)
{
	int	ac;
	int	cmds_nbr;

	ac = 0;
	while (av[ac])
		ac++;
	cmds_nbr = count_cmds(ac, av);
	if (i == 0)
		open_infile(av[1]);
	else
	{
		close(pipes[1]);
		dup2(pipes[0], STDIN_FILENO);
		close(pipes[0]);
	}
	if (i == cmds_nbr - 1)
		open_outfile(av[ac - 1]);
	else
	{
		close(pipes[0]);
		dup2(pipes[1], STDOUT_FILENO);
		close(pipes[1]);
	}
	cmd_exec(av[i + 2], envp);
}

static void	pipex(int cmds_nbr, char **av, char **envp)
{
	int	pipes[2];
	int	pid;
	int	i;

	if (pipe(pipes) == -1)
		error_msg("Error creating pieps!\n");
	i = 0;
	while (i < cmds_nbr)
	{
		pid = fork();
		if (pid == -1)
			error_msg("Error creating child process!\n");
		if (pid == 0)
			child_process(av, envp, pipes, i);
		i++;
	}
	close(pipes[0]);
	close(pipes[1]);
	while (i--)
		waitpid(-1, NULL, 0);
}

int	main(int ac, char **av, char **envp)
{
	int	cmds_nbr;

	if (ac != 5)
	{
		error_msg("Input should be: INFILE cmd1 cmd2 OUTFILE!\n");
		return (1);
	}
	cmds_nbr = count_cmds(ac, av);
	pipex(cmds_nbr, av, envp);
	return (0);
}
