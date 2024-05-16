/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvarela <rvarela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 12:23:50 by rvarela           #+#    #+#             */
/*   Updated: 2024/05/12 18:38:12 by rvarela          ###   ########.fr       */
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
}




int	main(int ac, char **av)
{
	t_pipex	*data;
	int		*pid;
	int		**pipes;
	//int		i;

	//check input file (file, permissions, redirect to STDIN FD1)
	if (ac < 5)
	{
		perror("Input should be: INFILE cmd1 cmd2 cmd(x times) OUTFILE");
		exit(EXIT_FAILURE);
	}
	data->fd_in = open(av[1], O_RDONLY, 0644);
	if (data->fd_in == -1)
	{
		perror("Error opening INFILE!");
		exit(EXIT_FAILURE);
	}
	data->cmd_count = get_cmd_num(ac, **av);
	while (data->cmd_count >= 0)
	{
		pipe(pipes[data->cmd_count]);
		if (pipe(pipes[data->cmd_count]) == -1)
		{
			perror("Error creating pipes!");
			exit(EXIT_FAILURE);
		}
		data->cmd_count--;
	}
}

