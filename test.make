.PHONY: test

GTEST_BASE_DIR = build/google-test
GTEST_DIR = $(GTEST_BASE_DIR)/googletest
GMOCK_DIR = $(GTEST_BASE_DIR)/googlemock
LIB_GMOCK = $(GMOCK_DIR)/make/gmock_main.a

# GNU dialect is needed for Google Test.
CXXFLAGS  = -std=gnu++11
CXXFLAGS += -Wall
CXXFLAGS += -g -O0

INC += -Isrc
INC += -I$(GTEST_DIR)/include
INC += -I$(GMOCK_DIR)/include

SRC += src/ascii-matrix.c++
SRC += src/diagram.c++

SRC += test/ascii-matrix-test.c++
SRC += test/diagram-test.c++
SRC += test/matrix-test.c++

LDLIBS    = -l:gmock_main.a -lpthread
LDFLAGS   = -Lbuild/google-test/googlemock/make


test: build/test
	build/test


build/test: $(LIB_GMOCK) src/* test/* test.make
	$(CXX) $(CXXFLAGS) $(SRC) $(INC) $(LDFLAGS) $(LDLIBS) -o build/test


# Google Test
$(LIB_GMOCK): gtest.make
	make -f gtest.make
