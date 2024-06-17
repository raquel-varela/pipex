/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvarela- <rvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:26:22 by rvarela-          #+#    #+#             */
/*   Updated: 2024/06/17 17:56:34 by rvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

void	open_outfile(char *outfile)
{
	int	fd_out;

	fd_out = open (outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_out == -1)
		error_msg("Error opening OUTFILE!\n");
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
}
