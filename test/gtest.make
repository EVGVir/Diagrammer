.PHONY: clean

LIB_GTEST = google-test/googletest/make/gtest_main.a


# Google Test
google-test:
	git clone https://github.com/google/googletest.git --branch master google-test


$(LIB_GTEST): google-test
	make -C google-test/googletest/make gtest_main.a


# Clean
clean:
	-rm -f *~
	-rm -fr bin
	-rm -fr google-test
