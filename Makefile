#Copyright Notice:
#The files within this zip file are copyrighted by Lazy Foo' Productions (2004-2014)
#and may not be redistributed without written permission.


#All source files
SRCS = $(wildcard *.cpp)

#Object files are derived from SRCS macro
OBJS = $(SRCS:%.cpp=%.o)

#CC specifies which compiler we're using
CC = g++
#COMPILER_FLAGS specifies the additional compilation options we're using
# -Wall enables all warnings (warnings are good!)
COMPILER_FLAGS = -Wall

# Flags and stuff, change as required
OPTIMZE=-O3
#CFLAGS=-fopenmp -ggdb $(OPTIMIZE)
CXXFLAGS= -fopenmp -ggdb $(OPTIMIZE) -Wall $(shell pkg-config sdl2 --cflags)
LDFLAGS= -fopenmp -lm

#CC=g++

# The first target (all) is allways the default target
all: build test

# Our buld target depends on the real target
.PHONY: build
build: $(TARGET)

# Our test target
# 
# Here we instruct make to generate a line with all test
# which are all sequentially executed using the $(foreach)
# macro. We conclude with 'true' because the && construct
# awaits an argument on both sides. The 'true' command
# simply returns a success value
.PHONY: test
test: $(TESTS)
	$(foreach T,$(TESTS), ./$(T) &&) true

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = Waermeblanko

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LDFLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

# Cleanup all generated files
clean:
	rm -Rf $(TESTS) $(OBJS) $(TARGET)
