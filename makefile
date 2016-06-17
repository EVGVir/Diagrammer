.PHONY: clean test


# Test
test:
	make -C test -f test.make test


# Clean
clean:
	-rm -f *~
	-make -C test -f test.make clean
