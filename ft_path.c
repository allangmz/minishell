/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkempf-e <tkempf-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 13:54:23 by aguemazi          #+#    #+#             */
/*   Updated: 2022/12/13 15:43:57 by tkempf-e         ###   ########.fr       */
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

char	*ft_get_path(char **command_split, char *env[], char *variable)
{
	char	**path_list;
	char	*path;
	int		indice_path;

	indice_path = ft_get_indice_variable(env, variable);
	if (indice_path == -1)
	{
		return (NULL);
	}
	path_list = ft_split(env[indice_path] + 5, ':');
	path = ft_search_path(command_split, path_list);
	return (path);
}

int ft_exec_path(char **command_split, char *env[])
{
	char	*pathname;
	int		status;
	// int		status;
	pid_t	pid;
	
	if (!command_split)
	{
		printf("commande vide\n");
		return (-3);
	}
	if (!ft_strrchr(command_split[0],'/'))
	{
		pathname = ft_get_path(command_split, env, "PATH");
	}
	else
	{
		pathname = command_split[0];
	}
	if (access(pathname, X_OK) == -1 || pathname == NULL)
	{
		printf("ca marche aps la commande\n");
		return (-2); // faudra tous free
	}
	pid = fork();
	if (pid == -1)
	{
		printf("ca marche aps le pid\n");
		//erreur
		return (-3); // faudra tous free
	}
	else if (pid == 0)
	{
		usleep(10);

		execve(pathname, command_split, env);

	}
	else
	{
}
	// wait(0);
	 waitpid(pid, &status, 0);
	free(pathname);
	return (0);
}
