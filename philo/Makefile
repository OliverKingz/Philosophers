# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/03 01:21:27 by ozamora-          #+#    #+#              #
#    Updated: 2025/04/08 18:13:05 by ozamora-         ###   ########.fr        #
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
SRC_FILES	:= main
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
CFLAGS	+= -D_GNU_SOURCE # Define GNU_SOURCE for usleep function
IFLAGS	:= -I$(INC_DIR)
LDFLAGS	:= -lpthread # Link with pthread library for threading functions
LDFLAGS	+= -lm       # Link with math library for mathematical functions

# DEBUG MODE
BUILD_MODE_FILE := .build_mode
DEBUG			?= 0
VALGRIND		?= 0
VALGRIND_FLAGS	:= -s --tool=memcheck --leak-check=full --show-leak-kinds=all \
		--track-origins=yes --trace-children=yes --track-fds=yes

ifeq ($(DEBUG),1)
	CFLAGS += -g3 -fsanitize=address
	LDFLAGS += -fsanitize=address
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

# **************************************************************************** #
# BONUS SECTION (GROUPED FOR EASY REMOVAL)
# Comment or delete this section if you don't need bonus functionality.

# BONUS DIRECTORIES
SRC_BONUS_DIR	:= src/bonus/
INC_BONUS_DIR	:= inc/bonus/
OBJ_BONUS_DIR	:= obj/bonus/

# BONUS FILES
BONUS_NAME	:= philo_bonus
SRC_BONUS_FILES	:= main_bonus
INC_BONUS_FILES	:= philosophers_bonus

# BONUS GENERAL FILES
SRCS_BONUS	:= $(addprefix $(SRC_BONUS_DIR), $(addsuffix .c, $(SRC_BONUS_FILES)))
OBJS_BONUS	:= $(SRCS_BONUS:$(SRC_BONUS_DIR)%.c=$(OBJ_BONUS_DIR)%.o)
DEPS_BONUS	:= $(OBJS_BONUS:.o=.d)
INCS_BONUS	:= $(addprefix $(INC_BONUS_DIR), $(addsuffix .h, $(INC_BONUS_FILES)))

# BONUS COMPILER FLAGS
IFLAGS_BONUS:= -I$(INC_BONUS_DIR)

# BONUS RULES
bonus: $(BONUS_NAME)
$(BONUS_NAME): $(OBJS_BONUS)
	@$(CC) $(CFLAGS) $(IFLAGS_BONUS) $(OBJS_BONUS) $(LDFLAGS) -o $(NAME) 
	@touch $(BONUS_NAME)
	@printf "%b" "$(CL) -> $(BW)[$(NAME)]:\t$(BG)Bonus compiled\t\t✅$(NC)\n"

$(OBJ_BONUS_DIR):
	@mkdir -p $(OBJ_BONUS_DIR)
$(OBJ_BONUS_DIR)%.o: $(SRC_BONUS_DIR)%.c | $(OBJ_BONUS_DIR)
	@mkdir -p $(dir $@)
	@printf "%b" "$(CL) -> $(BW)[$(NAME)]:\t$(NC)$<\r"
	@$(CC) $(CFLAGS) $(IFLAGS_BONUS) -c $< -o $@

# **************************************************************************** #
# NORM AND DEBUG RULES

# Rule to compile with debug flags
debug:
	@if [ ! -f $(BUILD_MODE_FILE) ] || ! grep -q "DEBUG=1" $(BUILD_MODE_FILE); then \
		$(MAKE) fclean -s; \
	fi
	@echo "DEBUG=1" > $(BUILD_MODE_FILE)
	@$(MAKE) DEBUG=1 -s
	@echo " -> $(BW)[Debug]:\t$(BB)Debug mode enabled\t🟦$(NC)"
	-@if [ ! -z "$(ARGS)" ]; then ./$(NAME) $(ARGS); fi

# Rule to compile with valgrind debug flags
valgrind:
	@if [ ! -f $(BUILD_MODE_FILE) ] || ! grep -q "VALGRIND=1" $(BUILD_MODE_FILE); then \
		$(MAKE) fclean -s; \
	fi
	@echo "VALGRIND=1" > $(BUILD_MODE_FILE)
	@$(MAKE) VALGRIND=1 -s
	@echo " -> $(BW)[Valgrind]:\t$(BB)Valgrind mode enabled\t🟦$(NC)"
	-@if [ ! -z "$(ARGS)" ]; then \
		valgrind $(VALGRIND_FLAGS) ./$(NAME) $(ARGS); \
	fi

