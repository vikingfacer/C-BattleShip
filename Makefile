COMPILER="g++"
FLAGS="-std=c++11"
libs="-lboost_regex"
BINS=test

all: $(BINS)

%.o:%.cpp
	$(COMPILER) $(FLAGS) -c $^ -o $@


test: main.o Ship.o board.o
	$(COMPILER) $(FLAGS) $^ -o $@ $(libs)

memtest: test
	valgrind --tool=memcheck  ./$<


.PHONY: clean

clean: 
	rm *.o
