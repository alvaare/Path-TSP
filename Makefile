SRC = $(*.cpp)
OBJ = $(src:.cpp=.o)
DEPS = $(*.hpp)

CXX = g++
CXXFLAGS = -Wall

%.o: %.c $(DEPS) $(CXX) -c -o $@ $< $(CXXFLAGS)

christophides: $(OBJ) $(CXX) -o $@ $^ $(CXXFLAGS)

clean: rm -f $(OBJ) myprog
