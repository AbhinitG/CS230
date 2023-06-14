CC = clang
CFLAGS = -std=c11 -Wall -Wextra
LDLIBS = -lpthread

PROG = worldcup
OBJS = worldcup.o

.PHONY: all clean

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(PROG) $(OBJS)