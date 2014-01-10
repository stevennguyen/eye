eye: main.o pwm.o
	g++ ./build/main.o ./build/pwm.o `pkg-config --cflags --libs opencv` -o ./bin/eye

main.o: ./src/main.cpp
	g++ ./src/main.cpp `pkg-config --cflags --libs opencv` -c -o ./build/main.o

pwm.o: ./src/pwm.c
	g++ ./src/pwm.c -c -o ./build/pwm.o

clean:
	rm ./build/*
	rm ./bin/*
