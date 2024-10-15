NAME = cub3d
LIB = minilibx/libmlx.a
LIBDIR = minilibx/
HDR = includes/

SRC_DIR = src/
OBJ_DIR = obj/
SRC_BONUS_DIR = src_bonus/
OBJ_BONUS_DIR = obj_bonus/
HDR_DIR = includes/
HDR_BONUS_DIR = includes_bonus/

PARSING = parsing/
UTILS = utils/
COMMON = common/
HOOKS = hooks/
RENDER = render/
MOVE = move/
MENU = menu/

COMP = cc
CFLAGS = -Wall -Wextra -I $(LIBDIR) -g #-Werror


SRC = main.c \
      $(COMMON)free_map.c \
      $(COMMON)manage_mlx.c \
      $(COMMON)manage_mini.c \
      $(COMMON)manage_settings.c \
      $(COMMON)diameter.c \
      $(PARSING)parsing.c \
      $(PARSING)parse_buf.c \
      $(PARSING)load.c \
      $(PARSING)load_walls.c \
      $(PARSING)load_floorceil.c \
      $(PARSING)load_images.c \
      $(PARSING)get_data.c \
      $(PARSING)read_images.c \
      $(PARSING)fill_map.c \
      $(PARSING)check_map.c \
      $(UTILS)ft_perror.c \
      $(UTILS)ft_memcpy.c \
      $(UTILS)ft_bzero.c \
      $(HOOKS)keys.c \
      $(HOOKS)win.c \
      $(RENDER)loop.c \
      $(RENDER)raycast.c \
      $(RENDER)move.c \
      $(RENDER)drawv.c \
      $(RENDER)minimap.c

SRC_BONUS = main.c \
      $(COMMON)free_map.c \
      $(COMMON)manage_mlx.c \
      $(COMMON)manage_mini.c \
      $(COMMON)manage_settings.c \
      $(COMMON)settings_file.c \
      $(COMMON)diameter.c \
      $(PARSING)parsing.c \
      $(PARSING)parse_buf.c \
      $(PARSING)load.c \
      $(PARSING)load_walls.c \
      $(PARSING)load_floorceil.c \
      $(PARSING)load_flat.c \
      $(PARSING)load_gun.c \
      $(PARSING)load_images.c \
      $(PARSING)load_bmp.c \
      $(PARSING)get_data.c \
      $(PARSING)resize_images.c \
      $(PARSING)fill_map.c \
      $(PARSING)check_map.c \
      $(UTILS)ft_perror.c \
      $(UTILS)ft_memcpy.c \
      $(UTILS)ft_bzero.c \
      $(HOOKS)keys.c \
      $(HOOKS)mouse.c \
      $(HOOKS)win.c \
      $(HOOKS)keys_keypad.c \
      $(RENDER)loop.c \
      $(RENDER)raycast.c \
      $(RENDER)flat.c \
      $(RENDER)floor.c \
      $(RENDER)drawv.c \
      $(RENDER)draw_flat.c \
      $(RENDER)draw_hud.c \
      $(RENDER)minimap.c \
      $(RENDER)manage_menu.c \
      $(MOVE)move.c \
      $(MOVE)move_xy.c \
      $(MOVE)move_angle.c \
      $(MOVE)shoot.c \
      $(MOVE)doors.c \
      $(MENU)buttons.c \
      $(MENU)draw_menu.c \
      $(MENU)init_menu.c \
      $(MENU)init_menu_buttons.c \
      $(MENU)menu_utils.c \
      $(MENU)build_menu.c \
      $(MENU)slider.c \
      $(MENU)textfield.c \
      $(MENU)build_windows.c \
      $(MENU)manage_background.c \
      $(MENU)draw_rectangle.c \
      $(MENU)draw_string.c \
      $(MENU)save_settings.c \
      $(MENU)update_interactions.c

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

bonus : $(LIB) $(OBJ_BONUS_DIR) $(OBJ_BONUS_DIR)$(MENU) $(OBJ_BONUS_DIR)$(MOVE) $(OBJ_BONUS_DIR)$(RENDER) $(OBJ_BONUS_DIR)$(HOOKS) $(OBJ_BONUS_DIR)$(PARSING) $(OBJ_BONUS_DIR)$(UTILS) $(OBJ_BONUS_DIR)$(COMMON) $(addprefix $(OBJ_BONUS_DIR), $(OBJ_BONUS))
	@$(COMP) $(CFLAGS) $(addprefix $(OBJ_BONUS_DIR), $(OBJ_BONUS)) -Lminilibx -lmlx_Linux -lm -lz -lX11 -lXext -I $(HDR_BONUS_DIR) -I $(LIBDIR) -o $(NAME)
	$(DEL)
	@echo $(MSG_READY)

