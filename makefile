all: one two

one:
	g++ -c main.cpp -IC:\Razvoj_softvera\include -IC:\Razvoj_softvera\spritemanager.cpp
two:
	g++ main.o -o main -LC:\Razvoj_softvera\lib -lsfml-graphics -lsfml-window -lsfml-system