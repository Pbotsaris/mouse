SRC=src
OBJ=obj
BIN=bin

CFLAGS +=-W  -Wall -Wextra -g3 -Iinclude -fsanitize=address
CFLAGS_NO_SAN +=-W -Wall -Wextra -g3 -Iinclude 

CC=gcc
TARGET=$(BIN)/my_mouse
RM=rm -rf

SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS) 

$(OBJ)/%.o: $(SRC)/%.c 
	${CC} ${CFLAGS} -c $< -o $@

let_leak: $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS_NO_SAN) 

$(OBJ)/%.o: $(SRC)/%.c 
	${CC} ${CFLAGS_NO_SAN} -c $< -o $@

clean:
	$(RM) $(TARGET) $(BIN)/*.dSYM $(OBJ)/*.o 
