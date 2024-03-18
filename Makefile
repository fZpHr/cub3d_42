# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/01 00:00:00 by ysabik            #+#    #+#              #
#    Updated: 2024/03/18 16:09:34 by ysabik           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC					= gcc
CFLAGS				= -Werror -Wall -Wextra -g
NAME				= cub3D
INCLUDES			= ./includes
SRC_FILES			= \
						srcs/main.c \
						srcs/data/ft_map_into_array.c \
						srcs/data/ft_assign_to_cube.c \
						srcs/parses/ft_check_args.c \
						srcs/parses/ft_check_map_file.c \
						srcs/parses/ft_check_map_content.c \
						srcs/parses/ft_check_texture.c \
						srcs/parses/ft_access_texture.c \
						srcs/parses/ft_parse_checker.c \
						srcs/rendering/interactions/ft_does_collide.c \
						srcs/rendering/interactions/ft_handle_action.c \
						srcs/rendering/interactions/ft_handle_doors.c \
						srcs/rendering/interactions/ft_handle_keys.c \
						srcs/rendering/interactions/ft_move_backward.c \
						srcs/rendering/interactions/ft_move_forward.c \
						srcs/rendering/mlx/ft_game_keydown.c \
						srcs/rendering/mlx/ft_game_keyup.c \
						srcs/rendering/mlx/ft_game_loop.c \
						srcs/rendering/mlx/ft_game_mouse.c \
						srcs/rendering/mlx/ft_game_quit.c \
						srcs/rendering/mlx/ft_mlx_init.c \
						srcs/rendering/mlx/ft_mlx_new_frame.c \
						srcs/rendering/put/ft_put_line.c \
						srcs/rendering/put/ft_put_pixel.c \
						srcs/rendering/put/ft_put_rect.c \
						srcs/rendering/raycasting/ft_cast_ray.c \
						srcs/rendering/raycasting/ft_hor_casting.c \
						srcs/rendering/raycasting/ft_ver_casting.c \
						srcs/rendering/ft_anim.c \
						srcs/rendering/ft_render.c \
						srcs/rendering/ft_render_ceiling.c \
						srcs/rendering/ft_render_chunk.c \
						srcs/rendering/ft_render_floor.c \
						srcs/rendering/ft_render_info.c \
						srcs/rendering/ft_rendering.c \
						srcs/rendering/ft_render_minimap.c \
						srcs/utils/ft_function.c \
						srcs/utils/ft_init.c \
						srcs/utils/ft_error_handle.c \
						srcs/utils/ft_error.c \
						srcs/utils/ft_lli_to_str.c \
						srcs/utils/ft_numlen.c \
						srcs/utils/ft_ftoa.c

BUILD_FOLDER		= ./build

LIBFT_FOLDER		= ./libft
LIBFT_A				= $(LIBFT_FOLDER)/libft.a
LIBFT_FLAGS			= -L $(LIBFT_FOLDER) -lft -I $(LIBFT_FOLDER)

MLX_FOLDER			= ./minilibx-linux
MLX_A				= $(MLX_FOLDER)/libmlx.a
MLX_FLAGS			= -L $(MLX_FOLDER) -lmlx -lXext -lX11 -lm -lbsd -I $(MLX_FOLDER)

