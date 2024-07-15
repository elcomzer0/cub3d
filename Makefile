# Target programs
NAME = fdf

# Color codes
RED = \033[1;7;31m
GREEN = \033[1;7;32m
YELLOW = \033[1;3;33m
BLUE = \033[0;34m
MAGENTA = \033[1;3;35m
CYAN = \033[0;36m
RESET = \033[0m

# Compiler and flags
CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf

# Libraries and Includes
# LIBRARIES = -lm -lX11 -lXext -lmlx_Linux -L$(MINILIBX_DIRERECTORY)
INCLUDES = -I(HEADER_DIR) -I$(MINILIBX_HEADERS)

# Library paths

# MINILIBX DIRECTORY AND HEADERS


# Header
HEADER_LIST = ./includes/cub3d.h
HEADER_DIR = ./
HEADER = &(addprefix $(HEADER_LIST), $(HEADER_DIR))

SOURCES_DIR = ./sources/
SOURCES_LIST = main.c \
	image.c \
	init.c \
	menu.c \
	move.c \
	raycaster.c \
	read.c \
	render.c \
	utils.c

SOURCES = $(addprefix $(SOURCES_LIST), $(SOURCES_DIR))
OBJECTS_DIR = ./objects/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS = $(addprefix $(OBJECTS_LIST), $(OBJECTS_DIR))

.PHONY: all clean fclean re

#Build all target program
all: $(NAME)

# Build cub3d. MINILIBX needs to be included
$(NAME): $(OBJECTS) $(OBJECTS_DIR)
	@echo "$(YELLOW)Building (BLUE) $@$(YELLOW) program...$(RESET)\n"
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJECTS) -o $@
	@echo "$(GREEN)Done!$(RESET)\n"

# Create folder objects dir
$(OBJECTS_DIR):
	@mkdir -p $(OBJECTS_DIR)
	@echo "$(GREEN)Create objects folder$(RESET)\n"

# MINILIBX


# This is a target that delets all objects files
clean:
	@echo "$(RED)Deleting objects files...$(RESET)\n"
	#MINILIBX 
	@$(RM) $(OBJECTS_DIR)

# Clean built programs
fclean:
	@echo "$(RED) Cleaning object files and built programs...$(RESET)\n"
	# MINILIBX
	@$(RM) -f $(NAME)
	@echo "$(NAME): $(RED)Deleted$(RESET)\n"

# Rebuild all
re:
	@$(MAKE) fclean
	@$(MAKE) all
	@echo "$(GREEN)DELETED AND RECOMPILED!$(RESET)\n"
