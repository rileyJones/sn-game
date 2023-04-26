.SUFFIXES: .c .o

TARGET = game
OBJECTS = main.o update.o render.o event.o gamepad.o init.o

CC = gcc
CFLAGS = -Wall -Werror -pedantic -g
LIBS = 
SDL = `sdl2-config --cflags --libs`

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS) $(SDL)

run: $(TARGET) 
	./$(TARGET)

#.PHONY: clean
clean:
	rm $(TARGET)
	rm *.o

.c.o:
	$(CC) -c -o $@ $< $(CFLAGS) $(LIBS) $(SDL)

main.o: main.c game.h gamepad.h
update.o: update.c game.h gamepad.h
render.o: render.c game.h gamepad.h
event.o: event.c game.h gamepad.h
gamepad.o: gamepad.c gamepad.h
init.o: init.c game.h gamepad.h
