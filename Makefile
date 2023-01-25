# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mkootstr <mkootstr@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/01/24 16:40:30 by mkootstr      #+#    #+#                  #
#    Updated: 2023/01/25 04:41:30 by mkootstr      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = so_long
MLX = MLX42/libmlx42.a
LIBFT = Libft/libft.a
HEADER = so_long.h

OBJ =		src/free/error.c\
		 	src/free/free.c\
			src/main/keyhooks.c\
			src/main/main.c\
			src/main/move.c\
			src/main/so_long.c\
			src/parser/check_map.c\
			src/parser/check_path.c\
			src/parser/parse_map.c\
			src/parser/parse_utils.c\
			src/parser/struct_utils.c

CFLAGS = -Wall -Wextra -Werror # -g -fsanitize=address

all: $(MLX) $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $@ $(OBJ) $(LIBFT) $(MLX) -I include -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit

$(MLX):
	make -C ./MLX42

$(LIBFT):
	make -C ./Libft

clean:
	make clean -C ./MLX42
	make clean -C ./Libft

fclean: clean
	rm -f $(MLX)
	rm -f $(LIBFT)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
