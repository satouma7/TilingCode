CXX = c++

CXXFLAGS = -Wextra -Wall -O3 -mtune=native -std=gnu++14

INC = -I$(HOME)/include 

LIBS = -L$(HOME)/lib -lbasic -lglsc3d_3 -lz -L/opt/local/lib -lsdl2 -lfreetype -lpng -lc++ -L/$(HOME)/lib -framework OpenGL

PROGRAM = test_program
OBJECT = $(PROGRAM).o
SOURCE = main.cpp

$(PROGRAM): $(PROGRAM)
	$(CXX) $(CXXFLAGS) $(INC) $(LIBS) -o $(PROGRAM) $(SOURCE)

clean:;		@rm -f $(OBJS) $(PROGRAM) core
