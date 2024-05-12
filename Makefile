NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror

PARSE_DIR = parsing

SRCS = main.c get_next_line.c player_utils.c set_up_images.c raycast.c raycast_utils.c general_utils.c \
		$(addprefix $(PARSE_DIR)/, get_map.c get_map_utils.c map_utils2.c parse.c parse_utils.c parse_colors.c \
			parse_colors_utils.c parse_textures.c map_dfs.c parse_map.c)

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

#MAC_OS
$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) -g3 -fsanitize=address -Lmlx -lmlx -framework OpenGL -framework AppKit $(LIBFT)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

#LINUX
#$(NAME): $(OBJS)
#	$(CC) $(OBJS) -o $(NAME) -Lmlx-linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz $(LIBFT)

#%.o: %.c
#	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME) $(NAME)

re: fclean all

.PHONY: all clean fclean re

