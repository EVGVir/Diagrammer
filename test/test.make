.PHONY: clean test

LIB_GTEST = google-test/googletest/make/gtest_main.a

# GNU dialect is needed for Google Test.
CXXFLAGS  = -std=gnu++11
CXXFLAGS += -Wall
CXXFLAGS += -g -O0

LDLIBS    = -l:gtest_main.a -lpthread
LDFLAGS   = -Lgoogle-test/googletest/make


test: bin/test
	bin/test


bin/test: bin test.c++ $(LIB_GTEST)
	$(CXX) $(CXXFLAGS) test.c++ -I../src -Igoogle-test/googletest/include $(LDFLAGS) $(LDLIBS) -o bin/test


bin:
	mkdir bin


# Google Test
$(LIB_GTEST): gtest.make
	make -f gtest.make $(LIB_GTEST)


# Clean
clean:
	-rm -f *~
	-rm -fr bin
	-make -f gtest.make clean
