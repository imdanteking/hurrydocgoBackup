CC=g++
FLAG=-std=c++17 -I ../third_party/cppjieba/include -lpthread -ljsoncpp -lboost_system
hurrydocgo: controller.cpp ../index/index.cpp ../searcher/searcher.cpp
	$(CC) -o $@ $^ $(FLAG)
.PHONY:clean
clean:
	rm -rf hurrydocgo
	rm -rf ../data/output/raw_input
