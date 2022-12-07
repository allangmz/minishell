/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkempf-e <tkempf-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:59:13 by aguemazi          #+#    #+#             */
/*   Updated: 2022/12/07 20:04:39 by tkempf-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../Libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

char	**ft_copy_env(char **env);
int		ft_get_indice_variable(char *env[], char *variable);
char	*test(char *str, char *env[], int last_return);
void	handle_signals(int signo);
int		ft_exec_path(char **command_split, char *env[]);
void	ft_free_doublechar(char ***tab);
char	**ft_malloc_words_minishell(char *s, char **tab, size_t nbline, char sep);
char	**ft_split_minishell(char *s, char sep);
char	*ft_add_str_in_str(char *s1, char *s2, int begin);
char	*ft_delete_nchar(char *str, int begin, int n);
char	*ft_expand_string_variables(char *str, char *env[], size_t begin,
			size_t n);
char	*get_variable_in_env(char *env[], char *variable);
char	*ft_expand_last_return(char *str, char *char_last_return, size_t begin,
			size_t n);
char	**ft_split_pipe (char *str);
int		redirections(char *str, char **envp);
int		exec_command(char **cmd, char **env_copy);
// BULTIN
void	ft_echo(char	**str_split);
void	ft_unset_variable_env(char ***env, char *variable);
void	ft_export_variable_env(char ***env, char *str);
void	ft_print_env(char **env);
void	ft_cd(char **cmd, char ***env_copy);
void	ft_pwd(void);

#endif