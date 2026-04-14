# --- Couleurs et Styles ---
GREEN       = \033[1;32m
RED         = \033[1;31m
YELLOW      = \033[1;33m
CYAN        = \033[1;36m
RESET       = \033[0m

# --- Configuration du Projet ---
NAME        = cub3D
CC          = cc
CFLAGS      = -Wall -Wextra -Werror

# --- Configuration LIBFT ---
LIBFT_DIR   = libft
LIBFT_A     = $(LIBFT_DIR)/libft.a

# --- Configuration MLX (MacroLibX) ---
MLX_DIR     = mlx
MLX_LIB     = $(MLX_DIR)/libmlx.so

# --- Configuration FREE ---
FREE_DIR    = free
FREE_A      = $(FREE_DIR)/ft_free.a

# --- Inclusions ---
# -I permet au compilateur de trouver les fichiers .h
INCLUDES    = -I includes -I $(LIBFT_DIR) -I $(MLX_DIR)/includes -I $(FREE_DIR) -I src/gnl

# --- Sources et Objets ---
SRCS_DIR    = src
SRCS        = $(SRCS_DIR)/main.c \
              $(SRCS_DIR)/init/init_mlx.c \
              $(SRCS_DIR)/init/map.c \
			  $(SRCS_DIR)/init/map_texture.c \
			  $(SRCS_DIR)/init/map_color.c \
			  $(SRCS_DIR)/init/init_image.c \
			  $(SRCS_DIR)/init/spawn.c \
              $(SRCS_DIR)/error/ft_perror.c \
              $(SRCS_DIR)/on_event/mlx_event.c \
			  $(SRCS_DIR)/raystracing/to_3d.c \
			  $(SRCS_DIR)/raystracing/draw.c \
			  $(SRCS_DIR)/keyhook/keyhook.c \
			  $(SRCS_DIR)/gnl/get_next_line.c \

# Génère la structure des objets en miroir des sources
OBJ_DIR     = obj
OBJS        = $(SRCS:$(SRCS_DIR)/%.c=$(OBJ_DIR)/%.o)

# --- Logique de la barre de progression ---
TOTAL_FILES  := $(words $(SRCS))
CURRENT_FILE := 0

define progress_bar
    @$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE) + 1))))
    @$(eval PERCENT=$(shell echo $$(($(CURRENT_FILE) * 100 / $(TOTAL_FILES)))))
    @printf "\r$(CYAN)Compilation de $(NAME) : [%-20s] %d%% $(RESET)" \
        "$$(printf '#%.0s' $$(seq 1 $$(($(PERCENT) / 5))))" "$(PERCENT)"
endef

# --- Règles Principales ---

all: $(LIBFT_A) $(FREE_A) $(MLX_LIB) $(NAME)

# Compilation de la Libft
$(LIBFT_A):
	@printf "$(CYAN)Compilation de la libft...$(RESET)\n"
	@$(MAKE) -C $(LIBFT_DIR) > /dev/null
	@printf "$(GREEN)✅ libft compilée !$(RESET)\n"

# Compilation de ft_free
$(FREE_A):
	@printf "$(CYAN)Compilation de la free...$(RESET)\n"
	@$(MAKE) -C $(FREE_DIR) > /dev/null
	@printf "$(GREEN)✅ free compilée !$(RESET)\n"

# Compilation de la MLX
$(MLX_LIB):
	@printf "$(CYAN)Compilation de la MacroLibX...$(RESET)\n"
	@$(MAKE) -C $(MLX_DIR) > /dev/null 2>&1
	@printf "$(GREEN)✅ MacroLibX compilée !$(RESET)\n"

# Linkage final (Méthode Directe)
# On passe les chemins des .a et .so directement comme des fichiers objets
$(NAME): $(OBJ_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(FREE_A) $(LIBFT_A) $(MLX_LIB) -lSDL2 -lm -o $(NAME)
	@printf "\n$(GREEN)✅ $(NAME) est prêt !$(RESET)\n"

# Compilation des fichiers objets (.o)
$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(@D)
	@$(call progress_bar)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# --- Nettoyage ---

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) clean -C $(LIBFT_DIR) > /dev/null
	@$(MAKE) clean -C $(MLX_DIR) > /dev/null 2>&1
	@printf "$(YELLOW)🧹 Fichiers objets supprimés.$(RESET)\n"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR) > /dev/null
	@$(MAKE) fclean -C $(FREE_DIR) > /dev/null
	@printf "$(RED)🗑️  $(NAME), libft.a et ft_free.a supprimés.$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re