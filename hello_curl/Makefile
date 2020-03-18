PROGS = hello_curl
SRCS  = hello_curl.c




CFLAGS=-I$(IDIR)
OBJS  = $(SRCS:.c=.o)
all: $(PROGS)
$(PROGS): $(OBJS)
	$(CC) $^ -o $@ -lcurl
clean:
	rm -f $(PROGS) *.o