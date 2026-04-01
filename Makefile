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

# --- Inclusions ---
# -I permet au compilateur de trouver les fichiers .h
INCLUDES    = -I includes -I $(LIBFT_DIR) -I $(MLX_DIR)/includes

# --- Sources et Objets ---
SRCS_DIR    = src
SRCS        = $(SRCS_DIR)/main.c \
              $(SRCS_DIR)/init/init_mlx.c \
              $(SRCS_DIR)/init/map.c \
              $(SRCS_DIR)/error/ft_perror.c \
              $(SRCS_DIR)/on_event/mlx_event.c

OBJ_DIR     = obj
# Génère la structure des objets en miroir des sources
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

all: $(LIBFT_A) $(MLX_LIB) $(NAME)

# Compilation de la Libft
$(LIBFT_A):
	@printf "$(CYAN)Compilation de la libft...$(RESET)\n"
	@$(MAKE) -C $(LIBFT_DIR) > /dev/null
	@printf "$(GREEN)✅ libft compilée !$(RESET)\n"

# Compilation de la MLX
$(MLX_LIB):
	@printf "$(CYAN)Compilation de la MacroLibX...$(RESET)\n"
	@$(MAKE) -C $(MLX_DIR) > /dev/null 2>&1
	@printf "$(GREEN)✅ MacroLibX compilée !$(RESET)\n"

# Linkage final (Méthode Directe)
# On passe les chemins des .a et .so directement comme des fichiers objets
$(NAME): $(OBJ_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) $(MLX_LIB) -lSDL2 -lm -o $(NAME)
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
	@printf "$(RED)🗑️  $(NAME) et libft.a supprimés.$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re