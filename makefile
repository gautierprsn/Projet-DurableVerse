EXEC=DurableVerse
TEST=unitTest
SRC=src/
HEADER=headers/
OBJ=obj/
BIN=bin/
LDFLAGS=
CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -lm

all:: $(BIN)$(EXEC) $(BIN)$(TEST)

start: $(BIN)$(EXEC)
	./$(BIN)$(EXEC)

test: $(BIN)$(TEST)
	./$(BIN)$(TEST)

$(BIN)$(EXEC): $(OBJ)main.o $(OBJ)carte.o $(OBJ)interface.o $(OBJ)plateau.o $(OBJ)structure.o $(OBJ)structureEngine.o 
	$(CC) $^ -o $@ $(LDFLAGS)

$(OBJ)main.o: $(SRC)main.c $(HEADER)interface.h
	$(CC) -c $(SRC)main.c -o $@ $(CFLAGS)

$(OBJ)carte.o : $(SRC)carte.c $(HEADER)carte.h $(HEADER)plateau.h
	$(CC) -c $(SRC)carte.c -o $@ $(CFLAGS)

$(OBJ)interface.o : $(SRC)interface.c $(HEADER)interface.h $(HEADER)plateau.h $(HEADER)carte.h
	$(CC) -c $(SRC)interface.c -o $@ $(CFLAGS)

$(OBJ)plateau.o : $(SRC)plateau.c $(HEADER)plateau.h $(HEADER)structure.h $(HEADER)carte.h
	$(CC) -c $(SRC)plateau.c -o $@ $(CFLAGS)

$(OBJ)structure.o : $(SRC)structure.c $(HEADER)structure.h $(HEADER)structureEngine.h
	$(CC) -c $(SRC)structure.c -o $@ $(CFLAGS)
	
$(OBJ)structureEngine.o : $(SRC)structureEngine.c $(HEADER)structureEngine.h
	$(CC) -c $(SRC)structureEngine.c -o $@ $(CFLAGS)


$(BIN)$(TEST): $(OBJ)unitTest.o $(OBJ)carte.o $(OBJ)interface.o $(OBJ)plateau.o $(OBJ)structure.o $(OBJ)structureEngine.o
	$(CC) $^ -lcunit -o $@ $(LDFLAGS)

$(OBJ)unitTest.o : $(SRC)unitTest.c $(HEADER)structureEngine.h $(HEADER)plateau.h
	$(CC) -c $(SRC)unitTest.c -o $@ $(CFLAGS)

mrproper: clean
	rm -rf $(BIN)*

clean: 
	rm -rf $(OBJ)*