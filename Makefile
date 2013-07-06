# The basic structure of this makefile should work in any UNIX environment.
# It should also work automatically with makedepend, should you be so inclined to use it.

# C++ compiler
CXX = g++

# C++ compiler flags
CXXFLAGS = -g -Wall

# Creating a .o file
COMPILE = $(CXX) $(CXXFLAGS) -c

# Name of the executable.
EXE = cranberry

# All object files, space separated.
SRCS = $(shell ls src/*.cpp) src/lex.yy.cpp
OBJS = $(SRCS:.cpp=.o)

# The first target is the one that is executed when you invoke
# "make". The line describing the action starts with <TAB>.
#   In this case there isn't one.
all: flex make $(EXE)

make: $(SRCS)
	makedepend -Y src/*.cpp 2>/dev/null

flex : src/cranberry.lex
	flex -+ -o src/lex.yy.cpp src/cranberry.lex

# The variable "$@" stands for the current target. "$^" is everything 
# it depends on.  In this case, the executable depends on all the object files.
$(EXE) : $(OBJS)
	$(CXX) $^ -o $@

# An object file is dependent on the corresponding source file
# "$<" is the name of the first prerequisite.
# But there should only be one anyway.
#  This is mainly here for non gnu-make versions of make.
src/%.o : src/%.cpp
	$(COMPILE) -o $@ $<

# Get rid of all the signs of compilation.
clean:
	rm -rf ./src/*.o ./$(EXE) Makefile.bak

# Below this: Stuff from makedepend. Or rules in a similar form as above.
# DO NOT DELETE

src/lex.yy.o: src/h/token.h src/h/parser.h src/h/class_def.h src/h/language.h
