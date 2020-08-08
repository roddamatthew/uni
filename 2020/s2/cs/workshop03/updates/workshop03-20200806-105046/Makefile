# must specify make target
all: test
	@true

notest:
	@true

.PHONY: all test notest clean

clean:
	@rm -f ?/*.out success

test:
	-@bash bin/run-tests

