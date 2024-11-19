NAME		= fractol
INCLUDE		= include
CC			= cc
CFLAGS		=  -I$(INCLUDE)

SRCS		= main.c hooks.c fractol.c complex.c utils.c

LIBFT			= ft
LIBFT_ARCHIVE	= libft.a
LIBFT_DIR		= libft

MLX			= mlx_Linux
MLX_ARCHIVE	= libmlx_Linux.a
MLX_DIR		= minilibx-linux


all: $(LIBFT_ARCHIVE) $(MLX_ARCHIVE) $(NAME)

$(LIBFT_ARCHIVE):
	make -C $(LIBFT_DIR)

$(MLX_ARCHIVE):
	make -C $(MLX_DIR)


$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME) -L$(MLX_DIR) -l$(MLX) -lX11 -lXext -L$(LIBFT_DIR) -l$(LIBFT) -lm

clean:
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

fclean:
	make -C $(LIBFT_DIR) fclean
	make -C $(MLX_DIR) clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
