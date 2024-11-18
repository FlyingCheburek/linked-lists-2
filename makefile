all: run no-bin

mem-check: build
	valgrind ./program

run: build 
	./program

build: program clean

check: program clean no-bin

program: target/*.o
	g++ target/*.o -o program

target/*.o:
	g++ -c src/main/main.cpp
	g++ -c src/main/linked_list/*.hpp
	mv src/main/linked_list/*.hpp.gch target/
	mv *.o target/

no-bin:
	rm program

clean:
	rm target/*.*
	


