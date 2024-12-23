NAME = fractol
CFLAGS = -Wall -Wextra -Werror -g3 $(INCLUDES_D)
MAKEFLAGS += --no-print-directory

SRC =	main.c complex.c colors.c fractal.c input.c formula.c

OBJ = $(SRC:.c=.o)

OBJ_D = obj/
SRCS_D = src/
LOG_D = log/
INCLUDES_D = -Iincludes/ -Ilibft/includes/

OBJ := $(addprefix $(OBJ_D), $(OBJ))
SRCS := $(addprefix $(SRCS_D), $(SRCS))

# colors
RED 	= \033[31m
GREEN 	= \033[32m
YELLOW 	= \033[33m
RESET 	= \033[0m
BLUE 	= \033[34m

RM = rm -fr

ARGS = 1

all:
	$(MAKE) libft
	$(MAKE) $(NAME)

.PHONY: libft
libft:
	$(MAKE) -C libft

$(NAME): $(OBJ)
	echo "$(YELLOW)[MAKE]: mlx$(RESET)"
	$(MAKE) -C mlx_linux
	echo "$(YELLOW)[MAKE]: libft$(RESET)"
	$(CC) $(CFLAGS) $(OBJ) libft/bin/libft.a -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
	echo "$(YELLOW)[CREATING EXE]: $@$(RESET)"
	echo "$(GREEN)[SUCCESS]: $@$(RESET)"

$(OBJ_D)%.o : $(SRCS_D)%.c libft/bin/libft.a includes/fractol.h | $(OBJ_D)
	echo "$(BLUE)[COMPILING]: $@$(RESET)"
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

.PHONY: clean
clean:
	$(MAKE) clean -C mlx_linux
	$(MAKE) clean -C ./libft
	$(MAKE) clog
	$(RM) $(OBJ_D)
	echo "$(RED)[CLEAN]: obj files$(RESET)"

.PHONY: fclean
fclean: clean
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME)
	$(RM) $(NAME)
	echo "$(RED)[CLEAN]: binaries$(RESET)"

.PHONY: clog
clog:
	$(RM) $(LOG_D)
	echo "$(RED)[CLEAN]: log$(RESET)"

.PHONY: re
re:
	$(MAKE) fclean
	$(MAKE) all

# Create directories
$(OBJ_D):
	echo "$(YELLOW)[CREATING]: $(OBJ_D)$(RESET)"
	mkdir -p $(OBJ_D)

$(LOG_D):
	echo "$(YELLOW)[CREATING]: $(LOG_D)$(RESET)"
	mkdir -p $(LOG_D)

.PHONY: debug
debug: all $(LOG_D)
	./$(NAME) $(ARGS) > $(LOG_D)$(shell date --iso=seconds).log
	cat $(LOG_D)$(shell date --iso=seconds).log
	echo "$(BLUE)[SAVED]: $(LOG_D)$(shell date --iso=seconds).log"

.SILENT: