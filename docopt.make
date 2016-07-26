.PHONY: docopt

DOCOPT_BASE_DIR = build/docopt
LIB_DOCOPT = $(DOCOPT_BASE_DIR)/libdocopt.a


docopt: $(LIB_DOCOPT)


$(DOCOPT_BASE_DIR):
	git clone https://github.com/docopt/docopt.cpp.git --branch master $(DOCOPT_BASE_DIR)


$(DOCOPT_BASE_DIR)/Makefile: | $(DOCOPT_BASE_DIR)
	cd $(DOCOPT_BASE_DIR); cmake .


$(LIB_DOCOPT): $(DOCOPT_BASE_DIR)/Makefile
	make -C $(DOCOPT_BASE_DIR) docopt_s
