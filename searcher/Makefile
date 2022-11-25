FLAG=-std=c++17 -ljsoncpp
searcher: searcher.cpp ../index/index.cpp
	g++ $^ -o $@ $(FLAG)
.PHONY: clean
clean:
	rm -f searcher