CFLAGS = -Weverything -pedantic -ggdb3 -O3 -Wno-c++98-compat

dijkstra: lib.cpp dijkstra.cpp 
	clang++ $(CFLAGS) lib.cpp dijkstra.cpp -o dijkstra

dial: lib.cpp dial.cpp
	clang++ $(CFLAGS) lib.cpp dial.cpp -o dial

radix: lib.cpp radix.cpp
	clang++ $(CFLAGS) lib.cpp radix.cpp -o radix

clean:
	@rm dijkstra dial radix
