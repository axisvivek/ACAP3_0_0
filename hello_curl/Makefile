PROGS = hellocurl
SRCS  = hello_curl.c
OBJS  = $(SRCS:.c=.o)
all: $(PROGS)
$(PROGS): $(OBJS)
	$(CC) $^ -o $@
clean:
	rm -f $(PROGS) *.o