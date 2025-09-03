LIB = ./Include
PRE = ./src/

SOURCE = main.cpp RPN.cpp

SOURCES = ${addprefix $(PRE), $(SOURCE)}

NAME = RPN

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

OBJ = $(SOURCES:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I $(LIB) -c $< -o $@

clean: 
	rm -f $(OBJ)
        
fclean: clean
	rm -f $(NAME)

re: fclean all

valgrind:
	valgrind ./$(NAME)

.PHONY: all clean fclean re
