NAME	:= mandelbrot
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -O3 -ffast-math
MLX_DIR	:= ./MLX42
MLX_LIB := $(MLX_DIR)/build/libmlx42.a
LIBFT	:= libft/libft.a
HEADERS	:= -I ./include -I $(MLX_DIR)/include -I libft
LIBS	:= $(MLX_LIB) -ldl -lglfw -pthread -lm $(LIBFT)
SRCS	:= 	./src/alloc.c \
			./src/coloring.c \
			./src/cursors.c \
			./src/ft_strcmp.c \
			./src/ft_strtod.c \
			./src/index_to_coordinates.c \
			./src/init.c \
			./src/input_hooks.c \
			./src/main.c \
			./src/map_complex_plane.c \
			./src/resize.c \
			./src/the_formula.c \
			./src/zoom.c

OBJS	:= ${SRCS:.c=.o}

all: $(MLX_LIB) $(NAME)

$(NAME): $(OBJS) $(MLX_LIB) $(LIBFT)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

mlx: $(MLX_LIB)

$(LIBFT):
	make -C libft
	make -C libft clean

d: $(MLX_DIR)
	$(CC) $(SRCS) $(LIBS) -g $(HEADERS)

$(MLX_LIB): $(MLX_DIR)
	@cmake $(MLX_DIR)/ -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4

$(MLX_DIR):
	git clone https://github.com/codam-coding-college/MLX42.git

%.o: %.c ./include/fractal.h
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(MLX_DIR)
	@rm -f compile_commands.json

re: fclean all

.SECONDARY: $(OBJS)
.PHONY: all clean fclean re d mlx
