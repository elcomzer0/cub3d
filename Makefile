# Target programs
NAME = cub3d

# Color codes
RED = \033[1;7;31m
GREEN = \033[1;7;32m
YELLOW = \033[1;7;33m
BLUE = \033[1;7;34m
MAGENTA = \033[1;3;35m
CYAN = \033[0;36m
RESET = \033[0m

# Compiler and flags
CC = cc
CFLAGS = -g -Wall -Werror -Wextra
RM = rm -rf

# Libraries and Includes
LIBRARIES = -lm -lmlx -lX11 -lXext 
INCLUDES = -I$(HEADER_DIR)

# Library paths

# MINILIBX DIRECTORY AND HEADERS


# Header
HEADER_LIST = ./includes/cub3d.h
HEADER_DIR = ./
HEADER = $(addprefix $(HEADER_DIR), $(HEADER_LIST))

SOURCES_DIR = ./sources/
SOURCES_LIST = main.c \
	utils.c \
	init.c \
	free.c \
	draw.c \
	draw_elements.c \
	menu.c \
	read.c \
	raycaster.c \
	raycaster_2.c \
	render.c \
	render_utils.c \
	shader.c \
	move.c


SOURCES = $(addprefix $(SOURCES_DIR), $(SOURCES_LIST))
OBJECTS_DIR = objects/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS = $(addprefix $(OBJECTS_DIR), $(OBJECTS_LIST))

.PHONY: all clean fclean re

#Build all target program
all: $(NAME)

# Build cub3d. MINILIBX needs to be included
$(NAME): $(OBJECTS_DIR) $(OBJECTS)
	@echo "$(YELLOW) Building $(BLUE) CUB3D $(YELLOW) program... $(RESET)\n"
	@$(CC) $(CFLAGS) $(LIBRARIES) $(INCLUDES) $(OBJECTS) -o $@
	@echo "$(GREEN) Done $(RESET)\n"

# Create folder objects dir
$(OBJECTS_DIR):
	@mkdir -p $(OBJECTS_DIR)
	@echo "$(GREEN) Create objects folder $(RESET)\n"

# ADD OBJECTS FILES

$(OBJECTS_DIR)%.o: $(SOURCES_DIR)%.c $(HEADER)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(GREEN) OBJECTS ADDED $(RESET)\n"

# This is a target that delets all objects files
clean:
	@echo "$(RED) Deleting objects files... $(RESET)\n"
 
	@$(RM) $(OBJECTS_DIR)

# Clean built programs
fclean:
	@echo "$(RED) Cleaning built program... $(RESET)\n"

	@$(RM) -f $(NAME)
	@echo "$(NAME): $(RED) Deleted $(RESET)\n"

# Rebuild all
re:
	@$(MAKE) fclean
	@$(MAKE) all
	@echo "$(GREEN) DELETED AND RECOMPILED $(RESET)\n"

# Debug target for cub3d with gdb
debug: CFLAGS += -g
debug: re
	@echo "$(GREEN) Starting gdb for $(NAME)... $(RESET)"
	@gdb --args ./$(NAME) maps/sq_map_50x50.cub

# Valgrind target to check memory leaks
valgrind: $(NAME)
	@echo "$(YELLOW) Running Valgrind... $(RESET)\n"
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)


