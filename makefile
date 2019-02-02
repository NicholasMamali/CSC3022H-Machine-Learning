

default:
	g++          -c ./src/driver.cpp
	g++          driver.o -o KMeans --std=c++11
	mv *.o KMeans ./bin


# deletes all the object code files
run:
	./bin/KMeans
clean:
	rm -f ./bin/*

