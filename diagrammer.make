.PHONY:

DOCOPT_BASE_DIR = build/docopt
LIB_DOCOPT = $(DOCOPT_BASE_DIR)/libdocopt.a

CXXFLAGS  = -std=c++11
CXXFLAGS += -Wall
CXXFLAGS += -g -O0

INC += -Isrc
INC += -I$(DOCOPT_BASE_DIR)

SRC += src/*.c++

LIBS += `pkg-config --libs --cflags cairo`
LIBS += -L$(DOCOPT_BASE_DIR) -ldocopt


build/diagrammer: src/* diagrammer.make $(LIB_DOCOPT)
	$(CXX) $(CXXFLAGS) $(SRC) $(INC) $(LIBS) -o build/diagrammer


# Docopt
$(LIB_DOCOPT): docopt.make
	make -f docopt.make
