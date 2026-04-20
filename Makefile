NAME        = cub3D
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
CFLAGS_BONUS = -Wall -Wextra -Werror -DBONUS=1

LIBFT_DIR   = libft
LIBFT_A     = $(LIBFT_DIR)/libft.a

MLX_DIR     = mlx
MLX_LIB     = $(MLX_DIR)/libmlx.so

FREE_DIR    = free
FREE_A      = $(FREE_DIR)/ft_free.a

INCLUDES    = -I includes -I $(LIBFT_DIR) -I $(MLX_DIR)/includes -I $(FREE_DIR)

SRCS_DIR    = src
SRCS        = $(SRCS_DIR)/main.c \
              $(SRCS_DIR)/init/init_mlx.c \
              $(SRCS_DIR)/init/map.c \
			  $(SRCS_DIR)/init/handle_map.c \
			  $(SRCS_DIR)/init/verify_map.c \
			  $(SRCS_DIR)/init/copy_map.c \
			  $(SRCS_DIR)/init/map_texture.c \
			  $(SRCS_DIR)/init/map_color.c \
			  $(SRCS_DIR)/init/init_image.c \
			  $(SRCS_DIR)/init/spawn.c \
              $(SRCS_DIR)/error/error.c \
              $(SRCS_DIR)/event/mlx_event.c \
			  $(SRCS_DIR)/event/keyhook.c \
			  $(SRCS_DIR)/event/mouse.c \
			  $(SRCS_DIR)/raycasting/to_3d.c \
			  $(SRCS_DIR)/raycasting/draw.c \
			  $(SRCS_DIR)/gnl/get_next_line.c \

OBJ_DIR     = obj
OBJS        = $(SRCS:$(SRCS_DIR)/%.c=$(OBJ_DIR)/%.o)

all: .manda $(LIBFT_A) $(FREE_A) $(MLX_LIB) $(NAME)

bonus: CFLAGS = $(CFLAGS_BONUS)
bonus: .bonus $(LIBFT_A) $(FREE_A) $(MLX_LIB) $(NAME)

.manda:
	@if [ -f .bonus ]; then rm -rf $(OBJ_DIR) $(NAME); fi
	@rm -f .bonus
	@touch .manda

.bonus:
	@if [ -f .manda ]; then rm -rf $(OBJ_DIR) $(NAME); fi
	@rm -f .manda
	@touch .bonus

$(LIBFT_A):
	@printf "Compilation libft...\n"
	@$(MAKE) -C $(LIBFT_DIR) > /dev/null
	@printf "libft OK.\n"

$(FREE_A):
	@printf "Compilation free...\n"
	@$(MAKE) -C $(FREE_DIR) > /dev/null
	@printf "free OK.\n"

$(MLX_LIB):
	@printf "Compilation MacroLibX...\n"
	@$(MAKE) -j -C $(MLX_DIR) > /dev/null 2>&1
	@printf "MacroLibX OK.\n"

$(NAME): $(OBJ_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(FREE_A) $(LIBFT_A) $(MLX_LIB) -lSDL2 -lm -o $(NAME)
	@printf "$(NAME) is OK !\n"

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) clean -C $(LIBFT_DIR) > /dev/null
	@$(MAKE) clean -C $(MLX_DIR) > /dev/null 2>&1
	@$(MAKE) clean -C $(FREE_DIR) > /dev/null
	@printf "Obj deleted.\n"

fclean: clean
	@rm -f $(NAME) .bonus .manda
	@$(MAKE) fclean -C $(LIBFT_DIR) > /dev/null
	@$(MAKE) fclean -C $(MLX_DIR) > /dev/null 2>&1
	@$(MAKE) fclean -C $(FREE_DIR) > /dev/null
	@printf "$(NAME) and librairy deleted.\n"

re: fclean all

.PHONY: all clean fclean re bonus
