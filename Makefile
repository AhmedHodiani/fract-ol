NAME			= $(BUILD_PATH)/fractol
CC				= cc
CFLAGS			= -Wall -Wextra -Werror
BUILD_PATH		?= ./build

DEPENDENCIES		= libft libftprintf
DEPENDENCIES_DIR	= ./dependencies
DEPENDENCIES_FLAGS	= $(foreach lib,$(DEPENDENCIES),-L$(BUILD_PATH)/$(lib)) \
						$(foreach lib,$(patsubst lib%,%, $(DEPENDENCIES)),-l$(lib)) \
						-lmlx -lXext -lX11 -lm
INCLUDE_FLAGS		= -Iinclude $(foreach lib,$(DEPENDENCIES),-Iinclude/$(lib))

SRCS			=	src/main.c \
					src/hooks.c \
					src/fractol.c \
					src/fractol_utils.c \
					src/complex/basic.c \
					src/complex/power.c \
					src/utils.c
OBJS			= $(SRCS:src/%.c=$(BUILD_PATH)/obj/%.o)
HEADERS			= include/fractol.h

all: $(NAME)

$(NAME): $(OBJS) $(foreach lib,$(DEPENDENCIES),$(BUILD_PATH)/$(lib)/$(lib).a) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJS) $(DEPENDENCIES_FLAGS) $(INCLUDE_FLAGS) -o $(NAME)

$(foreach lib,$(DEPENDENCIES),$(BUILD_PATH)/$(lib)/$(lib).a):
	$(MAKE) -C $(DEPENDENCIES_DIR)/$(basename $(@F)) BUILD_PATH=../../$(BUILD_PATH)/$(basename $(@F)) all

$(BUILD_PATH)/obj/%.o: src/%.c $(HEADERS)
	@mkdir -p $(BUILD_PATH)/obj/complex
	$(CC) $(CFLAGS) $(DEPENDENCIES_FLAGS) $(INCLUDE_FLAGS) -c $< -o $@

clean:
	@rm -rf $(BUILD_PATH)/obj
	@rm -rf $(BUILD_PATH)/lib*/obj

copy_include:
	@for lib in $(DEPENDENCIES); do \
		cp $(DEPENDENCIES_DIR)/$$lib/include/* include/; \
		echo "# include \"$$lib.h\"" >> include/fractol.h; \
	done

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(BUILD_PATH)

re: fclean all

.PHONY: all clean re fclean copy_include
