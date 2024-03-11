# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/05 17:52:23 by hbelle            #+#    #+#              #
#    Updated: 2024/02/29 13:36:21 by hbelle           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D

SRCS	=	main.c \
		srcs/parses/ft_check_args.c \
		srcs/parses/ft_check_map_file.c \
		srcs/utils/ft_error_handle.c \
		srcs/data/ft_map_into_array.c \
		srcs/parses/ft_check_map_content.c \



OBJ_DIR = .o
OBJTS = $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))
LIBFT	=	libft/libft.a

RM	=	rm -f
HEADER =	-I includes 
LIBS =	-Llibft/ -lft

CFLAGS = -Wall -Wextra -Werror -g

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@cc $(CFLAGS) $(HEADER) -c  $< -o $@
	@if test -s $*.c; then\
			echo "\033[01m\033[35mCompiling ⌛\033[00m\
			\033[36m$*.c\033[032m  [OK] ✅ \033[00m";\
			else \
			echo "\033[01m\033[33mCompiling \033[00m\
			\033[36m$*.c\033[00m\  [Error] ❌ \033[00m"; fi

$(NAME): $(OBJTS) $(LIBFT)
	@cc -o $(NAME) $(OBJTS) $(CFLAGS) $(HEADER) $(LIBS) MacroLibX/libmlx.so -lSDL2
	@echo "\033[01m\033[4;33mCompilation done\033[00m\033[1;31m =▶\033[00m\033[1;32m ./${NAME}\033[00m"

$(LIBFT):
	@make -C libft/ -s

all:	${NAME}

clean:
	@${RM} -r $(OBJ_DIR) 
	@echo "\033[01m\033[31mRemoving objects ...\033[00m"
	@make -C libft/ fclean -s

fclean:	clean
	@${RM} ${NAME}
	@echo "\033[01m\033[31mRemoving exec : ${NAME} ...\033[00m"

re:	fclean $(LIBFT) all

.PHONY: all clean fclean re