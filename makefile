ifeq ($(OS),Windows_NT)
	uname_S := Windows
	WinBuild = 1
	BFLAGS= -DWinBuild
else 
	uname_S := $(shell uname -s)
	BFLAGS= 	
endif

# Declaration of variables
CC = gcc
CC_FLAGS = -w -g


server: server.o
	$(CC) server.o -o server

### Build stuff
# To obtain object files
%.o: %.c
	$(CC) -c $(CC_FLAGS) $(BFLAGS) $< -o $@

clean:
	rm -rf server *.o
