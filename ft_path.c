/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemazi <aguemazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 13:54:23 by aguemazi          #+#    #+#             */
/*   Updated: 2022/07/26 11:56:50 by aguemazi         ###   ########.fr       */
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
		i ++;
	}
	free(temp);
	ft_free_doublechar(&command_split);
	if (!path_list[i])
	{
		ft_free_doublechar(&path_list);
		return (NULL);
	}
	ft_free_doublechar(&path_list);
	return (path);
}

char	*ft_get_path(char *command, char *env[], char *variable)
{
	char	**path_list;
	char	*path;
	char	**command_split;
	int		indice_path;

	command_split = ft_split(command, ' ');
	indice_path = ft_get_indice_variable(env, variable);
	if (indice_path == -1)
	{
		return (NULL);
	}
	path_list = ft_split(env[indice_path] + 5, ':');
	path = ft_search_path(command_split, path_list);
	return (path);
}

int ft_exec_path(char *str, char *env[]) // *str = chemin ou nom de commande + option + argument
{
	char	**command_split;
	char	*pathname;
	pid_t	pid;
	int		status;

	if (!str)
	{
		printf("commande vide\n");
		return (-3);
	}
	command_split = ft_split(str, ' ');
	if (!ft_strrchr(command_split[0],'/'))
	{
		pathname = ft_get_path(str, env, "PATH");
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
		execve(pathname, command_split, env);
	}
	else
	{
		wait(&status);
	}
	printf("ca marche bg\n");
	return (0);
}