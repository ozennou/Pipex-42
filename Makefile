NAME = pipex

NAME_B = pipex_bonus

SCRS = main.c utils.c utils2.c utils3.c utils4.c cmds.c my_split.c

SRCS_B = main_bonus.c utils_bonus.c utils2_bonus.c utils3_bonus.c utils4_bonus.c cmds_bonus.c set_bonus.c heredoc_bonus.c \
		get_next_line_bonus.c get_next_line_utils_bonus.c my_split_bonus.c

OBJS = $(SCRS:.c=.o)

OBJS_B = $(SRCS_B:.c=.o)

CC = cc -Wall -Wextra -Werror

RM = rm -f


%_bonus.o : %_bonus.c pipex_bonus.h get_next_line_bonus.h
	@echo "$< Compiling bonus..."
	@$(CC) -c $< -o $(<:.c=.o)

%.o : %.c pipex.h
	@echo "$< Compiling..."
	@$(CC) -c $< -o $(<:.c=.o)

$(NAME) : $(OBJS)
	@echo "Linking..."
	@$(CC) $(OBJS) -o $(NAME)

$(NAME_B) : $(OBJS_B)
	@echo "Linking bonus..."
	@$(CC) $(OBJS_B) -o $(NAME_B)

all: $(NAME)
	
bonus : $(NAME_B)

clean :
	@echo "Cleaning..."
	@$(RM) $(OBJS) $(OBJS_B)

fclean : clean
	@echo "Full cleaning..."
	@$(RM) $(NAME) $(NAME_B)

re : fclean all