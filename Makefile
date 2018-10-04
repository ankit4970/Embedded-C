SRC_DIR = src
INC_DIR = includes
src = $(wildcard $(SRC_DIR)/*.c)
CPPFLAGS = -I$(INC_DIR)
LDFLAGS = -lpthread
CC = gcc

runMe: $(src)
	$(CC) -o $@ $^ $(CPPFLAGS) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f runMe
