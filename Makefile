# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/05 14:21:19 by asfaihi           #+#    #+#              #
#    Updated: 2022/04/17 14:02:44 by asfaihi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = server

SRC = server.cpp Client.cpp main.cpp

FLAGS = -Wall -Wextra -Werror

CPP_STANDARD = -std=c++98

OBJECT = $(SRC:%.cpp=%.o)

all: $(NAME)

$(NAME): $(OBJECT)
	c++ $(OBJECT) -o $(NAME)

%.o:%.cpp
	c++ $(CPP_STANDARD) -c $<

clean:
	/bin/rm -f $(OBJECT)

fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -rf a.out
	/bin/rm -rf *.dSYM

re: fclean all
