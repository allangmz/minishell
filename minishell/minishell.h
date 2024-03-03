/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkempf-e <tkempf-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:59:13 by aguemazi          #+#    #+#             */
/*   Updated: 2022/12/17 22:12:46 by tkempf-e         ###   ########.fr       */
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
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>

int	g_last_return;

typedef struct s_redirection
{
	int		redirection;
	char	*file;
}	t_redirection;

//cd
int				ft_change_pwd(char ***env);
int				ft_change_oldpwd(char ***env, char *oldpwd);
void			cmen(char **cmd);
int				ft_cd(char **cmd, char ***env_copy);

void			ft_add_variable_env(char ***env, char *str);

void			ft_echo(char **str_split);

void			ft_print_env(char ***env);

//export
void			ft_change_variable_env(char ***env, int indice_var, char *str);
char			*ft_variable_extract(char *str);
// static int		ft_verif_variable(char *str);
void			ft_print_export(char ***env);
int				ft_export_variable_env(char ***env, char *str);

void			ft_pwd(void);

//unset
char			**ft_copy_env_less_var(char ***env, int indice_variable);
void			ft_unset_variable_env(char ***env, char *variable);

//check_str
int				check_empty(char *str);
int				check_str(char *str);
int				check_str3(char *str);
int				check_str2(char *str);
int				ft_isforbiden(char c);

//add_str_in_str
// static void		ft_copie(char *s2, char **s1, int *i, char **newstr);
char			*ft_add_str_in_str(char **s1, char *s2, int begin);

char			*ft_create_str_copy(char *src, int n);

//delete_nchar
char			*delete_until_the_end(int newsize, char *newstr, char *str);
char			*delete_not_until_the_end(int newsize, char *newstr, char *str,
					int limit[]);
char			*ft_delete_nchar(char **str, int begin, int n);

//expand_string_variable
char			*get_variable_in_env(char *env[], char *variable);
char			*ft_add_variable(char **str, int i, int j, char *env[]);
char			*ft_expand_string_variables(char **str,
					char *env[], size_t begin, size_t n);
char			*ft_add_last_return(char **str, int i, char *char_last_return);
char			*ft_expand_last_return(char **str, char *char_last_return,
					size_t begin, size_t n);

void			ft_free_doublechar(char ***tab);

int				ft_get_indice_variable(char *env[], char *variable);

//path
char			*ft_get_path(char **command_split, char *env[], char *variable);
char			*patate_name(char **command_split, char **env[]);
int				fourchette(char	**pathname, char **command_split, char **env[]);
int				let_me_in(char **pathname, char **command_split);
int				ft_exec_path(char **command_split, char **env[]);

//pipe
int				ft_pipe_last(char *cmd, int inputfd, char ***env_copy);
void			lire_pipe(int pipe_fd);
int				ft_pipe(char *cmd, int inputfd, char ***env_copy);

char			*ft_search_path(char **command_split, char **path_list);

//split_minishell
char			**ft_split_minishell(char *s, char sep);
int				ft_size_variable(char *str);
void			ft_replace_variable(char **str, int *i, char *env[]);
void			ft_gestion_double_quote(char **str, int *i, char *env[]);
void			ft_gestion_any_quote(char **str, int *i, char *env[]);
void			ft_gestion_less_quote_malloc_words(char *s, size_t *compt,
					size_t (*i), char sep);
void			ft_gestion_space_malloc_words(char *s,
					size_t (*i), char sep);
void			ft_malloc_words2(char ***tab, size_t *j,
					size_t *compt, size_t *compt2);
char			**ft_malloc_words_minishell(char *s, char **tab, size_t nbline,
					char sep);
char			**ft_malloc_tab2d_minishell(char *s, char sep);
void			gestion_quote_nbwords(char *s, size_t *i);
int				ft_nbwords_minishell(char *s, char sep);
void			ft_gestion_quote_malloc_words(char *s, size_t *compt,
					size_t (*i), char quote);
void			ft_gestion_quote_split(char *s, char ***tab,
					size_t *i, size_t (*index)[2]);
void			ft_norminette_est_relou(char *s, size_t *i,
					char ***tab, size_t (*index)[2]);

//split_pipe
void			ft_gestion_quote_count2(char *str, int *i, int *command_count);
void			ft_gestion_quote_count_pipe(char *str, int *i);
int				ft_count_pipe(char *str);
void			ft_malloc_command(char ***tab_pipe, char *str);
void			ft_copy_gestion_pipe(char *str, char ***tab_pipe,
					int *command_count, int (*i)[2], char quote);
void			ft_copy_command(char ***tab_pipe, char *str);
char			**ft_split_pipe(char *str);

char			*translate_variable(char *str, char *env[]);

char			**ft_copy_env(char **env);

//main
int				exec_command(char **cmd, char ***env_copy);
void			your_name(char **tab_pipe, int fd,
					int saved_std[2], char ***env_copy);
void			no_name(char *str, char ***env_copy, int saved_std[2]);
int				ft_minishell(int saved_std[2], char ***env_copy);

//redirections
// static void		opens(char *str, t_redirection	redirection,
//int saved_std[2]);
// static int		loop_redirection(char **str, int saved_std[2], int *i);
void			redirect_options(char *str, char ***envp);
char			*ft_cmd(char *str, int i);
int				redirections(char *cmd, char ***envp);
t_redirection	ft_file2(t_redirection redirection, int i, char *str);
t_redirection	ft_file(char *str, int i);
int				red_loop(int *i, char **str);
void			red_if(char **str, int *i, int (*limit)[2]);
void			delete_redirection_to_str(char **str);
int				redirection_checker(char *str);
int				ft_isalnum(int c);
int				ft_test(char *str, int i);
int				ft_pick_redirection(char *str);
void			ft_gestion_quote_count(char *str, int *i);
void			here_doc(char *cmd, char *delimiter);
void			exit_redirect(char *exit);
void			enter_redirect(char *entry, char *cmd);
int				redirection_counter(char *str);
void			exit_append_redirect(char *exit, char *cmd);
void			exits(t_redirection redirection, char *str, int saved_std[2]);
void			handle_signals(int signo);

#endif