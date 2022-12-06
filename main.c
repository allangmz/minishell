/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemazi <aguemazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 16:55:11 by aguemazi          #+#    #+#             */
/*   Updated: 2022/12/06 18:57:33 by aguemazi         ###   ########.fr       */
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

int ft_count_pipe(char *str)
{
	int	pipe_count;
	int	i;

	i = 0;
	pipe_count = 1;
	while (str[i])
	{
		if (str[i] && str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			i++;
		}
		if (str[i] && str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				i++;
			i++;
		}
		if (str[i] && str[i] == '|')
			pipe_count++;
		i++;
	}
	return (pipe_count);
}

void ft_gestion_quote_count(char *str, int *i, int *command_count)
{
	if (str[*i] && str[*i] == '\'')
	{
		*i += 1;
		*command_count += 1;
		while (str[*i] && str[*i] != '\'')
		{
			*i += 1;
			*command_count += 1;
		}
		*i += 1;
		*command_count += 1;
	}
	if (str[*i] && str[*i] == '\"')
	{
		*i += 1;
		*command_count += 1;
		while (str[*i] && str[*i] != '\"')
		{
			*i += 1;
			*command_count += 1;
		}
		*i += 1;
		*command_count += 1;
	}
}

void	ft_malloc_command(char ***tab_pipe, char *str)
{
	int	i;
	int	j;
	int	command_count;

	command_count = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		ft_gestion_quote_count(str, &i, &command_count);
		if (str[i] && str[i] != '\'' && str[i] != '\"' && str[i] != '|')
		{
			i++;
			command_count++;
		}
		if (str[i] && str[i] == '|')
		{
			(*tab_pipe)[j] = malloc(sizeof(char *) * command_count + 1);
			(*tab_pipe)[j++][command_count] = '\0';
			i++;
			command_count = 0;
		}
	}
	(*tab_pipe)[j] = malloc(sizeof(char *) * command_count + 1);
	(*tab_pipe)[j][command_count] = '\0';
}

void ft_copy_gestion_pipe(char *str, char ***tab_pipe, int *command_count, int (*i)[2], char quote)
{
	if (str[(*i)[0]] && str[(*i)[0]] == quote)
	{
		(*tab_pipe)[(*i)[1]][*command_count] = str[(*i)[0]];
		*command_count += 1;
		(*i)[0] += 1;
		while (str[(*i)[0]] && str[*i[0]] != quote)
		{
			(*tab_pipe)[(*i)[1]][*command_count] = str[(*i)[0]];
			(*i)[0] += 1;
			*command_count += 1;
		}
		(*tab_pipe)[(*i)[1]][*command_count] = str[(*i)[0]];
		(*i)[0] += 1;
		*command_count += 1;
	}
}

void	ft_copy_command(char ***tab_pipe, char *str)
{
	int		indice[2];
	int		command_count;

	indice[0] = 0;
	indice[1] = 0;
	command_count = 0;
	while (str[indice[0]])
	{
		ft_copy_gestion_pipe(str, tab_pipe, &command_count, &indice, '\'');
		ft_copy_gestion_pipe(str, tab_pipe, &command_count, &indice, '\"');
		if (str[indice[0]] && str[indice[0]] != '\'' && str[indice[0]] != '\"' && str[indice[0]] != '|')
		{
			(*tab_pipe)[indice[1]][command_count] = str[indice[0]];
			indice[0]++;
			command_count++;
		}
		if (str[indice[0]] && str[indice[0]] == '|')
		{
			indice[0]++;
			indice[1]++;
			command_count = 0;
		}
	}
}

char **ft_split_pipe (char *str)
{
	char	**tab_pipe;
	int		pipe_count;

	if (!str)
		return (NULL);
	pipe_count = ft_count_pipe(str);
	tab_pipe = malloc(sizeof(char *) * pipe_count + 1);
	tab_pipe[pipe_count] = NULL;
	ft_malloc_command(&tab_pipe, str);
	ft_copy_command(&tab_pipe, str);
	return (tab_pipe);
}

