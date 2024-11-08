# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: orezek <orezek@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/08 20:51:02 by orezek            #+#    #+#              #
#    Updated: 2024/11/08 20:51:04 by orezek           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		ircserv
CCP =		c++
CFLAGS =	-g -I./include/ -I./include/commands -I/opt/homebrew/Cellar/cjson/1.7.18/include
LIBS =      -L/opt/homebrew/lib -lcurl -lcjson  # Correctly link libcjson

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

# Link step includes $(LIBS) to link against libcurl and libcjson
$(BIN_PATH)$(NAME): $(OBJ) | $(BIN_PATH)
	@echo "$(BOLD)$(BCYAN)[ Compiling $(NAME)... ]$(NC)"
	$(CCP) $(CFLAGS) $(OBJ) -o $@ $(LIBS)
	@echo "$(BOLD)$(GREEN)[ Program $(NAME) ready in bin/ folder! ]$(NC)"

clean:
	@rm -Rf $(OBJ_PATH)
	@echo "$(BOLD)$(RED)[ Obj files deleted ]$(NC)"

fclean: clean
	@rm -f $(BIN_PATH)$(NAME)
	@echo "$(BOLD)$(RED)[ Program deleted ]$(NC)"

re: fclean all

.PHONY: all re clean fclean
