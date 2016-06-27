.PHONY:

CXXFLAGS  = -std=c++11
CXXFLAGS += -Wall
CXXFLAGS += -g -O0

INC += -Isrc

SRC += src/*.c++

LIBS += `pkg-config --libs --cflags cairo`


build/diagrammer: src/* diagrammer.make
	$(CXX) $(CXXFLAGS) $(SRC) $(INC) $(LIBS) -o build/diagrammer
