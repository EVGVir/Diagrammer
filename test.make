.PHONY: test

GTEST_BASE_DIR = build/google-test
GTEST_DIR = $(GTEST_BASE_DIR)/googletest
GMOCK_DIR = $(GTEST_BASE_DIR)/googlemock
LIB_GMOCK = $(GMOCK_DIR)/make/gmock_main.a

DOCOPT_BASE_DIR = build/docopt
LIB_DOCOPT = $(DOCOPT_BASE_DIR)/libdocopt.a


# GNU dialect is needed for Google Test.
CXXFLAGS  = -std=gnu++11
CXXFLAGS += -Wall
CXXFLAGS += -g -O0

INC += -Isrc
INC += -I$(GTEST_DIR)/include
INC += -I$(GMOCK_DIR)/include
INC += -I$(DOCOPT_BASE_DIR)

SRC += $(filter-out src/main.c++,$(wildcard src/*.c++)) # There must not be two main() functions.
SRC += test/*.c++

LIBS += `pkg-config --libs --cflags cairo`
LIBS += -Lbuild/google-test/googlemock/make -l:gmock_main.a
LIBS += -L$(DOCOPT_BASE_DIR) -ldocopt
LIBS += -lpthread

test: build/test
	build/test


build/test: $(LIB_GMOCK) $(LIB_DOCOPT) src/* test/* test.make
	$(CXX) $(CXXFLAGS) $(SRC) $(INC) $(LIBS) -o build/test


# Google Test
$(LIB_GMOCK): gtest.make
	make -f gtest.make


# docopt
$(LIB_DOCOPT): docopt.make
	make -f docopt.make
