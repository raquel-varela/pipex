/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvarela <rvarela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:19:49 by rvarela-          #+#    #+#             */
/*   Updated: 2024/06/19 23:03:56 by rvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static void	child_files_closes(char **av, int **pipes, int i, int ac)
{
	int	cmds_nbr;

	cmds_nbr = count_cmds(ac, av);
	if (!pipes)
		return ;
	if (i == 0)
	{
		if (strncmp(av[1], "here_doc", 8) != 0)
			open_infile(av[1], pipes);
		else
			open_heredoc(av[2], pipes);
	}
	else
	{
		dup2(pipes[i - 1][0], STDIN_FILENO);
		close_all_pipes_read(pipes);
	}
	if (i == cmds_nbr - 1)
		open_outfile(av[ac - 1], pipes);
	else
	{
		dup2(pipes[i][1], STDOUT_FILENO);
		close_all_pipes_write(pipes);
	}
}

static void	child_process(char **av, char **envp, int **pipes, int i)
{
	int	ac;

	ac = 0;
	while (av[ac])
		ac++;
	if (!pipes)
		return ;
	child_files_closes(av, pipes, i, ac);
	if (strncmp(av[1], "here_doc", 9) == 0)
		cmd_exec(av[i + 3], envp, pipes);
	else
		cmd_exec(av[i + 2], envp, pipes);
}

static int	**pipes_init(int cmds_nbr)
{
	int	**pipes;
	int	i;

	pipes = (int **)malloc(sizeof(int *) * (cmds_nbr));
	if (!pipes)
		return (0);
	pipes[cmds_nbr - 1] = NULL;
	i = 0;
	while (i < cmds_nbr - 1)
	{
		pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (pipes[i] == NULL)
		{
			ft_free_tab((void **)pipes);
			return (0);
		}
		if (pipe(pipes[i]) == -1)
			error_msg("Error creating pipe!\n");
		i++;
	}
	return (pipes);
}

static void	pipex(int cmds_nbr, char **av, char **envp)
{
	int	**pipes;
	int	pid;
	int	i;

	pipes = pipes_init(cmds_nbr);
	if (!pipes)
		return ;
	i = 0;
	while (i < cmds_nbr)
	{
		pid = fork();
		if (pid == -1)
			error_free_pipes("Error creating child process!\n", pipes);
		if (pid == 0)
			child_process(av, envp, pipes, i);
		i++;
	}
	close_all_pipes_read(pipes);
	close_all_pipes_write(pipes);
	while (i--)
		waitpid(-1, NULL, 0);
	ft_free_tab((void **)pipes);
}

int	main(int ac, char **av, char **envp)
{
	int	cmds_nbr;

	if (ac < 5)
		error_msg("Input should be: INFILE cmd1 cmd2 cmdx OUTFILE\n\
				OR\nhere_doc LIMITER cmd1 cmd2 cmdx OUTFILE\n");
	cmds_nbr = count_cmds(ac, av);
	pipex(cmds_nbr, av, envp);
	return (0);
}
