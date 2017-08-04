CC = g++
CFLAGS = -I.
DEPS = hellomake.h
OBJ = hellomake.o hellofunc.o

#%.o:%.cpp $(DEPS)
#	$(CC) -c -o $@ $< $(CFLAGS)

#hellomake:$(OBJ)
#	$(CC) -o $@ $^ $(CFLAGS)
#

test: graph_v2.cpp
	$(CC) -o $@ $< -lboost_system -g -std=c++11
