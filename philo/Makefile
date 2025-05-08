# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/03 01:21:27 by ozamora-          #+#    #+#              #
#    Updated: 2025/05/08 23:15:20 by ozamora-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# DIRECTORIES
SRC_DIR			:= src/
INC_DIR			:= inc/
OBJ_DIR			:= obj/

# **************************************************************************** #
# PROJECT
NAME		:= philo

# **************************************************************************** #
# FILES
SRC_FILES	:= init log main routine_admin routine_philo time utils
INC_FILES	:= philosophers

# GENERAL FILES
SRCS	:= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS	:= $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
DEPS	:= $(OBJS:.o=.d)
INCS	:= $(addprefix $(INC_DIR), $(addsuffix .h, $(INC_FILES)))

# **************************************************************************** #
# COMPILER
CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror
CFLAGS	+= -MMD -MP
IFLAGS	:= -I$(INC_DIR)
LDFLAGS	:= -lpthread # Link with pthread library for threading functions (good practice)

# DEBUG MODE
BUILD_MODE_FILE := .build_mode
DEBUG			?= 0
VALGRIND		?= 0
VALGRIND_FLAGS	:= -s --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes
VALGRIND_FLAGS_DATARACE	:= -s --tool=helgrind

ifeq ($(DEBUG),1)
	CFLAGS += -g3 -fsanitize=thread 
	LDFLAGS += -fsanitize=thread
endif

ifeq ($(VALGRIND),1)
	CFLAGS += -g3
endif

# **************************************************************************** #
# COLOURS: BOLD RGBYW
BR	= \033[1;31m
BG	= \033[1;32m
BB	= \033[1;34m
BY	= \033[1;33m
BW	= \033[1;37m

# NO COLOR and CLEAR LINE
NC	= \033[0;39m
CL	= \033[2K

# **************************************************************************** #
# ESSENTIAL RULES
-include $(DEPS)

# Default rule to create the program
all: $(NAME)

# Rule to create the program
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(IFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@printf "%b" "$(CL) -> $(BW)[$(NAME)]:\t\t$(BG)Compilation success\t✅$(NC)\n"
	@echo "────────────────────────────────────────────────────────────$(BY)"
	@echo "▗▄▄▖ ▗▖ ▗▖▗▄▄▄▖▗▖    ▗▄▖  ▗▄▄▖ ▗▄▖ ▗▄▄▖ ▗▖ ▗▖▗▄▄▄▖▗▄▄▖  ▗▄▄▖";
	@echo "▐▌ ▐▌▐▌ ▐▌  █  ▐▌   ▐▌ ▐▌▐▌   ▐▌ ▐▌▐▌ ▐▌▐▌ ▐▌▐▌   ▐▌ ▐▌▐▌   ";
	@echo "▐▛▀▘ ▐▛▀▜▌  █  ▐▌   ▐▌ ▐▌ ▝▀▚▖▐▌ ▐▌▐▛▀▘ ▐▛▀▜▌▐▛▀▀▘▐▛▀▚▖ ▝▀▚▖";
	@echo "▐▌   ▐▌ ▐▌▗▄█▄▖▐▙▄▄▖▝▚▄▞▘▗▄▄▞▘▝▚▄▞▘▐▌   ▐▌ ▐▌▐▙▄▄▖▐▌ ▐▌▗▄▄▞▘";
	@echo "                                                by ozamora-"
	@echo "$(NC)────────────────────────────────────────────────────────────"

# Rule to compile object files from source files
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@printf "%b" "$(CL) -> $(BW)[$(NAME)]:\t\t$(NC)$<\r"
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

# Rule to clean generated files
clean:
	@rm -rf $(OBJ_DIR) $(BUILD_MODE_FILE)
	@printf "%b" "$(CL) -> $(BW)[$(NAME)]:\t\t$(BG)Object files cleaned\t❎$(NC)\n"

# Rule to clean generated files and the executable
fclean:
	@$(MAKE) clean > /dev/null
	@rm -f $(NAME) $(BONUS_NAME)
	@printf "%b" "$(CL) -> $(BW)[$(NAME)]:\t\t$(BG)Exe and objects cleaned\t❎$(NC)\n"

# Rule to recompile from zero
re: fclean all

.PHONY: all clean fclean re
.DEFAULT_GOAL := all