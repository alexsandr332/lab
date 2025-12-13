CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = sport_db
OBJ = sport.o main.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c sport.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ) $(TARGET) sport.dat

run: $(TARGET)
	./$(TARGET)

rebuild: clean all
