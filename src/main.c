/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvarela- <rvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 12:23:50 by rvarela           #+#    #+#             */
/*   Updated: 2024/06/14 18:17:59 by rvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"


static void	child_process(char **av, char **envp, int **pipes, int i)
{
	int	ac;
	int	cmds_nbr;

	ac = 0;
	while (av[ac])
		ac++;
	cmds_nbr = count_cmds(ac, av);
	if (i == 0)   //se estas no primeiro comando
		open_infile(av[1]);
	else
	{
		dup2(pipes[i - 1][0], STDIN_FILENO);
	    close(pipes[i - 1][0]);
	}
	if (i == cmds_nbr - 1) //se estas no ultimo cmd
		open_outfile(av[ac - 1]);
	else
	{
		dup2(pipes[i][1], STDOUT_FILENO);
		close(pipes[i][1]);
	}
	cmd_exec(av[i + 2], envp);
}

static int	**pipes_init(int cmds_nbr)
{
	int	**pipes;
	int	i;

	pipes = (int **)malloc(sizeof(int *) * (cmds_nbr));
	if (pipes == NULL)
		return (0);
	pipes[cmds_nbr - 1] = NULL;
	i = 0;
	while (i < cmds_nbr - 1)
	{
		pipes[i] = (int *)malloc(2 * sizeof(int));
		if (pipes[i++] == NULL)
		{
			ft_free_tab((void **)pipes);
			return (0);
		}
	}
	i = 0;
	while (i < cmds_nbr - 1)
	{
		if (pipe(pipes[i++]) == -1)
			error_msg("Error creating pipe!\n");
	}
	return (pipes);
}

static void	pipex(int cmds_nbr, char **av, char **envp)
{
	int	**pipes;
	int	pid;
	int	i;

	pipes = pipes_init(cmds_nbr);
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
	while (i--)
		waitpid(-1, NULL, 0);
	ft_free_tab((void **)pipes);
}

int	main(int ac, char **av, char **envp)
{
	int	cmds_nbr;

	if (ac != 5)
		error_msg("Input should be: INFILE cmd1 cmd2 OUTFILE!\n");
	cmds_nbr = count_cmds(ac, av);
	pipex(cmds_nbr, av, envp);
	return (0);
}
