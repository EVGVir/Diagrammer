.PHONY: clean test


# Test
test: build
	make -f test.make test


# Misc
build:
	mkdir build


# Clean
clean:
	-rm -rf build
	-find . -type f -name '*~' -delete
