BUSSES+=src

CFLAGS=-fPIC -Wall 
CFLAGS+=-I../include
CFLAGS+=-g
CFLAGS+=-std=c++11

LDFLAGS+=

GPP=g++
CC=gcc

SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o )

.PHONY: all clean doc $(BUSSES)

all:	$(OBJS)
	@echo " ALL DONE. $@"

$(BUSSES):
	@cd $@; $(MAKE);

%.o:	%.c | %.h
	$(CC) -c $< $(CFLAGS)

%.o:	%.cc | %.hh
	$(GPP) -c $< $(CFLAGS)

%.o:	%.cpp | %.h
	$(GPP) -c $< $(CFLAGS)  

%.o:	%.cpp
	$(GPP) -c $< $(CFLAGS)

clean:
	@echo " CLEAN"
	@rm -f *.o
	@echo " CLEAN."

