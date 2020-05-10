CC = g++
CFLAGS = -Wall -Wextra -Wvla -pthread -std=c++11

default: ConvexHull PointSetBinaryOperations
	./PointSetBinaryOperations

# Executables
ConvexHull: Point.o PointSet.o ConvexHull.cpp
	$(CC) $(CFLAGS) $^ -o $@

PointSetBinaryOperations: Point.o PointSet.o PointSetBinaryOperations.cpp
	$(CC) $(CFLAGS) $^ -o $@

# Object files
Point.o: Point.h Point.cpp
	$(CC) $(CFLAGS) -c $^

PointSet.o: PointSet.h PointSet.cpp
	$(CC) $(CFLAGS) -c $^

tar:
	tar cvf ex1.tar ConvexHull.cpp PointSet.h PointSet.cpp Point.h Point.cpp PointSetBinaryOperations.cpp README Makefile

clean:
	rm -f *.o *.gch *.tar ConvexHull PointSetBinaryOperations