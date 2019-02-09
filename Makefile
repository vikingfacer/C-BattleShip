COMPILER="g++"
FLAGS="-std=c++11"
libs="-lboost_regex"
BIN=test



all: $(BINS)

%.o:%.cpp
	$(COMPILER) $(FLAGS) -c $^ -o $@


run: $(BIN)
	./$(BIN)

$(BIN): Ship.o board.o main.o tile.o
	$(COMPILER) $(FLAGS) $^ -o $@ $(libs)

memtest: run
	valgrind --tool=memcheck  ./$(BIN)


.PHONY: clean

clean: 
	rm *.o; rm $(BIN)
