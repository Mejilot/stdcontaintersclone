all: clean test

clean:
	rm -rf test

test:
	g++ ./tests/test_*.cc -std=c++17 -lgtest -lgtest_main -o $@
	./$@
leaks: test
	leaks --atExit -- ./test

valgrind: test
	valgrind --track-origins=yes --leak-check=full -s ./test

format:
	cp ../materials/linters/.clang-format .
	clang-format -i *.h ./tests/*.cc
	rm .clang-format

style:
	cp ../materials/linters/.clang-format .
	clang-format -n *.h ./tests/*.cc
	rm .clang-format

.PHONY: clean format style
