# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/21 10:59:06 by mbartos           #+#    #+#              #
#    Updated: 2024/09/30 12:21:34 by mbartos          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BOLD =	\033[1m
GREEN =	\033[32m
RED =	\033[31m
BCYAN =	\033[96m
NC =	\033[0m

# Name of the executable
NAME =		ircserv

# Compiler and flags
CCP =		c++
CFLAGS =	-g -Wall -Wextra -Werror -std=c++98 \
			-I./include/

# Source and object paths
SRC_PATH = ./src/
SRC =		$(wildcard $(SRC_PATH)*.cpp)

# Objects and dependencies
OBJ_PATH =	obj/
OBJ =		$(SRC:$(SRC_PATH)%.cpp=$(OBJ_PATH)%.o)  # Ensures correct object file paths
DEPS =		$(OBJ:.o=.d)

# Binary directory
BIN_PATH = bin/

all: $(BIN_PATH)$(NAME)

# Rule to compile .cpp files to .o files
$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp | $(OBJ_PATH)
	$(CCP) $(CFLAGS) -MMD -MP -c $< -o $@

# Include dependency files
-include $(DEPS)

# Create object directory if it doesn't exist
$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

# Create binary directory if it doesn't exist
$(BIN_PATH):
	@mkdir -p $(BIN_PATH)

# Link object files to create the final executable
$(BIN_PATH)$(NAME): $(OBJ) | $(BIN_PATH)
	@echo "$(BOLD)$(BCYAN)[ Compiling $(NAME)... ]$(NC)"
	$(CCP) $(CFLAGS) $(OBJ) -o $@
	@echo "$(BOLD)$(GREEN)[ Program $(NAME) ready in bin/ folder! ]$(NC)"

clean:
	@rm -Rf $(OBJ_PATH)
	@echo "$(BOLD)$(RED)[ Obj files deleted ]$(NC)"

fclean: clean
	@rm -f $(BIN_PATH)$(NAME)
	@echo "$(BOLD)$(RED)[ Program deleted ]$(NC)"

re: fclean all

.PHONY: all re clean fclean
