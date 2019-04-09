a.out: main.o Book.o Shelf.o member.o metafunc.o io.o
	g++ main.o Book.o Shelf.o member.o metafunc.o io.o 
main.o: main.cpp
	g++ main.cpp Book.cpp member.cpp Shelf.cpp io.cpp -c
io.o: io.cpp io.h
	g++ io.cpp io.h member.cpp Book.cpp Shelf.cpp -c
member.o: member.cpp Member.h
	g++ member.cpp Member.h Shelf.cpp Book.cpp -c
Shelf.o: Shelf.cpp Shelf.h
	g++ Shelf.cpp Shelf.h Book.cpp -c 
metafunc.o: metafunc.cpp 
	g++ metafunc.cpp -c 
Book.o: Book.cpp Book.h
	g++ Book.cpp Book.h -c
