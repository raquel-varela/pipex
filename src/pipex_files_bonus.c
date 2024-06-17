/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_files_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvarela- <rvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:34:49 by rvarela-          #+#    #+#             */
/*   Updated: 2024/06/17 19:12:12 by rvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	close_all_pipes_read(int **pipes)
{
	int	i;

	i = 0;
	if (!pipes)
		return ;
	while (pipes[i])
	{
		close(pipes[i][0]);
		i++;
	}
}

void	close_all_pipes_write(int **pipes)
{
	int	i;

	i = 0;
	if (!pipes)
		return ;
	while (pipes[i])
	{
		close(pipes[i][1]);
		i++;
	}
}

void	open_infile(char *infile, int **pipes)
{
	int	fd_in;

	if (!pipes)
		return ;
	if (access(infile, F_OK | R_OK) == 0)
	{
		fd_in = open(infile, O_RDONLY);
		if (fd_in == -1)
			error_free_pipes("Error opening INFILE!\n", pipes);
	}
	else
	{
		fd_in = open(infile, O_RDONLY, 0644);
		if (fd_in == -1)
			error_free_pipes("Error opening INFILE!\n", pipes);
	}
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	close_all_pipes_read(pipes);
}

void	open_outfile(char *outfile, int **pipes)
{
	int	fd_out;

	if (!pipes)
		return ;
	fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_out == -1)
		error_free_pipes("Error opening OUTFILE!\n", pipes);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	close_all_pipes_write(pipes);
}
