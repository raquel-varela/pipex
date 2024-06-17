/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvarela- <rvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 12:25:25 by rvarela           #+#    #+#             */
/*   Updated: 2024/06/17 19:08:29 by rvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <stdbool.h>

/*typedef struct s_pipex
{
	int		fd_in;
	int		fd_out;
	int		cmd_count;
	int		pipe_fd;
	char	**args_path;
	char	***arsg_cmd
}			t_pipex;*/

//utils
void	error_msg(char *str);
void	error_free_pipes(char *str, int **pipes);
void	cmd_exec(char *av, char **envp, int **pipes);
char	*get_path(char *cmd, char **envp);
int		count_cmds(int ac, char **av);
void	open_infile(char *infile, int **pipes);
void	open_outfile(char *outfile, int **pipes);
void	close_all_pipes_read(int **pipes);
void	close_all_pipes_write(int **pipes);

#endif
