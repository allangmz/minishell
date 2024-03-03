/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkempf-e <tkempf-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 19:57:00 by tkempf-e          #+#    #+#             */
/*   Updated: 2022/12/17 20:01:02 by tkempf-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_search_path(char **command_split, char **path_list)
{
	int		i;
	char	*temp;
	char	*path;

	i = 0;
	temp = ft_strjoin("/", command_split[0]);
	path = ft_strjoin(path_list[0], temp);
	while (path_list[i] && access(path, X_OK) == -1)
	{
		free(path);
		free(temp);
		temp = ft_strjoin("/", command_split[0]);
		path = ft_strjoin(path_list[i], temp);
		i++;
	}
	free(temp);
	if (!path_list[i])
	{
		ft_free_doublechar(&path_list);
		return (NULL);
	}
	ft_free_doublechar(&path_list);
	return (path);
}
