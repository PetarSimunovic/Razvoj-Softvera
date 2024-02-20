all: one two

one:
	g++ -c main.cpp -IC:\Razvoj_softvera\include 
two:
	g++ main.o -o main -LC:\Razvoj_softvera\lib  -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system 