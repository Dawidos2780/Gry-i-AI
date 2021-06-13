#
#  To sa opcje dla kompilacji
#
CPPFLAGS= -c -g -Iinc -Wall -pedantic

__start__: tictactoe
	./tictactoe

obj:
		mkdir -p obj

tictactoe: obj/main.o obj/board.o
	g++ -Wall -pedantic -o tictactoe obj/main.o obj/board.o
								   

obj/main.o: src/main.cpp inc/board.hh
	g++ ${CPPFLAGS} -o obj/main.o src/main.cpp

obj/board.o: src/board.cpp inc/board.hh
	g++ ${CPPFLAGS} -o obj/board.o src/board.cpp

clean:
	rm -f obj/*.o tictactoe