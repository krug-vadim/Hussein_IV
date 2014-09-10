PROG := Hussein

CXXFLAGS := `wx-config --cxxflags --libs core,base`
CXX      := g++

SRC := src/ui/app.cpp

OBJ := $(patsubst %.cpp, obj/%.o, $(notdir $(SRC)))

all: Hussein

Hussein:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(PROG)

