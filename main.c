/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemazi <aguemazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 16:55:11 by aguemazi          #+#    #+#             */
/*   Updated: 2022/11/29 20:38:58 by aguemazi         ###   ########.fr       */
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

	if (!variable)
	{
		// messafe d'erreur unset: not enough argument
		return ;
	}
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

void	ft_echo(char	**str_split)
{
	int	new_line_at_end;
	int	i;

	new_line_at_end = 1;
	i = 1;
	if (str_split[1] && ft_strcmp(str_split[1], "-n") == 0)
	{
		new_line_at_end = 0;
		i = 2;
	}
	while (str_split[i])
	{
		ft_putstr_fd(str_split[i], 1);
		i++;
	}
	if (new_line_at_end)
	{
		ft_putchar_fd('\n', 1);
	}
	return ;
}

void handle_signals(int signo)
{
	if (signo == SIGINT)//ctrl-c
	{
		printf("\n");
		rl_on_new_line();
		// rl_replace_line("", 0); // je sais pas comment le faire fonctionner faut demander a theo skuuuuuuuuuuuuuu
		rl_redisplay();
	}
	else if (signo == SIGQUIT)/* ctrl-\  */
	{
		rl_on_new_line();
		rl_redisplay();
		printf("  \b\b");
	}
}

char **ft_split_pipe (char *str)
{
	char	**tab_pipe;
	int		i;
	int		j;
	int		pipe_count;
	int		command_count;

	i = 1;
	pipe_count = 1; // fonction qui compte le nombre de pipe
	while (str[i])
	{
		if (str[i] && str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] == '\'')
				i++;
			i++;
		}
		if (str[i] && str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] == '\"')
				i++;
			i++;
		}
		if (str[i] && str[i] == '|')
		{
			pipe_count++;
		}
		i++;
	}
	// fprintf(stderr,"pipe count %d\n", pipe_count);
	tab_pipe = malloc(sizeof(char *) * pipe_count + 1);
	tab_pipe[pipe_count] = NULL;
	command_count = 0;// fonction nombre de caractere d'une commande entre pipe
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] && str[i] == '\'')
		{
			command_count++;
			i++;
			while (str[i] && str[i] == '\'')
			{
				i++;
				command_count++;
			}
			i++;
			command_count++;
		}
		if (str[i] && str[i] == '\"')
		{
			i++;
			command_count++;
			while (str[i] && str[i] == '\"')
			{
				i++;
				command_count++;
			}
			i++;
			command_count++;
		}
		if (str[i] && str[i] != '\'' && str[i] != '\"' && str[i] != '|')
		{
			i++;
			command_count++;
		}
		if (str[i] && str[i] == '|')
		{
			tab_pipe[j] = malloc(sizeof(char *) * command_count + 1);
			tab_pipe[j][command_count] = '\0';
			// fprintf(stderr,"command count %d\n", command_count);
			i++;
			j++;
			command_count = 0;
		}
		// fprintf(stderr,"command count oui %d\n", command_count);
	}
	tab_pipe[j] = malloc(sizeof(char *) * command_count + 1);
	tab_pipe[j][command_count] = '\0';
	//fonction qui recopie
	i = 0;
	j = 0;
	command_count = 0;
	while (str[i])
	{
		if (str[i] && str[i] == '\'')
		{
			tab_pipe[j][command_count] = str[i];
			command_count++;
			i++;
			while (str[i] && str[i] == '\'')
			{
				tab_pipe[j][command_count] = str[i];
				i++;
				command_count++;
			}
			tab_pipe[j][command_count] = str[i];
			i++;
			command_count++;
		}
		if (str[i] && str[i] == '\"')
		{
			tab_pipe[j][command_count] = str[i];
			i++;
			command_count++;
			while (str[i] && str[i] == '\"')
			{
				tab_pipe[j][command_count] = str[i];
				i++;
				command_count++;
			}
			tab_pipe[j][command_count] = str[i];
			i++;
			command_count++;
		}
		if (str[i] && str[i] != '\'' && str[i] != '\"' && str[i] != '|')
		{
			tab_pipe[j][command_count] = str[i];
			i++;
			command_count++;
		}
		if (str[i] && str[i] == '|')
		{
			i++;
			j++;
			command_count = 0;
		}
	}
	return (tab_pipe);
}

int	main(int argc, char **argv, char **env)
{
	char	**env_copy;
	int		last_return;
	char	*str;
	char	**str_split;
	char	**tab_pipe;
	char	*buffer;
	int		fd[2];
	int		pid;
	int inputfd;

	inputfd = STDIN_FILENO;
	
	int		i;

	(void) argc;
	(void) argv;
	env_copy = ft_copy_env(env);
	last_return = 0;
	buffer = NULL;
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, handle_signals);
	while (1)
	{
		str = readline("Minishell : ");
		if (!str)
		{
			printf("exit");
			exit(0);
		}
		add_history(str);
		i = 0;
		tab_pipe = ft_split_pipe(str);
		free(str);
		while (tab_pipe[i])
		{
			pipe(fd);
			pid = fork();
			if (pid == 0)
			{
				close(fd[0]);
				dup2(inputfd, STDIN_FILENO);
				close(inputfd);
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
				if (tab_pipe[i])
				{
					pipe(fd);
					pid = fork();
					if (pid == 0)
					{
						close(fd[0]);
						dup2(inputfd, STDIN_FILENO);
						close(inputfd);
						dup2(fd[1], STDOUT_FILENO);
						close(fd[1]);
						tab_pipe[i] = test(tab_pipe[i], env_copy, last_return); // renomme les variable selon "" ''
						str_split = ft_split_minishell(tab_pipe[i], ' '); // split les espace selon les "" ''
						if (ft_strcmp(str_split[0], "pwd") == 0) // qund PWD est unset ca detruis OLDPWD ?
						{
							buffer = getcwd(buffer, 255);
							printf("%s\n", buffer);
						}
						else if (ft_strcmp(str_split[0], "cd") == 0)
						{
							buffer = getcwd(buffer, 255);
							ft_change_oldpwd(&env_copy, buffer);
							chdir(str_split[1]);
							ft_change_pwd(&env_copy);// valeur de retour last_return
						}
						else if (ft_strcmp(str_split[0], "env") == 0)
						{
							ft_print_env(env_copy);// valeur de retour last_return
						}
						else if (ft_strcmp(str_split[0], "export") == 0)
						{
							ft_export_variable_env(&env_copy, str_split[1]); // verifier que la valeur est presente
						}
						else if (ft_strcmp(str_split[0], "unset") == 0)
						{
							ft_unset_variable_env(&env_copy, str_split[1]);// valeur de retour last_return
						}
						else if (ft_strcmp(str_split[0], "echo") == 0)
						{
							ft_echo(str_split); // valeur de retour last_return
							// fprintf(stderr,"salkut\n");
						}
						else
							last_return = ft_exec_path(str_split, env_copy);
						ft_free_doublechar(&str_split);
					}
					close(fd[1]);
					waitpid(pid, 0, 0);
					inputfd = fd[0];
				}
					
			}
			close(fd[1]);
			waitpid(pid, 0, 0);
			i++;
		}
		// fprintf(stderr,"i   %d", i);
	}
	return (0);
}

// rajouter des protection sur toute les fonctions + les retour pour $? de chaque fonction + verifier que tout soit free au bon moment