/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvarela- <rvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:37:52 by rvarela-          #+#    #+#             */
/*   Updated: 2024/05/17 16:58:13 by rvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <string.h>

char	**ft_split(char *str, char sep);

void	get_cmd_path(char *cmd)
{
	char	**cmd_split;
	//char	*path;

	cmd_split = ft_split(cmd, ' ');
	execlp("whereis", "whereis", "-b", cmd_split[0], NULL);
}

int main()
{
    get_cmd_path("grep ");
    return (0);
}
