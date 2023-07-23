CFLAGS=-std=gnu++11 -pedantic -Wall -Werror -ggdb3
PROGS=container1 container2 container3 container4
OBJS=$(patsubst %,%.o,$(PROGS)) container.o
all: $(PROGS)
container%: container%.o
	g++ -o $@ $^
%.o: %.cpp
	g++ $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f *~ $(PROGS) $(OBJS)

container.o: container.hpp



