PROGS = helloworld
SRCS  = hello_world.c
OBJS  = $(SRCS:.c=.o)
all: $(PROGS)
$(PROGS): $(OBJS)
	$(CC) $^ -o $@
clean:
	rm -f $(PROGS) *.o