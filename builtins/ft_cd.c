/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemazi <aguemazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 10:51:12 by aguemazi          #+#    #+#             */
/*   Updated: 2022/12/07 11:34:43 by aguemazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_change_pwd(char ***env)
{
	int		i;
	char	*buffer;

	buffer = NULL;
	i = ft_get_indice_variable((*env), "PWD"); //ajouter securiter si introuvable
	if (i == -1)
		return ;
	buffer = getcwd(buffer, 255);
	free((*env)[i]);
	(*env)[i] = malloc(sizeof(char) * (ft_strlen(buffer) + 5));
	(*env)[i] = ft_strjoin("PWD=", buffer);
	return ;
}

void	ft_change_oldpwd(char ***env, char *oldpwd)
{
	int		i;

	i = ft_get_indice_variable((*env), "OLDPWD"); //ajouter securiter si introuvable
	if (i == -1)
		return ;
	free((*env)[i]);
	(*env)[i] = malloc(sizeof(char) * (ft_strlen(oldpwd) + 8));
	(*env)[i] = ft_strjoin("OLDPWD=", oldpwd);
	return ;
}

void	ft_cd(char **cmd, char ***env_copy)
{
	char	*buffer;

	buffer = NULL;
	buffer = getcwd(buffer, 255);
	ft_change_oldpwd(env_copy, buffer);
	chdir(cmd[1]);
	ft_change_pwd(env_copy);// valeur de retour last_return il est pas gerer la
}
