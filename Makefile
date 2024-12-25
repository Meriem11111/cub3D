NAME = cub3D
CC = cc 
CFLAGS = -Wall -Werror -Wextra #-fsanitize=address
src = main.c utils.c parse_textures.c check_errors.c moves.c free.c ft_split.c ./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c
MLX = -lmlx_Linux -lXext -lX11 -lm

OBJ = $(src:.c=.o)

RED = "\033[0;31m"
GREEN0 = "\033[32m"
RED = "\033[0;31m"
BLUE = "\033[34m"
YELLOW = \033[0;33m
PURPLE = "\033[0;35m"
RESET = \033[0m

all : $(NAME)

$(NAME) : $(OBJ)
		@ $(CC) $(CFLAGS) $(OBJ) $(MLX) -o $(NAME)
		@echo $(GREEN0) ✨ Compilation done ✨ 
clean :
		@echo $(RED) cleaning.. 
		@rm -rf $(OBJ)
fclean : clean
		@rm -rf $(NAME)
		@echo $(PURPLE) ✨ Done ✨ 
re:	fclean	all
.SILENT : $(OBJ)