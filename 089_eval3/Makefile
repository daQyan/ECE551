CCFLAGS=--std=gnu++ -pedantic -Wall -Werror -ggdb3
PROGS=cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4
OBJS=$(patsubst %,%.o,$(PROGS)) onePage.o styBook.o
all: $(PROGS)
cyoa-step%: cyoa-step%.o onePage.o styBook.o
	g++ -o $@ $^
%.o: %.cpp
	g++ $(CFLAGS) -c $<
.PHONY: clean
clean:
	rm -f *~ $(PROGS) $(OBJS)
onePage.o: onePage.hpp
styBook.o: styBook.hpp