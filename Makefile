# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/05 15:16:33 by mtrullar          #+#    #+#              #
#    Updated: 2024/08/15 12:27:41 by mtrullar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += --no-print-directory

NAME		=	pipex
NAME_BONUS	=	pipex_bonus
CC			=	clang
CFLAGS		=	-Wall -Wextra -Werror -g3

#Folders
INCLUDE			=	incs/
INCLUDE_BONUS	=	incs_bonus/
SRCS_DIR		=	srcs/
SRCS_BONUS_DIR	=	srcs_bonus/
LIBFT			= 	libft/
OBJ_DIR			=	obj/
OBJ_BONUS_DIR	=	obj_bonus/

MYLIBFT			= libcustomft.a
RM				=	@rm -rf

#Colors
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

BOLD = \e[1m
RESET = \e[0m

RESET_LINE			=	\033[A\033[K

SRC_FILE =	main.c					\
			parsing.c				\
			execute_commands.c		\
			free_func.c				\
			custom_split.c			\
			pipex_utils.c			\

SRC_BONUS_FILE	=	main_bonus.c				\
					parsing_bonus.c				\
					execute_commands_bonus.c	\
					free_func_bonus.c			\
					custom_split_bonus.c		\
					utils_bonus.c				\
					here_doc_bonus.c			\

SRCS		= $(addprefix $(SRCS_DIR), $(SRC_FILE))
OBJ			= $(addprefix $(OBJ_DIR), $(SRC_FILE:.c=.o))

SRCS_BONUS	= $(addprefix $(SRCS_BONUS_DIR), $(SRC_BONUS_FILE))
OBJ_BONUS	= $(addprefix $(OBJ_BONUS_DIR), $(SRC_BONUS_FILE:.c=.o))

OBJF			=	.cache_exists
OBJF_BONUS		=	.bonus_cache_exists

all: $(NAME)

$(NAME):  $(OBJ)
	@make -C $(LIBFT)
	@$(CC) -o $(NAME) $(CFLAGS) -I$(INCLUDE) $(OBJ) -Llibft -lcustomft
	@echo "$(RESET_LINE)$(MAGENTA)$(BOLD)[ PIPEX ]$(RESET)$(DEF_COLOR) COMPILED $(GREEN) ✔ $(DEF_COLOR)"

$(NAME_BONUS):	$(OBJ_BONUS)
	@make -C $(LIBFT)
	@$(CC) -o $(NAME_BONUS) $(CFLAGS) -I$(INCLUDE_BONUS) $(OBJ_BONUS) -Llibft -lcustomft
	@echo "$(RESET_LINE)$(MAGENTA)$(BOLD)[ PIPEX BONUS ]$(RESET)$(DEF_COLOR) COMPILED $(GREEN) ✔ $(DEF_COLOR)"

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c | $(OBJF)
	@$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@
	@echo "$(RESET_LINE)$(MAGENTA)$(BOLD)[ PIPEX ]$(RESET)$(DEF_COLOR)	compiling: $< $(GREEN) ✔ $(DEF_COLOR)"

$(OBJ_BONUS_DIR)%.o: $(SRCS_BONUS_DIR)%.c | $(OBJF_BONUS)
	@$(CC) $(CFLAGS) -I$(INCLUDE_BONUS) -c $< -o $@
	@echo "$(RESET_LINE)$(MAGENTA)$(BOLD)[ PIPEX_BONUS ]$(RESET)$(DEF_COLOR)	compiling: $< $(GREEN) ✔ $(DEF_COLOR)"

$(OBJF):
	@mkdir -p $(OBJ_DIR)

$(OBJF_BONUS):
	@mkdir -p $(OBJ_BONUS_DIR)
	
bonus:	$(NAME_BONUS)

clean:
	@$(RM) $(OBJ_DIR)
	@$(RM) $(OBJ_BONUS_DIR)
	@echo "\n$(RESET_LINE)$(CYAN)Object files cleared$(DEF_COLOR)"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(NAME_BONUS)
	@make fclean -sC $(LIBFT)
	@echo "$(RESET_LINE)$(CYAN)Everything cleared!$(DEF_COLOR)"

re: fclean all
	@echo "$(GREEN)\e[1mEverything has been rebuilt, fresh and clean\e[0m$(DEF_COLOR)"

.PHONY: all clean fclean re