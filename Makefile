CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
SRC = minishell_loop.c\
	minishell_tokenizer1.c\
	minishell_tokenizer2.c\
	minishell_roles_cmdexpected.c\
	minishell_syntax_check.c\
	minishell_signal_handling.c\
	minishell_free_and_exit.c\
	minishell_init.c\
	minishell_utils.c\
	minishell_utils2.c\
	minishell_utils3.c\
	m_command_filler.c\
	m_execution.c

OBJ = $(addprefix objects/, $(SRC:.c=.o))
NAME = minishell
LDFLAGS = -lreadline

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(LDFLAGS)

objects/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
