CC = gcc
CFLAGS =  -lSDL_image -framework OpenGL -framework GLUT
SDL_INC= `sdl-config --cflags`
SDL_LIB= `sdl-config --libs`

all: planetary clear

input.o: input.c
	$(CC) -c $^

planets.o: planets.c
	$(CC) -c $^ $(SDL_INC) $(SDL_LIB)

planetary.o: planetary.c
	$(CC) -c $^ $(SDL_INC) $(SDL_LIB)

planetary: planetary.o planets.o input.o
	$(CC) -o planetary $^ $(CFLAGS) $(SDL_INC) $(SDL_LIB)

clear:
	rm *.o

