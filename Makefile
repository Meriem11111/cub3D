NAME = cub3D
CC = cc 
CFLAGS = -Wall -Werror -Wextra  -fsanitize=address
src = main.c utils.c ./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c

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
		@ $(CC) $(CFLAGS) $(OBJ) -o $(NAME)
		@echo $(GREEN0) ✨ Compilation done ✨ 
clean :
		@echo $(RED) cleaning.. 
		@rm -rf $(OBJ)
fclean : clean
		@rm -rf $(NAME)
		@echo $(PURPLE) ✨ Done ✨ 
re:	fclean	all
.SILENT : $(OBJ)