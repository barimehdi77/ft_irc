# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbari <mbari@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/05 14:21:19 by asfaihi           #+#    #+#              #
#    Updated: 2022/05/12 15:36:39 by mbari            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the final executable files
NAME = ./ft_irc

# Project's directories
SRCS_FOLDER = srcs
OBJECTSDIR = objects
HEADERS_FOLDER = headers

# Name of variables
FLAGS = #-Wall -Wextra -Werror
CPP_STANDARD = #-std=c++98
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
RESET = \033[0m

# Exercise files variable
SRC_FILES = Client.cpp \
Server.cpp \
commands.cpp \
getSocket.cpp \
messagesHandling.cpp \
pollHandling.cpp \
requestHandling.cpp \
Channel.cpp \
DeezNuts.cpp \
utils.cpp \


MAIN = main.cpp
# Define objects for all sources
OBJS := $(addprefix $(OBJECTSDIR)/, $(SRC_FILES:.cpp=.o))
MAIN_OBJ = $(addprefix $(OBJECTSDIR)/, $(MAIN:.cpp=.o))

# Name the compiler
CC = c++

# OS specific part
RM = rm -rf
RMDIR = rm -rf
MKDIR = mkdir -p
MAKE = make -C
ECHO = /bin/echo
ERRIGNORE = 2>/dev/null

all: credit $(NAME)
	@echo "$(BLUE)██████████████████████ Compiling is DONE ███████████████████████$(RESET)"
	@echo "       Made with love by : \033[1;91mmbari asfaihi abdel-ke\033[m"

head:
	@echo "$(BLUE)█████████████████████ Making ft_irc Server █████████████████████$(RESET)"

# Phonebook making rules
$(NAME): head $(OBJS) $(MAIN_OBJ) $(HEADERS_FOLDER)
	@$(CC) $(CPP_STANDARD) -I $(HEADERS_FOLDER) $(OBJECTSDIR)/main.o $(OBJS) -o $@ -g

$(OBJECTSDIR)/%.o: $(SRCS_FOLDER)/%.cpp $(HEADERS_FOLDER)
	@$(MKDIR) $(dir $@)
	@printf "$(BLUE)█ $(YELLOW)Compiling$(RESET) $<:\r\t\t\t\t\t\t\t..."
	@$(CC) $(CPP_STANDARD) $(FLAGS) -I $(HEADERS_FOLDER) -o $@ -c $< -g
	@echo "\r\t\t\t\t\t\t\t$(GREEN){DONE}$(BLUE) █$(RESET)"

$(OBJECTSDIR)/%.o: main.cpp $(HEADERS_FOLDER)
	@printf "$(BLUE)█ $(YELLOW)Compiling$(RESET) $<:\r\t\t\t\t\t\t\t..."
	@$(CC) $(CPP_STANDARD) $(FLAGS) -I $(HEADERS_FOLDER) -o $@ -c $< -g
	@echo "\r\t\t\t\t\t\t\t$(GREEN){DONE}$(BLUE) █$(RESET)"

# Remove all objects, dependencies and executable files generated during the build
clean:
	@echo "$(RED)deleting$(RESET): " $(OBJECTSDIR)
	@$(RMDIR) $(OBJECTSDIR)


fclean: clean
	@echo "$(RED)deleting$(RESET): " $(NAME)
	@$(RM) $(NAME) $(ERRIGNORE)

re: fclean all

# Print Credit
credit:
	@echo " ┏━━━┓┏━━━━┓    ┏━━┓┏━━━┓┏━━━┓"
	@echo " ┃┏━━┛┃┏┓┏┓┃    ┗┫┣┛┃┏━┓┃┃┏━┓┃"
	@echo " ┃┗━━┓┗┛┃┃┗┛     ┃┃ ┃┗━┛┃┃┃ ┗┛"
	@echo " ┃┏━━┛  ┃┃       ┃┃ ┃┏┓┏┛┃┃ ┏┓"
	@echo " ┃┃    ┏┛┗┓┏━━━┓┏┫┣┓┃┃┃┗┓┃┗━┛┃"
	@echo " ┗┛    ┗━━┛┗━━━┛┗━━┛┗┛┗━┛┗━━━┛"
	@echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
	@echo "━━━━━━━━━┃ Made with love by : \033[1;91mmbari asfaihi abdel-ke\033[m ┃━━━━━━━━━"
	@echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
