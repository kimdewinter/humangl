NAME = humangl

LIB_GLFW_NAME = glfw
LIB_GLAD_NAME = glad

SRC_PATH = ./src/
OBJ_PATH = ./obj/
LIB_PATH = ./lib/
INC_PATH = ./include/ $(LIB_PATH)$(LIB_GLFW_NAME)/include/ $(LIB_PATH)$(LIB_GLAD_NAME)/include/

CC_FLGS = -std=c++11 #-Werror -Wextra -Wall
CC_LIBS = -lglfw -framework AppKit -framework OpenGL -framework IOKit -framework CoreVideo

SRC_NAME = main.cpp
OBJ_NAME = $(SRC_NAME:.cpp=.o)
LIB_NAME = $(LIB_GLFW_NAME)/src
LIB_SRC_NAME = $(LIB_GLAD_NAME)/src/glad.c

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))
LIB = $(addprefix -L$(LIB_PATH),$(LIB_NAME))
LIB_SRC = $(addprefix $(LIB_PATH),$(LIB_SRC_NAME))

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CC_FLGS) $(LIB) $(LIB_SRC) $(INC) $(OBJ) $(CC_LIBS) -o $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp
	mkdir -p $(OBJ_PATH)
	$(CXX) $(CC_FLGS) $(INC) -o $@ -c $<

clean:
	rm -fv $(OBJ)
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -fv $(NAME)

re: fclean all
