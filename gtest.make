.PHONY: gtest

GTEST_BASE_DIR = build/google-test
GMOCK_DIR = $(GTEST_BASE_DIR)/googlemock
LIB_GMOCK = $(GMOCK_DIR)/make/gmock_main.a


gtest: $(LIB_GMOCK)


$(GTEST_BASE_DIR):
	git clone https://github.com/google/googletest.git --branch master $(GTEST_BASE_DIR)


$(LIB_GMOCK): | $(GTEST_BASE_DIR)
	make -C $(GMOCK_DIR)/make gmock_main.a
