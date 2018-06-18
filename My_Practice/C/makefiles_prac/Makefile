cc = gcc


main: main.c add.c sub.c  
	$(cc) main.c add.c sub.c -o main

install:main
	sudo cp main /bin/
clean:
	rm main
