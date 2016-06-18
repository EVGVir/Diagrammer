.PHONY: gtest

LIB_GTEST = build/google-test/googletest/make/gtest_main.a


gtest: $(LIB_GTEST)


google-test:
	git clone https://github.com/google/googletest.git --branch master build/google-test


$(LIB_GTEST): google-test
	make -C build/google-test/googletest/make gtest_main.a
