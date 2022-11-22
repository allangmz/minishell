SRCS = ft_path.c ft_free_double_char.c ft_get_indice_variable.c main.c ft_expand_string_variables.c ft_add_str_in_str.c ft_delete_nchar.c ft_split_minishell.c
OBJS	=	$(SRCS:.c=.o)

GCC		=	gcc

RM		=	rm -rf

FLAGS	=	-Wall -Wextra -Werror

NAME	=	minishell

all:		$(NAME)

%.o:		%.c
			@$(GCC) -I. -I${HOME}/.brew/opt/readline/include -o $@ -c $? $(FLAGS) -g3

$(NAME):	$(OBJS)
			@$(MAKE) -C ../Libft
			@$(GCC) $(FLAGS) $(OBJS) -lreadline -L/Users/tkempf-e/.brew/opt/readline/lib -I/Users/tkempf-e/.brew/opt/readline/include ../Libft/Libft.a -o $(NAME) -g3
			@echo "\033[1;32mCompilation complete ✅";

clean:
			@$(MAKE) clean -C ../Libft
			@$(RM) $(OBJS)
			@echo "\033[1;32mCleaning complete 🧽"

fclean:		clean
			@$(MAKE) fclean -C ../Libft
			@$(RM) $(NAME)
			@echo "\033[1;32mFull cleaning complete 🧹"

re:			fclean all
			@echo "\033[1;32mRebuild complete 🔨"

.PHONY:		all fclean clean re
# gcc -lreadline -L/Users/tkempf-e/.brew/opt/readline/lib -I/Users/tkempf-e/.brew/opt/readline/include signals.c
