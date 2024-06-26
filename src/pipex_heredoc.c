/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvarela <rvarela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 21:57:43 by rvarela           #+#    #+#             */
/*   Updated: 2024/06/19 23:08:09 by rvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	error_heredoc(char *str, char *heredoc, int **pipes)
{
	unlink(heredoc);
	perror(str);
	ft_free_tab((void **)pipes);
	exit(EXIT_FAILURE);
}

static void	heredoc_in(char *doc, int **pipes)
{
	int	fd_here;

	fd_here = open(doc, O_RDONLY, 0777);
	if (fd_here == -1)
		error_heredoc("Error reading here_doc!\n", doc, pipes);
	dup2(fd_here, STDIN_FILENO);
	close(fd_here);
	unlink(doc);
}

void	open_heredoc(char *limiter, int **pipes)
{
	int		fd_tmp;
	char	*line;

	fd_tmp = open("tmpdoc", O_RDWR | O_CREAT | O_APPEND, 0777);
	if (fd_tmp == -1)
		error_heredoc("Here_doc Error!\n", "tmpdoc", pipes);
	while (1)
	{
		write(1, "Here_doc> ", 10);
		line = get_next_line(0);
		if (!line)
			error_free_pipes("Error reading from STDIN!\n", pipes);
		if ((ft_strlen(line) - 1) == ft_strlen(limiter)
			&& ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			break ;
		}
		write(fd_tmp, line, ft_strlen(line));
		free(line);
	}
	close(fd_tmp);
	heredoc_in("tmpdoc", pipes);
}