C_RESET				= \033[0m
C_BOLD				= \033[1m
C_DIM				= \033[2m
C_UNDERLINE			= \033[4m
C_BLINK				= \033[5m
C_BLACK				= \033[30m
C_RED				= \033[31m
C_GREEN				= \033[32m
C_YELLOW			= \033[33m
C_BLUE				= \033[34m
C_MAGENTA			= \033[35m
C_CYAN				= \033[36m
C_WHITE				= \033[37m

OBJ_FILES			= $(SRC_FILES:.c=.o)
BUILD_FILES			= $(addprefix $(BUILD_FOLDER)/, $(OBJ_FILES))

TO_COMPILE			= 0

all : $(NAME)

$(NAME) : $(BUILD_FILES)
	@echo ""
	@echo -n "  > $(C_YELLOW)$(C_BOLD)./$(NAME)$(C_RESET):  $(C_DIM)"
	$(CC) $(CFLAGS) -o $(NAME) $(BUILD_FILES) -I $(INCLUDES) $(LIBFT_FLAGS) $(MLX_FLAGS)
	@echo "$(C_RESET)"
	@echo ""
	@echo -n "$(C_BOLD)$(C_MAGENTA)>$(C_BLUE)>$(C_CYAN)>$(C_GREEN)"
	@echo -n " Compilation success ! "
	@echo "$(C_CYAN)<$(C_BLUE)<$(C_MAGENTA)<$(C_RESET)"
	@echo ""

m_line_break :
	@echo ""

b_flags :
	@$(eval CFLAGS += -D BONUS=1)
	@$(eval CFLAGS += -D HIDE_MOUSE=0)

bonus : b_flags all

$(LIBFT_A) :
	@echo -n "$(C_CYAN)$(C_BOLD)$(C_UNDERLINE)"
	@echo "Compiling $(C_YELLOW)$(LIBFT_A)$(C_CYAN)... :$(C_RESET)"
	@echo ""
	@make -C $(LIBFT_FOLDER)
	@echo "$(C_RESET)"
	@echo ""

$(MLX_A) :
	@echo -n "$(C_CYAN)$(C_BOLD)$(C_UNDERLINE)"
	@echo "Compiling $(C_YELLOW)$(MLX_A)$(C_CYAN)... :$(C_RESET)"
	@echo ""
	@make -C $(MLX_FOLDER)
	@echo "$(C_RESET)"
	@echo ""

$(BUILD_FOLDER)/%.o : %.c | $(LIBFT_A) $(MLX_A)
	@if [ $(TO_COMPILE) -eq 0 ] ; then \
		echo -n "$(C_CYAN)$(C_BOLD)$(C_UNDERLINE)" ; \
		echo "Compiling $(C_YELLOW)./$(NAME)$(C_CYAN)... :$(C_RESET)" ; \
		echo "" ; \
	fi
	@$(eval TO_COMPILE := 1)
	@echo -n "  - $(C_GREEN)$<$(C_RESET):  $(C_DIM)"
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES) $(LIBFT_FLAGS) $(MLX_FLAGS)
	@echo -n "$(C_RESET)"

define del =
	@echo -n "$(C_RED)$(C_BOLD)$(C_UNDERLINE)"
	@echo "Deleting files... :$(C_RESET)$(C_RED)"
	@\
	l=-1 ; \
	for file in $(1) ; do \
		if [ $${#file} -gt $$l ] ; then \
			l=$${#file} ; \
		fi ; \
	done ; \
	cols=$$((64 / $$l)) ; \
	i=0 ; \
	for file in $(1) ; do \
		if [ $$i -eq 0 ] ; then \
			echo -n "    " ; \
		fi ; \
		if [ "$$file" = "./$(NAME)" ] ; then \
			printf "$(C_YELLOW)%-$$((l))s  $(C_RED)" "$$file" ; \
		else \
			printf "%-$$((l))s  " "$$file" ; \
		fi ; \
		if [ $$i -gt $$cols ] ; then \
			echo "" ; \
			i=-1; \
		fi ; \
		i=$$(($$i + 1)); \
	done ; \
	if [ $$i -ne -1 ] ; then \
		echo "" ; \
	fi
	@echo "$(C_RESET)"
endef

clean :
	@echo -n "$(C_RED)$(C_BOLD)$(C_UNDERLINE)"
	@echo "Cleaning $(LIBFT_FOLDER)... :$(C_RESET)$(C_DIM)"
	@make -C $(LIBFT_FOLDER) clean
	@echo "$(C_RESET)"
	@echo -n "$(C_RED)$(C_BOLD)$(C_UNDERLINE)"
	@echo "Cleaning $(MLX_FOLDER)... :$(C_RESET)$(C_DIM)"
	@make -C $(MLX_FOLDER) clean
	@echo "$(C_RESET)"
	$(call del, "$(BUILD_FOLDER)" $(BUILD_FILES))
	@rm -rf $(BUILD_FILES) $(BUILD_FOLDER)

fclean :
	@echo -n "$(C_RED)$(C_BOLD)$(C_UNDERLINE)"
	@echo "FCleaning $(LIBFT_FOLDER)... :$(C_RESET)$(C_DIM)"
	@make -C $(LIBFT_FOLDER) fclean
	@echo "$(C_RESET)"
	@echo -n "$(C_RED)$(C_BOLD)$(C_UNDERLINE)"
	@echo "FCleaning $(MLX_FOLDER)... :$(C_RESET)$(C_DIM)"
	@make -C $(MLX_FOLDER) clean
	@echo "$(C_RESET)"
	$(call del, "./$(NAME)" "$(BUILD_FOLDER)" $(BUILD_FILES))
	@rm -rf $(NAME) $(BUILD_FILES) $(BUILD_FOLDER)

re : fclean m_line_break all

re_bonus : fclean m_line_break bonus

soft_clean :
	$(call del, "$(BUILD_FOLDER)" $(BUILD_FILES))
	@rm -rf $(BUILD_FILES) $(BUILD_FOLDER)

soft_fclean :
	$(call del, "./$(NAME)" "$(BUILD_FOLDER)" $(BUILD_FILES))
	@rm -rf $(NAME) $(BUILD_FILES) $(BUILD_FOLDER)

soft_re : soft_fclean m_line_break all

soft_re_bonus : soft_fclean m_line_break bonus

.PHONY : all bonus clean fclean re re_bonus \
			soft_clean soft_fclean soft_re soft_re_bonus \
			m_line_break b_flags