$(LIB) :
	@make -C $(LIBDIR) -s

$(NAME) : $(LIB) $(OBJ_DIR) $(OBJ_DIR)$(RENDER) $(OBJ_DIR)$(HOOKS) $(OBJ_DIR)$(PARSING) $(OBJ_DIR)$(UTILS) $(OBJ_DIR)$(COMMON) $(addprefix $(OBJ_DIR), $(OBJ))
	@$(COMP) $(CFLAGS) $(addprefix $(OBJ_DIR), $(OBJ)) -Lminilibx -lmlx_Linux -lm -lz -lX11 -lXext -I $(HDR_DIR) -I $(LIBDIR) -o $(NAME)


$(OBJ_DIR)$(COMMON) : $(OBJ_DIR)
	@ mkdir -p $(OBJ_DIR)$(COMMON)

$(OBJ_DIR)$(PARSING) : $(OBJ_DIR)
	@ mkdir -p $(OBJ_DIR)$(PARSING)

$(OBJ_DIR)$(HOOKS) : $(OBJ_DIR)
	@ mkdir -p $(OBJ_DIR)$(HOOKS)

$(OBJ_DIR)$(UTILS) : $(OBJ_DIR)
	@ mkdir -p $(OBJ_DIR)$(UTILS)

$(OBJ_DIR)$(RENDER) : $(OBJ_DIR)
	@ mkdir -p $(OBJ_DIR)$(RENDER)

$(OBJ_BONUS_DIR)$(COMMON) : $(OBJ_BONUS_DIR)
	@ mkdir -p $(OBJ_BONUS_DIR)$(COMMON)

$(OBJ_BONUS_DIR)$(PARSING) : $(OBJ_BONUS_DIR)
	@ mkdir -p $(OBJ_BONUS_DIR)$(PARSING)

$(OBJ_BONUS_DIR)$(HOOKS) : $(OBJ_BONUS_DIR)
	@ mkdir -p $(OBJ_BONUS_DIR)$(HOOKS)

$(OBJ_BONUS_DIR)$(UTILS) : $(OBJ_BONUS_DIR)
	@ mkdir -p $(OBJ_BONUS_DIR)$(UTILS)

$(OBJ_BONUS_DIR)$(RENDER) : $(OBJ_BONUS_DIR)
	@ mkdir -p $(OBJ_BONUS_DIR)$(RENDER)

$(OBJ_BONUS_DIR)$(MOVE) : $(OBJ_BONUS_DIR)
	@ mkdir -p $(OBJ_BONUS_DIR)$(MOVE)

$(OBJ_BONUS_DIR)$(MENU) : $(OBJ_BONUS_DIR)
	@ mkdir -p $(OBJ_BONUS_DIR)$(MENU)

$(OBJ_DIR) :
	@ mkdir -p $(OBJ_DIR)

$(OBJ_BONUS_DIR) :
	@ mkdir -p $(OBJ_BONUS_DIR)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	$(DEL)
	@echo -n $(MSG_COMPILING)
	@ $(COMP) $(CFLAGS) -c $^ -o $@ -I $(HDR_DIR)

$(OBJ_BONUS_DIR)%.o : $(SRC_BONUS_DIR)%.c
	$(DEL)
	@echo -n $(MSG_COMPILING)
	@$(COMP) $(CFLAGS) -c $^ -o $@ -I $(HDR_BONUS_DIR)

cleancub :
	@echo $(MSG_CLEANING)
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_BONUS_DIR)
	@echo $(MSG_CLEANED)

clean :
	@echo $(MSG_CLEANING)
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_BONUS_DIR)
	@make -C $(LIBDIR) -s clean
	@echo $(MSG_CLEANED)

fclean : clean
	@rm -f $(NAME)
	@rm -f $(LIB)

re : fclean all

recub : cleancub all

recubonus : cleancub bonus

.PHONY: all fclean clean re bonus cleancub recub recubonus
