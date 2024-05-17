/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvarela- <rvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 12:25:25 by rvarela           #+#    #+#             */
/*   Updated: 2024/05/17 17:50:18 by rvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_pipex
{
	int		fd_in;
	int		fd_out;
	int		cmd_count;
	int		pipe_fd;
	char	**args_path;
	char	***arsg_cmd
}		t_pipex;

//utils
void    error_msg(char *str);


//path
char    **get_paths(char **env);

#endif