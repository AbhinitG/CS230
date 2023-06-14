CC = clang
CFLAGS = -std=c11 -Wall -Wextra
LDLIBS = -lpthread

PROG = client
OBJS = client.o

.PHONY: all clean

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(PROG) $(OBJS)