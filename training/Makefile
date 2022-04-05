# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/05 14:21:19 by asfaihi           #+#    #+#              #
#    Updated: 2022/04/05 14:21:20 by asfaihi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SER_NAME = server
CLI_NAME = client

SER_SRC = server.cpp
CLI_SRC = client.cpp

FLAGS = -Wall -Wextra -Werror

CPP_STANDARD = -std=c++98

all: $(SER_NAME) $(CLI_NAME)

$(SER_NAME):
	c++ $(CPP_STANDARD) $(FLAGS) $(SER_SRC) -o $(SER_NAME)

$(CLI_NAME):
	c++ $(CPP_STANDARD) $(FLAGS) $(CLI_SRC) -o $(CLI_NAME)

clean:

fclean:
	/bin/rm -f $(SER_NAME)
	/bin/rm -f $(CLI_NAME)

re: fclean all
