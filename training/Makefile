# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/05 14:21:19 by asfaihi           #+#    #+#              #
#    Updated: 2022/04/11 14:09:11 by asfaihi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SER_NAME = server
CLI_NAME = client

SER_SRC = server.cpp request.cpp
CLI_SRC = client.cpp

FLAGS = -Wall -Wextra -Werror

CPP_STANDARD = -std=c++98

SER_OBJECT = $(SER_SRC:%.cpp=%.o)
CLI_OBJECT = $(CLI_SRC:%.cpp=%.o)

all: $(SER_NAME) $(CLI_NAME)

$(SER_NAME): $(SER_OBJECT)
	c++ $(SER_OBJECT) -o $(SER_NAME)

$(CLI_NAME): $(CLI_OBJECT)
	c++ $(CLI_OBJECT) -o $(CLI_NAME)

%.o:%.cpp
	c++ $(CPP_STANDARD) -c $<

clean:
	/bin/rm -f $(SER_OBJECT)
	/bin/rm -f $(CLI_OBJECT)

fclean: clean
	/bin/rm -f $(SER_NAME)
	/bin/rm -f $(CLI_NAME)
	/bin/rm -rf a.out
	/bin/rm -rf *.dSYM

re: fclean all
