# Répertoire principal
LONG_DIR = .

# Répertoire pour la bibliothèque libft
LIBFT_DIR = $(LONG_DIR)/libft

# Répertoire pour minilibx
MLX_DIR = $(HOME)/minilibx-linux

# Nom de l'exécutable à générer
SO_LONG = so_long

# Fichiers sources
SRCS = 0_sources/main.c \
	0_sources/checks.c \
	0_sources/game_over.c \
	0_sources/create_map.c \
	0_sources/settle.c \
	0_sources/direction.c \
	0_sources/accessibility.c \
	
# Fichiers objets
OBJS = $(SRCS:.c=.o)

# Bibliothèque libft
LIBFT = $(LIBFT_DIR)/libft.a

# Bibliothèque MLX
MLX = $(MLX_DIR)/libmlx.a

# Options de compilation
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR) -I$(MLX_DIR) -I$(HOME)/minilibx-linux -g
LDFLAGS = -L$(LIBFT_DIR) -L$(MLX_DIR)
LDLIBS = -lft -lmlx -lXext -lX11 -lm

# Compilateur
CC = cc

# Règles de compilation
all: $(LIBFT) $(MLX) $(SO_LONG)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(HOME)/minilibx-linux

$(SO_LONG): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

# Compilation des fichiers objets
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(SO_LONG)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(MLX_DIR) clean

re: fclean all

.PHONY: all clean fclean re
