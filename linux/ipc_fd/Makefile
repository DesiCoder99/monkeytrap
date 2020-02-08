INCDIR =.
CC=gcc

CFLAGS=-I$(INCDIR)

LIBS=-lrt

DEPS = send_fd.h
OBJS = efd.o send_fd.o 
TARGETS = efd

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGETS): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *.o *~ core $(TARGETS)