# **************************************************************************** #
# ADDITIONAL RULES

# Rule to show help
help:
	@echo "$(BY)Available targets:$(NC)"
	@echo "  $(BB)all$(NC)       - Build the project"
	@echo "  $(BB)clean$(NC)     - Remove object files"
	@echo "  $(BB)fclean$(NC)    - Remove object files and executable"
	@echo "  $(BB)re$(NC)        - Rebuild the project from scratch"
	@echo "  $(BB)bonus$(NC)     - Build the bonus part of the project"
	@echo "  $(BB)debug$(NC)     - Build the project with debug flags"
	@echo "  $(BB)valgrind$(NC)  - Build the project with valgrind flags"
	@echo "  $(BB)help$(NC)      - Show this help message"
	@echo "  $(BB)show$(NC)      - Show compilation and linking commands"
	@echo "  $(BB)info$(NC)      - Show all variables being used"

# Rule to show compilation and linking commands
show:
	@echo "$(BY)Compilation command:$(NC)\t"\
		"$(CC) $(CFLAGS) $(IFLAGS) -c $(SRC_DIR)$(NAME).c -o $(OBJ_DIR)$(NAME).o"
	@echo "$(BY)Linking command:$(NC)\t"\
		"$(CC) $(CFLAGS) $(IFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)"
	@echo "$(BY)Cleaning command:$(NC)\t rm -rf $(NAME) $(BONUS_NAME)"\
		"$(OBJ_DIR)*.o $(OBJ_DIR)*.d $(OBJ_DIR) $(BUILD_MODE_FILE)"

# Rule to show all variables being used
info:
	@echo "$(BY)\nozamora's Project:$(NC)"
	@echo "$(BB)NAME: $(NC)$(NAME)"
	@echo "$(BB)BONUS_NAME: $(NC)$(BONUS_NAME)"
	@echo "$(BY)\nCompiler:$(NC)"
	@echo "$(BB)CC: $(NC)$(CC)"
	@echo "$(BB)CFLAGS: $(NC)$(CFLAGS)"
	@echo "$(BB)IFLAGS: $(NC)$(IFLAGS)"
	@echo "$(BB)LDFLAGS: $(NC)$(LDFLAGS)"
	@echo "$(BY)\nDirectories:$(NC)"
	@echo "$(BB)SRC_DIR: $(NC)$(SRC_DIR)"
	@echo "$(BB)INC_DIR: $(NC)$(INC_DIR)"
	@echo "$(BB)OBJ_DIR: $(NC)$(OBJ_DIR)"
	@echo "$(BY)\nFiles:$(NC)"
	@echo "$(BB)NAME: $(NC)$(NAME)"
	@echo "$(BB)SRC_FILES: $(NC)$(SRC_FILES)"
	@echo "$(BB)INC_FILES: $(NC)$(INC_FILES)"
	@echo "$(BB)SRCS: $(NC)$(SRCS)"
	@echo "$(BB)OBJS: $(NC)$(OBJS)"
	@echo "$(BB)DEPS: $(NC)$(DEPS)"
	@echo "$(BB)INCS: $(NC)$(INCS)"
	@echo "$(BY)\nBonus:$(NC)"
	@echo "$(BB)BONUS_NAME: $(NC)$(BONUS_NAME)"
	@echo "$(BB)SRC_BONUS_FILES: $(NC)$(SRC_BONUS_FILES)"
	@echo "$(BB)INC_BONUS_FILES: $(NC)$(INC_BONUS_FILES)"
	@echo "$(BB)SRCS_BONUS: $(NC)$(SRCS_BONUS)"
	@echo "$(BB)OBJS_BONUS: $(NC)$(OBJS_BONUS)"
	@echo "$(BB)DEPS_BONUS: $(NC)$(DEPS_BONUS)"
	@echo "$(BB)INCS_BONUS: $(NC)$(INCS_BONUS)"
	@echo "$(BB)IFLAGS_BONUS: $(NC)$(IFLAGS_BONUS)"

.PHONY: all clean fclean re bonus debug valgrind
.DEFAULT_GOAL := all