all:hangman

hangman:hangman.cpp
	c++ -o hangman hangman.cpp

clean:
	rm -rf *.o

clobber:clean
	rm -rf hangman
