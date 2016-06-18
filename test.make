.PHONY: test

LIB_GTEST = build/google-test/googletest/make/gtest_main.a

# GNU dialect is needed for Google Test.
CXXFLAGS  = -std=gnu++11
CXXFLAGS += -Wall
CXXFLAGS += -g -O0

INC += -Isrc
INC += -Ibuild/google-test/googletest/include

SRC += src/ascii-matrix.c++
SRC += test/ascii-matrix-test.c++

LDLIBS    = -l:gtest_main.a -lpthread
LDFLAGS   = -Lbuild/google-test/googletest/make


test: build/test
	build/test


build/test: $(LIB_GTEST) src/* test/*
	$(CXX) $(CXXFLAGS) $(SRC) $(INC) $(LDFLAGS) $(LDLIBS) -o build/test


# Google Test
$(LIB_GTEST): gtest.make
	make -f gtest.make
