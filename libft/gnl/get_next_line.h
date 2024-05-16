/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvarela- <rvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 09:32:10 by rvarela-          #+#    #+#             */
/*   Updated: 2024/04/12 14:19:55 by rvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

//functions
char		*get_next_line(int fd);
size_t		strlen_gnl(const char *str);
char		*ft_strjoin_gnl(char *s1, char *s2);
char		*ft_strchr_gnl(char *str, char c);

#endif