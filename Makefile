init:
	gcc -o game src/main.c -lSDL2main -lSDL2

run:
	./game

install:
	sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev