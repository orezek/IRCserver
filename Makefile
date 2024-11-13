# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/21 10:59:06 by mbartos           #+#    #+#              #
#    Updated: 2024/11/13 10:57:40 by mbartos          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BOLD =	\033[1m
GREEN =	\033[32m
RED =	\033[31m
BCYAN =	\033[96m
NC =	\033[0m

NAME =		ircserv

CCP =		c++ -std=c++98
CFLAGS =	-g -Wall -Wextra -Werror\
			-I./include/ -I./include/commands

SRC_PATH = ./src/
COMMANDS_PATH = ./src/commands/

SRC =		$(wildcard $(SRC_PATH)*.cpp) $(wildcard $(COMMANDS_PATH)*.cpp)

# Objects and dependencies
OBJ_PATH =	obj/
OBJ_COMMANDS_PATH = $(OBJ_PATH)commands/
OBJ =		$(patsubst $(SRC_PATH)%.cpp,$(OBJ_PATH)%.o,$(wildcard $(SRC_PATH)*.cpp)) \
			$(patsubst $(COMMANDS_PATH)%.cpp,$(OBJ_COMMANDS_PATH)%.o,$(wildcard $(COMMANDS_PATH)*.cpp))

DEPS =		$(OBJ:.o=.d)

BIN_PATH = bin/

all: $(BIN_PATH)$(NAME)

# Rule to compile general .cpp files into obj/
$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp | $(OBJ_PATH)
	$(CCP) $(CFLAGS) -MMD -MP -c $< -o $@

# Rule to compile command .cpp files into obj/commands/
$(OBJ_COMMANDS_PATH)%.o: $(COMMANDS_PATH)%.cpp | $(OBJ_COMMANDS_PATH)
	$(CCP) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(DEPS)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(OBJ_COMMANDS_PATH):
	@mkdir -p $(OBJ_COMMANDS_PATH)

$(BIN_PATH):
	@mkdir -p $(BIN_PATH)

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

logoff: CFLAGS += -DLOGGING_ENABLED=0
logoff: re

.PHONY: all re clean fclean log