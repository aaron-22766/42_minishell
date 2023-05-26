NAME		=	minishell

INCDIR		=	./include/minishell
SRCDIR		=	./src
SUBDIRS		=	minishell lexer parser evaluator executor
OBJDIR		=	./obj

INCS		=	$(wildcard *.h $(INCDIR))
SRCS		=	$(wildcard *.c $(foreach fd, $(SRCDIR)/$(SUBDIRS), $(fd)/*.c))
OBJS		=	$(addprefix $(OBJDIR)/,$(SRCS:.c=.o))

# **************************************************************************** #
#                               REMOVE WILDCARD                                #
# **************************************************************************** #

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra
LDFLAGS		=	-lreadline -L $(HOME)/.brew/opt/readline/lib
INCFLAGS	=	-I $(HOME)/.brew/opt/readline/include -I $(INCDIR)

RM			=	rm
RMFLAGS		=	-rf

LIBFT_GIT	=	https://github.com/aaron-22766/libft.git
LIBFT_DIR	=	./libft
LIBFT_LIB	=	libft.a
LIBFT		=	$(LIBFT_DIR)/$(LIBFT_LIB)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: %.c $(INCS)
	mkdir -p $(@D)
	$(CC) -c -o $@ $< $(CFLAGS) $(INCFLAGS)

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