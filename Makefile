COMPILER="g++"
FLAGS="-std=c++14"
FLAGS+="-g"
FLAGS+="-rdynamic"
libs="-lboost_regex"
BIN=BATTLESHIP

OS = $(shell uname)

# graphics stuff OS specific
ifeq ($(OS), Darwin)
	libs += -lraylib -framework OpenGL -framework OpenAL -framework Cocoa
else
	libs += -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
endif


all: $(BINS)

%.o:%.cpp
	$(COMPILER) $(FLAGS) -c $^ -o $@ $(libs)


run: $(BIN)
	./$(BIN)

$(BIN): Ship.o board.o main.o tile.o player.o drawable.o COMplayer.o
	$(COMPILER) $(FLAGS)  $^ -o $@ $(libs)
# -static for static
memtest: run
	valgrind --tool=memcheck  ./$(BIN)


.PHONY: clean

clean:
	rm *.o; rm $(BIN)
