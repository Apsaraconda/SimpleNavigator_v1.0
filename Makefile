CC=g++
STDFLAGS=-Wall -Wextra -Werror -std=c++17
LINUX_FLAGS=-lpthread -lm -lsubunit
LIBS=-lstdc++ -lncurses
TARGET=s21_graph.a
SRC=src/s21_graph/*.cc src/s21_graph_algorithms/*.cc
OS := $(shell uname -s)
ifeq ($(OS),Linux)
	OPEN_CMD=xdg-open
else
	OPEN_CMD=open
endif

all: clean app

$(TARGET): ${SRC}
	$(CC) -c $(STDFLAGS) $(SRC)
	ar rc $@ *.o
	ranlib $@

app: clean $(TARGET)
ifeq ($(OS), Darwin)
	$(CC) $(STDFLAGS) -c ./src/cli/*.cc
	$(CC) $(STDFLAGS) $(TARGET) *.o -o SimpleNavigator $(LIBS)
else
	$(CC) $(STDFLAGS) -c ./src/cli/*.cc
	$(CC) $(STDFLAGS) $(TARGET) *.o -o SimpleNavigator $(LIBS) $(LINUX_FLAGS)
endif

run:
	./SimpleNavigator

clean:
	rm -rf *.o
	rm -rf *.a
	rm -rf SimpleNavigator