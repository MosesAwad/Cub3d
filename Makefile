NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS_DIR = mandatory/srcs
SRCS = $(addprefix $(SRCS_DIR)/, main.c player_utils.c raycast.c raycast_utils.c general_utils.c)

PARSE_DIR = mandatory/parsing
PARSE = $(addprefix $(PARSE_DIR)/, get_map.c get_map_utils.c map_utils2.c parse.c parse_utils.c parse_colors.c \
			parse_colors_utils.c parse_textures.c map_dfs.c parse_map.c get_next_line.c)

SRCS_OBJS = $(SRCS:.c=.o)
PARSE_OBJS = $(PARSE:.c=.o)

LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

#MAC_OS
$(NAME): $(SRCS_OBJS) $(PARSE_OBJS)
	$(CC) $(SRCS_OBJS) $(PARSE_OBJS) -o $(NAME) -g3 -fsanitize=address -Lmlx -lmlx -framework OpenGL -framework AppKit $(LIBFT)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

#LINUX
#$(NAME): $(SRCS_OBJS) $(PARSE_OBJS)
#	$(CC) $(SRCS_OBJS) $(PARSE_OBJS) -o $(NAME) -Lmlx-linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz $(LIBFT)

#%.o: %.c
#	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(SRCS_OBJS) $(PARSE_OBJS)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME) $(NAME)

re: fclean all

.PHONY: all clean fclean re

