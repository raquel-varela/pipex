/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvarela <rvarela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 21:57:43 by rvarela           #+#    #+#             */
/*   Updated: 2024/06/17 22:02:43 by rvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	error_heredoc(char *str, char *heredoc, int **pipes)
{
	perror(str);
	ft_free_tab((void **)pipes);
	unlink(heredoc);
	exit(EXIT_FAILURE);
}

static void	heredoc_in(char *heredoc, int **pipes)
{
	int	fd_here;

	fd_here = open(heredoc, O_RDONLY);
	if (fd_here == -1)
		error_free_pipes("Error!\n", pipes);
	dup2(fd_here, STDIN_FILENO);
	unlink(heredoc);
}

void	open_heredoc(char *limiter, int **pipes)
{
	int		fd_heredoc;
	char	*line;

	fd_heredoc = open("heredoc", O_CREAT, O_RDWR, O_APPEND, 0644);
	if (fd_heredoc == -1)
		error_heredoc("Here_doc Error!\n", "heredoc", pipes);
	while (1)
	{
		write(1, "Here_doc>", 9);
		line = get_next_line(0);
		if (!line)
			error_free_pipes("Error reading from STDIN!\n", pipes);
		if ((ft_strlen(line) - 1) == ft_strlen(limiter)
			&& ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			break ;
		}
		write(fd_heredoc, line, ft_strlen(line));
		free(line);
	}
	close(fd_heredoc);
	heredoc_in("heredoc", pipes);
}
