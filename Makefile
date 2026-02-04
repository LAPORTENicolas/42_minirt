SHELL		:= bash

BUILD_DIR	:= ./build
SRC_DIR		:= ./srcs/
SRC_PATH 	:= $(SRC_DIR)
OBJ_DIR		:= $(BUILD_DIR)/objs/$(SRC_PATH)
DEP_DIR		:= $(BUILD_DIR)/deps/$(SRC_PATH)
SRCS		:= $(shell find $(SRC_PATH) -name '*.c')
SRCS		:= ./srcs/bmp_convert.c \
./srcs/build_pixels.c \
./srcs/build_pixels_utils.c \
./srcs/cam_move.c \
./srcs/cam_utils.c \
./srcs/color_palette.c \
./srcs/conversions.c \
./srcs/free_utils.c \
./srcs/generate_ray.c \
./srcs/init.c \
./srcs/keyboard.c \
./srcs/light.c \
./srcs/light_move.c \
./srcs/main.c \
./srcs/mouse_hooks.c \
./srcs/mouse_utils.c \
./srcs/quat_utils1.c \
./srcs/quat_utils2.c \
./srcs/render.c \
./srcs/texture.c \
./srcs/texture_utils.c \
./srcs/vec_utils1.c \
./srcs/vec_utils2.c \
./srcs/window.c \
./srcs/window_utils.c \
./srcs/obj/cone.c \
./srcs/obj/cone_checkerboard.c \
./srcs/obj/cone_data.c \
./srcs/obj/cone_texture.c \
./srcs/obj/cone_utils.c \
./srcs/obj/cylinder.c \
./srcs/obj/cylinder_checkboard.c \
./srcs/obj/cylinder_texture.c \
./srcs/obj/cylinder_utils.c \
./srcs/obj/obj_move.c \
./srcs/obj/obj_resize.c \
./srcs/obj/obj_rotate.c \
./srcs/obj/obj_select.c \
./srcs/obj/obj_utils.c \
./srcs/obj/plane.c \
./srcs/obj/plane_texture.c \
./srcs/obj/plane_utils.c \
./srcs/obj/restore_obj.c \
./srcs/obj/snapshot.c \
./srcs/obj/sphere.c \
./srcs/parsing/create_obj.c \
./srcs/parsing/create_texture.c \
./srcs/parsing/create_utils.c \
./srcs/parsing/min_obj.c \
./srcs/parsing/parsing.c \
./srcs/glass.c \
./srcs/parsing/vector_parsing.c
SRCS_BONUS		:= ./srcs/bmp_convert.c \
./srcs/build_pixels.c \
./srcs/build_pixels_utils.c \
./srcs/cam_move.c \
./srcs/cam_utils.c \
./srcs/color_palette.c \
./srcs/conversions.c \
./srcs/free_utils.c \
./srcs/generate_ray.c \
./srcs/init_bonus.c \
./srcs/keyboard.c \
./srcs/light.c \
./srcs/light_move.c \
./srcs/main_bonus.c \
./srcs/mouse_hooks.c \
./srcs/mouse_utils.c \
./srcs/quat_utils1.c \
./srcs/quat_utils2.c \
./srcs/render_bonus.c \
./srcs/texture_bonus.c \
./srcs/texture_utils.c \
./srcs/vec_utils1.c \
./srcs/vec_utils2.c \
./srcs/window_bonus.c \
./srcs/window_utils.c \
./srcs/obj/cone.c \
./srcs/obj/cone_checkerboard.c \
./srcs/obj/cone_data.c \
./srcs/obj/cone_texture_bonus.c \
./srcs/obj/cone_utils.c \
./srcs/obj/cylinder.c \
./srcs/obj/cylinder_checkboard.c \
./srcs/obj/cylinder_texture_bonus.c \
./srcs/obj/cylinder_utils.c \
./srcs/obj/obj_move.c \
./srcs/obj/obj_resize.c \
./srcs/obj/obj_rotate.c \
./srcs/obj/obj_select.c \
./srcs/obj/obj_utils.c \
./srcs/obj/plane.c \
./srcs/obj/plane_texture_bonus.c \
./srcs/obj/plane_utils.c \
./srcs/obj/restore_obj.c \
./srcs/obj/snapshot.c \
./srcs/obj/sphere_bonus.c \
./srcs/parsing/create_obj.c \
./srcs/parsing/create_texture.c \
./srcs/parsing/create_utils.c \
./srcs/parsing/min_obj.c \
./srcs/parsing/parsing.c \
./srcs/glass.c \
./srcs/parsing/vector_parsing.c \
./srcs/threads_bonus.c 
ifeq ($(BONUS),1)
	SRCS := $(SRCS_BONUS)
endif
OBJS		:= $(patsubst $(SRC_PATH)%,$(OBJ_DIR)%, $(SRCS:.c=.o))
DEPS		:= $(patsubst $(SRC_PATH)%,$(DEP_DIR)%, $(SRCS:.c=.d))

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -MMD -g
LDLIBS		:= -L./lib/mlx/ -lmlx_Linux -lm -lX11 -lXext -L./lib/libft -lft -L./lib/gnl -lgnl
TARGET		:= miniRT

all: gnl mlx libft ${TARGET}

doc:
	doxygen minirt_doc

debug:
	@echo $(SRCS)
	@echo $(OBJS)
	@echo $(DEPS)

gnl:
	make -C ./lib/gnl

mlx:
	make -C ./lib/mlx

libft:
	make -C ./lib/libft

bonus:
	@$(MAKE) BONUS=1 all

${TARGET}: ${OBJS} libft mlx
	@if ${CC} ${OBJS} -o ${TARGET} ${LDLIBS} >/dev/null 2>&1; then \
		printf "\n\e[38;2;0;229;232m Compilation \e[0m $(TARGET) \e[38;2;84;213;52m	\e[75G OK\n\e[0m"; \
	else \
		printf "\n\e[38;2;0;229;232m Compilation \e[0m $(TARGET) \e[38;2;213;84;52m	\e[75G KO\n\e[0m"; \
		${CC} ${OBJS} -o ${TARGET} ${LDLIBS}>/dev/null; \
	fi

$(OBJ_DIR)%.o: $(SRC_PATH)%.c
	@mkdir -p $(dir $@) >/dev/null
	@mkdir -p $(dir $(DEP_DIR)$*) >/dev/null
	@if ${CC} ${CFLAGS} -MF $(DEP_DIR)$*.d -c $< -o $@ >/dev/null 2>err_makefile.log; then \
		printf "\e[38;2;0;229;232m Compilation \e[0m $*.c \e[38;2;84;213;52m	\e[75G OK\n\e[0m"; \
	else \
		printf "\e[38;2;0;229;232m Compilation \e[0m $*.c \e[38;2;213;84;52m	\e[75G KO\n\e[0m"; \
		${CC} ${CFLAGS} -MF $(DEP_DIR)$*.d -c $< -o $@ >/dev/null; \
	fi

clean:
	@rm -rf $(BUILD_DIR)
	@rm -rf err_makefile.log
	@rm -rf doc/

fclean: clean
	@rm -rf $(TARGET)
	make -C ./lib/mlx clean
	make -C ./lib/libft fclean
	make -C ./lib/gnl fclean

re: fclean all

-include $(DEPS)

.PHONY: mlx libft doc bonus
