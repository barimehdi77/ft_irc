# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbari <mbari@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/03 15:52:51 by mbari             #+#    #+#              #
#    Updated: 2022/04/03 15:56:40 by mbari            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SER_NAME = server
CLI_NAME = client

CPP				= c++

SER_FILE = myserver.cpp
CLI_FILE = myclinet.cpp

all: clean $(SER_NAME) $(CLI_NAME)

$(SER_NAME):
				$(CPP) $(SER_FILE) -o $(SER_NAME)

$(CLI_NAME):
				$(CPP) $(CLI_FILE) -o $(CLI_NAME)


clean:
		rm $(SER_NAME) $(CLI_NAME)