int exec_command(char **cmd, char **env_copy)
{
	char	*buffer;
	int		last_return;


	last_return = 0;
	buffer = NULL;
	if (ft_strcmp(cmd[0], "pwd") == 0) // qund PWD est unset ca detruis OLDPWD ?
	{
		buffer = getcwd(buffer, 255);
		printf("%s\n", buffer);
	}
	else if (ft_strcmp(cmd[0], "cd") == 0)
	{
		buffer = getcwd(buffer, 255);
		ft_change_oldpwd(&env_copy, buffer);
		chdir(cmd[1]);
		ft_change_pwd(&env_copy);// valeur de retour last_return
	}
	else if (ft_strcmp(cmd[0], "env") == 0)
	{
		ft_print_env(env_copy);// valeur de retour last_return
	}
	else if (ft_strcmp(cmd[0], "export") == 0)
	{
		ft_export_variable_env(&env_copy, cmd[1]); // verifier que la valeur est presente
	}
	else if (ft_strcmp(cmd[0], "unset") == 0)
	{
		ft_unset_variable_env(&env_copy, cmd[1]);// valeur de retour last_return
	}
	else if (ft_strcmp(cmd[0], "echo") == 0)	
	{
		ft_echo(cmd); // valeur de retour last_return
		// fprintf(stderr,"salkut\n");
	}
	else
	{
		last_return = ft_exec_path(cmd, env_copy); // gerer le last return
	}
	return (last_return);
}

int	ft_pipe(char **cmd, int inputfd, char **env_copy)
{
	int		fd[2];
	char	*buffer;

	pipe(fd);
	buffer = NULL;
	// close(fd[0]);
	if (dup2(inputfd, STDIN_FILENO) == -1)
		fprintf(stderr,"GROSSE MERDE 1 ");
	close(inputfd);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		fprintf(stderr,"GROSSE MERDE 2");
	if (exec_command(cmd, env_copy) != 0)
	{
		fprintf(stderr,"GROSSE MERDE 3");
		return (-1);
	}
	close(fd[1]);
	return (fd[0]);
}

int	ft_pipe_last(char **cmd, int inputfd, char **env_copy)
{
	int		fd[2];
	char	*buffer;


	buffer = NULL;
	close(fd[1]);
	close(fd[0]);
	dup2(inputfd, STDIN_FILENO);
	exec_command(cmd, env_copy);
	return (0);
}

void lire_pipe(int pipe_fd)
{
	char      buffer[1024];
      int       ret;

      while ((ret = read(pipe_fd, buffer, 1023)) != 0)
      {
        fprintf(stderr,"%d\n", ret);
        buffer[ret] = 0;
        fprintf(stderr,"%s\n", buffer);
      }
}


int	main(int argc, char **argv, char **env)
{
	char	**env_copy;
	int		last_return;
	char	*str;
	char	**str_split;
	char	**tab_pipe;
	char	*buffer;
	int		fd;	
	int		i;
	int		saved_stdout;
	int		saved_stdin;

	(void) argc;
	(void) argv;
	env_copy = ft_copy_env(env);
	saved_stdout = dup(1);
	saved_stdin = dup(0);
	last_return = 0;
	buffer = NULL;
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, handle_signals);
	while (1)
	{
		// fprintf(stderr,"test\n");
		str = readline("Minishell : ");
		if (!str)
		{
			return (0);
		}
		// fprintf(stderr,"test\n");
		usleep(20);
		add_history(str);
		i = 0;
		tab_pipe = ft_split_pipe(str);
		fd = STDIN_FILENO;
		free(str);
		while (tab_pipe && tab_pipe[i])
		{
			tab_pipe[i] = test(tab_pipe[i], env_copy, last_return); // renomme les variable selon "" ''
			str_split = ft_split_minishell(tab_pipe[i], ' '); // split les espace selon les "" ''
			if (tab_pipe[i + 1])
			{
				dup2(saved_stdout, STDOUT_FILENO);
				fd = ft_pipe(str_split, fd, env_copy);
				dup2(saved_stdin, STDIN_FILENO);
			}	
			else
			{
				// lire_pipe(fd);
				dup2(saved_stdout, STDOUT_FILENO);
				ft_pipe_last(str_split, fd, env_copy);
			}
			i++;
		}
		close (fd);
		if (tab_pipe)
			ft_free_doublechar(&tab_pipe);
		dup2(saved_stdin, STDIN_FILENO);
		// fprintf(stderr,"i   %d", i);
	}
	return (0);
}

// rajouter des protection sur toute les fonctions + les retour pour $? de chaque fonction + verifier que tout soit free au bon moment

// errreur ----> echo "cat | cat | cat | cat |" | cat