# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/21 10:59:06 by mbartos           #+#    #+#              #
#    Updated: 2024/09/30 11:44:28 by mbartos          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BOLD =	\033[1m
GREEN =	\033[32m
RED =	\033[31m
BCYAN =	\033[96m
NC =	\033[0m

#name
NAME =		ircserv

#compiler
CCP =		c++
# CFLAGS =	-Wall -Wextra -Werror
CFLAGS =	-g -Wall -Wextra -Werror -std=c++98

#sources
SRC_PATH = *
SRC =	$(wildcard $(SRC_PATH)*.cpp)

#objects
OBJ_PATH =	obj/
OBJ =		$(SRC:.cpp=.o)
OBJS =		$(addprefix $(OBJ_PATH), $(OBJ))

# binary directory
BIN_PATH = bin/

# dependency files
DEPS =      $(OBJ:.o=.d)
DEP_PATH =  $(OBJ_PATH)

all: $(BIN_PATH)$(NAME)

$(OBJ_PATH)%.o : %.cpp | $(OBJ_PATH)
	$(CCP) $(CFLAGS) -MMD -MP -c $< -o $@

# Include dependency files
-include $(OBJS:.o=.d)

# $(OBJS): | $(OBJ_PATH)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(BIN_PATH):
	@mkdir -p $(BIN_PATH)

$(BIN_PATH)$(NAME): $(OBJS) | $(BIN_PATH)
	@echo "$(BOLD)$(BCYAN)[ Compiling $(NAME)... ]$(NC)"
	$(CCP) $(CFLAGS) $(OBJS) -o $(BIN_PATH)$(NAME)
	@echo "$(BOLD)$(GREEN)[ Program $(NAME) ready in bin/ folder! ]$(NC)"

clean:
	@rm -Rf $(OBJ_PATH)
	@echo "$(BOLD)$(RED)[ Obj files deleted ]$(NC)"

fclean: clean
	@rm -f $(BIN_PATH)$(NAME)
	@echo "$(BOLD)$(RED)[ Program deleted ]$(NC)"

re: fclean all

.PHONY: all, re, clean, fclean