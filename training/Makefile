# SER-NAME = server
# CLI-NAME = client

# SER-SRC = server.cpp
# CLI-SRC = client.cpp

# FLAGS = -Wall -Wextra -Werror

# CPP_STANDARD = -std=c++98

# all: $(SER-NAME) $(CLI-NAME)

# $(SER-NAME):
# 	c++  $(CPP_STANDARD) $(SER-SRC) -o $(SER_NAME)

# $(CLI-NAME):
# 	c++ $(CPP_STANDARD) $(CLI-SRC) -o $(CLI_NAME)

# clean:
# 	/bin/rm -f $(OBJECT)

# fclean: clean
# 	/bin/rm -f $(NAME)

# re: fclean all

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
	/bin/rm -f $(SER_NAME) $(CLI_NAME)

re: fclean all
