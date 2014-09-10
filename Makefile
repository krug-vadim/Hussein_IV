PROG := Hussein

CXXFLAGS := `wx-config --cxxflags --libs core,base,adv` -std=c++11
CXX      := g++

SRC := src/ui/app.cpp

OBJ := $(patsubst %.cpp, obj/%.o, $(notdir $(SRC)))

all: Hussein

Hussein:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(PROG)

