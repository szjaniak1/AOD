CFLAGS = -Wall -pedantic -ggdb3 -O3 -Wno-c++98-compat

dijkstra: lib.cpp dijkstra.cpp 
	g++ $(CFLAGS) lib.cpp dijkstra.cpp -o dijkstra

dial: lib.cpp dial.cpp
	g++ $(CFLAGS) lib.cpp dial.cpp -o dial

radix: lib.cpp radix.cpp
	g++ $(CFLAGS) lib.cpp radix.cpp -o radix

clean:
	@rm dijkstra dial radix
