/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemazi <aguemazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 13:54:23 by aguemazi          #+#    #+#             */
/*   Updated: 2022/12/16 17:48:10 by aguemazi         ###   ########.fr       */
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

int	ft_exec_path(char **command_split, char **env[])
{
	char	*pathname;
	pid_t	pid;

	if (!command_split)
	{
		ft_putstr_fd("commande vide\n",2);
		return (-3);
	}
	if (!ft_strrchr(command_split[0],'/'))
	{
		pathname = ft_get_path(command_split, *env, "PATH");
		if (!pathname)
		{
			ft_putstr_fd("Minishell: ",2);
			ft_putstr_fd(command_split[0],2);
			ft_putstr_fd(" : No such file or directory",2);
			ft_putstr_fd("\n",2);
			LAST_RETURN = 127;
			return (-1);
		}
	}
	else
	{
		pathname = ft_create_str_copy(command_split[0], 0);
	}
	if ( pathname == NULL || access(pathname, X_OK) == -1)
	{
		ft_putstr_fd("Minishell: command not found: ",2);
		ft_putstr_fd(command_split[0],2);
		ft_putstr_fd("\n",2);
		LAST_RETURN = 127;
		free(pathname);
		return (-2); // faudra tous free
	}
	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Minishell: ft_exec_path: crash fork ",2);
		ft_putstr_fd("\n",2);
		free(pathname);
		LAST_RETURN = 11;
		return (-3); // faudra tous free
	}
	else if (pid == 0)
	{
		usleep(10);
		LAST_RETURN = execve(pathname, command_split, *env);
	}
	wait(0);
	waitpid(pid, 0, 0);
	free(pathname);
	return (0);
}
