############# Compiler and Flags #################
C = gcc
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
CFLAGS = -Wall -Wextra -O2
LIBS = -lGL -lglfw
##################################################

################# Source Path ####################
ENGINE_SRC_C   = ./lib/glad/src/glad.c
ENGINE_SRC_CPP = $(shell find ./src/audio ./src/core ./src/graphics -name '*.cpp')
##################################################

ENGINE_OBJ = $(ENGINE_SRC_C:.c=.o) $(ENGINE_SRC_CPP:.cpp=.o)

ENGINE_TARGET_A = libFDSE.a
ENGINE_TARGET_SO = libFDSE.so

################### Build ########################

######### Static #########
static: clean
static: $(ENGINE_TARGET_A)

$(ENGINE_TARGET_A): $(ENGINE_OBJ)
	ar rcs $@ $^
##########################

######### Dynamic ########
dynamic: clean
dynamic: CXXFLAGS += -fPIC
dynamic: CFLAGS += -fPIC
dynamic: $(ENGINE_TARGET_SO)

$(ENGINE_TARGET_SO): $(ENGINE_OBJ)
	$(CXX) -shared -o $@ $^
###########################

##################################################

######## Compilation of other .cpp/.o ############
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.c
	$(C) $(CFLAGS) -c $< -o $@
##################################################

################### Clear ########################
clean:
	rm -f $(ENGINE_OBJ) $(ENGINE_TARGET_A) $(ENGINE_TARGET_SO)
##################################################