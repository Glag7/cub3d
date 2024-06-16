NAME = cub3d
LIB = minilibx/libmlx.a
LIBDIR = minilibx/
HDR = includes/

SRC_DIR = src/
OBJ_DIR = obj/
HDR_DIR = includes/

PARSING = parsing/
UTILS = utils/
COMMON = common/

COMP = cc
CFLAGS = -Wall -Wextra -I $(LIBDIR) -I $(HDR_DIR) -g #-Werror


SRC = main.c \
      $(COMMON)free_map.c \
      $(PARSING)parsing.c \
      $(PARSING)parse_buf.c \
      $(PARSING)load.c \
      $(PARSING)load_walls.c \
      $(PARSING)load_floorceil.c \
      $(PARSING)load_images.c \
      $(UTILS)ft_perror.c \
      $(UTILS)ft_memcpy.c \
      $(UTILS)ft_bzero.c

SRC_BONUS = skibidi

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)


DEL = @echo -n "\033[2K\r";
GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[0;34m
YELLOW = \033[0;33m
NOCOL = \033[m
BOLD = $(shell tput bold)
NOBOLD = $(shell tput sgr0)

MSG_CLEANING = "$(RED)$(BOLD)cleaning $(NAME)...$(NOBOLD)$(NOCOL)";
MSG_CLEANED = "$(RED)$(BOLD)cleaning done$(NOBOLD)$(NO_COLOR)";
MSG_COMPILING = "$(YELLOW)$(BOLD)compiling:$(NOBOLD)$(NOCOLOR) $(^)...";
MSG_READY = "$(BLUE)$(BOLD)$(NAME) ready$(NOBOLD)$(NOCOLOR)";


all : $(LIB) $(NAME)
	$(DEL)
	@echo $(MSG_READY)

bonus :
	$(DEL)
	@echo $(MSG_READY)

$(LIB) :
	@make -C $(LIBDIR) -s

$(NAME) : $(LIB) $(OBJ_DIR) $(OBJ_DIR)$(PARSING) $(OBJ_DIR)$(UTILS) $(OBJ_DIR)$(COMMON) $(addprefix $(OBJ_DIR), $(OBJ))
	@$(COMP) $(CFLAGS) $(addprefix $(OBJ_DIR), $(OBJ)) -Lminilibx -lmlx_Linux -lm -lz -lX11 -lXext -I $(HDR_DIR) -I $(LIBDIR) -o $(NAME)

$(OBJ_DIR)$(COMMON) : $(OBJ_DIR)
	@ mkdir -p $(OBJ_DIR)$(COMMON)

$(OBJ_DIR)$(PARSING) : $(OBJ_DIR)
	@ mkdir -p $(OBJ_DIR)$(PARSING)

$(OBJ_DIR)$(UTILS) : $(OBJ_DIR)
	@ mkdir -p $(OBJ_DIR)$(UTILS)

$(OBJ_DIR) :
	@ mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	$(DEL)
	@echo -n $(MSG_COMPILING)
	@ $(COMP) $(CFLAGS) -c $^ -o $@ -I $(HDR_DIR)

clean :
	@echo $(MSG_CLEANING)
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBDIR) -s clean
	@echo $(MSG_CLEANED)

fclean : clean
	@rm -f $(NAME)
	@rm -f $(LIB)

re : fclean all

.PHONY: all fclean clean re bonus
