NAME = cub3d
LIB = minilibx/libmlx.a
LIBDIR = minilibx/
HDR = includes/

SRC_DIR = src/
OBJ_DIR = obj/
HDR_DIR = includes/

COMP = cc
CFLAGS = -Wall -Wextra -g #-Werror


SRC = main.c 

SRC_BONUS = skibidi

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)

all : $(LIB) $(NAME)

bonus :
	echo no

$(LIB) :
	@make -C $(LIBDIR) -s

$(NAME) : $(LIB) $(OBJ_DIR) $(addprefix $(OBJ_DIR), $(OBJ))
	@$(COMP) $(CFLAGS) $(addprefix $(OBJ_DIR), $(OBJ)) -Lminilibx -lmlx_Linux -lm -lz -lX11 -lXext -I $(HDR_DIR) -o $(NAME)
	@echo no push

$(OBJ_DIR) :
	@ mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@ $(COMP) $(CFLAGS) -c $^ -o $@ -I $(HDR_DIR)

clean :
	@rm -f $(OBJ) $(OBJ_BONUS)
	@make -C $(LIBDIR) -s

fclean : clean
	@rm -f $(NAME)
	@rm -f $(LIB)

re : fclean all

.PHONY: all fclean clean re bonus
