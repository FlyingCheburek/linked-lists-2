all: program clean

program: target/*.o
	g++ target/*.o -o program

target/*.o:
	g++ -c src/main/main.cpp
	g++ -c src/main/linked_list/*.hpp
	mv src/main/linked_list/*.hpp.gch target/
	mv *.o target/
clean:
	rm target/*.*
	


