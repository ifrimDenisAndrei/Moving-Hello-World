CC = gcc
LDFLAGS = -lX11

window: hello_world.c file_size_calculator.c
	@$(CC) hello_world.c file_size_calculator.c -o MovingHelloWorld $(LDFLAGS)

execute: MovingHelloWorld
	@./MovingHelloWorld

clean:
	@rm -f MovingHelloWorld