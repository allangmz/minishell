/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemazi <aguemazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 16:55:11 by aguemazi          #+#    #+#             */
/*   Updated: 2022/10/05 17:55:23 by aguemazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../Libft/libft.h"
#include <sys/types.h>
#include "minishell.h"

void	ft_change_oldpwd();

// make a copy of src. if n = 0 copy all the src
char	*ft_create_str_copy(char *src, int n)
{
	char	*copy;
	int		i;

	if (n == 0)
		n = ft_strlen(src);
	copy = malloc(sizeof(char) * (n + 1));
	i = 0;
	while (i < n)
	{
		copy[i] = src[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	**ft_copy_env(char **env)
{
	char	**env_copy;
	int		i;
	int		j;

	i = 0;
	while (env[i])
	{
		i++;
	}
	env_copy = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		env_copy[i] = malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
		j = 0;
		while (env[i][j])
		{
			env_copy[i][j] = env[i][j];
			j++;
		}
		env_copy[i][j] = '\0';
		i++;
	}
	env_copy[i] = NULL;
	return (env_copy);
}

void	ft_change_pwd(char ***env)
{
	int		i;
	char	*buffer;

	buffer = NULL;
	i = ft_get_indice_variable((*env), "PWD");
	buffer = getcwd(buffer, 255);
	ft_change_oldpwd(env, get_variable_in_env(*env, ft_strjoin("","PWD"))); // fonctionne pas //ICI !!!!
	free((*env)[i]);
	(*env)[i] = malloc(sizeof(char) * (ft_strlen(buffer) + 5));
	(*env)[i] = ft_strjoin("PWD=", buffer);
	return ;
}

void	ft_change_oldpwd(char ***env, char *oldpwd)
{
	int		i;

	printf("%s\n",oldpwd);
	i = ft_get_indice_variable((*env), "OLDPWD");
	free((*env)[i]);
	(*env)[i] = malloc(sizeof(char) * (ft_strlen(oldpwd) + 8));
	(*env)[i] = ft_strjoin("OLDPWD=", oldpwd);
	return ;
}


void	ft_print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return ;
}

// même fichier ft_export_variable_env, ft_add_variable_env et ft_change_variable_env
void	ft_add_variable_env(char ***env, char *str)
{
	char	**new_env;
	int		i;
	int		j;

	i = 0;
	while ((*env)[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while ((*env)[i])
	{
		new_env[i] = malloc(sizeof(char) * (ft_strlen((*env)[i]) + 1));
		j = 0;
		while ((*env)[i][j])
		{
			new_env[i][j] = (*env)[i][j];
			j++;
		}
		new_env[i][j] = '\0';
		i++;
	}
	new_env[i] = ft_create_str_copy(str, 0);
	i++;
	new_env[i] = NULL;
	ft_free_doublechar(env);
	*env = new_env;
	return ;
}

void	ft_change_variable_env(char ***env, int indice_var, char *str)
{
	char	*temp;
	int		i;

	temp = malloc(sizeof(char) * ft_strlen(str) + 1);
	i = 0;
	while (str[i])
	{
		temp[i] = str[i];
		i++;
	}
	temp[i] = '\0';
	free((*env)[indice_var]);
	(*env)[indice_var] = temp;
	return ;
}

char	*ft_variable_extract(char *str)
{
	char	*variable;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		i++;
	}
	if (!str[i])
		return (NULL);
	variable = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (str[i] != '=')
	{
		variable[i] = str[i];
		i++;
	}
	variable[i] = '\0';
	return (variable);
}

void	ft_export_variable_env(char ***env, char *str)
{
	char	*variable;
	int		indice_variable;

	variable = ft_variable_extract(str);
	// ft_verif_variable(variable); // verifier si contient que alphanum ou _
	indice_variable = ft_get_indice_variable(*env, variable);
	if (indice_variable == -1)
	{
		ft_add_variable_env(env, str);
	}
	else
	{
		ft_change_variable_env(env, indice_variable, str);
	}
	free(variable);
	return ;
}

char	**ft_copy_env_less_var(char ***env, int indice_variable)
{
	char	**env_copy;
	int		i;
	int		j;

	i = 0;
	while ((*env)[i])
		i++;
	env_copy = malloc(sizeof(char *) * (i));
	i = 0;
	while ((*env)[i])
	{
		if (i == indice_variable)
			i++;
		env_copy[i] = malloc(sizeof(char) * (ft_strlen((*env)[i]) + 1));
		j = 0;
		while ((*env)[i][j])
		{
			env_copy[i][j] = (*env)[i][j];
			j++;
		}
		env_copy[i][j] = '\0';
		i++;
	}
	env_copy[i] = NULL;
	return (env_copy);
}

void	ft_unset_variable_env(char ***env, char *variable)
{
	int		indice_variable;
	char	**new_env;

	printf("variable    %s\n", variable);
	indice_variable = ft_get_indice_variable(*env, variable);
	if (indice_variable == -1)
	{
		return ;
	}
	new_env = ft_copy_env_less_var(env, indice_variable);
	ft_free_doublechar(env);
	*env = new_env;
}

int	main(int argc, char **argv, char **env)
{
	char	**env_copy;
	int		last_return;
	char	*str;
	char	**str_split;
	char	*buffer;

	(void) argc;
	(void) argv;
	env_copy = ft_copy_env(env);
	last_return = 0;
	buffer = NULL;
	while (1)
	{
		str = readline("Minishell : ");
		add_history(str);
		if (str)
		{
			str = test(str, env_copy, last_return);
			str_split = ft_split_minishell(str, ' ');
			if (ft_strcmp(str_split[0], "pwd") == 0)
			{
				buffer = getcwd(buffer, 255);
				printf("%s\n", buffer);
			}
			else if (ft_strcmp(str_split[0], "cd") == 0)
			{
				chdir(str_split[1]);
				ft_change_pwd(&env_copy);
			}
			else if (ft_strcmp(str_split[0], "env") == 0)
			{
				ft_print_env(env_copy);
			}
			else if (ft_strcmp(str_split[0], "export") == 0)
			{
				ft_export_variable_env(&env_copy, str_split[1]);
			}
			else if (ft_strcmp(str_split[0], "unset") == 0)
			{
				ft_unset_variable_env(&env_copy, str_split[1]);
			}
			else
				last_return = ft_exec_path(str_split, env_copy);
			ft_free_doublechar(&str_split);
			free(str);
		}
	}
	return (0);
}