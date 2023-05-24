NAME		=	minishell

SRCDIR		=	./src
OBJDIR		=	./obj

SRCS		=	$(wildcard $(SRCDIR)/*.c)
OBJS		=	$(addprefix $(OBJDIR)/,$(notdir $(SRCS:.c=.o)))

# **************************************************************************** #
#                               REMOVE WILDCARD                                #
# **************************************************************************** #

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra
LDFLAGS		=	-lreadline -L $(HOME)/.brew/opt/readline/lib
INCFLAGS	=	-I $(HOME)/.brew/opt/readline/include

RM			=	rm
RMFLAGS		=	-rf

LIBFT_GIT	=	https://github.com/aaron-22766/libft.git
LIBFT_DIR	=	./libft
LIBFT_LIB	=	libft.a
LIBFT		=	$(LIBFT_DIR)/$(LIBFT_LIB)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(INCFLAGS)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIBFT):
	git clone $(LIBFT_GIT) $(LIBFT_DIR); make -C $(LIBFT_DIR)

all: $(NAME)

clean:
	$(RM) $(RMFLAGS) $(OBJDIR)

fclean: clean
	$(RM) $(RMFLAGS) $(NAME)

libclean:
	$(RM) $(RMFLAGS) $(LIBFT_DIR)

allclean: fclean libclean

re: fclean all

.PHONY: all clean fclean re libclean allclean