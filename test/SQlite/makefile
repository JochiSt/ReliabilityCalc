BUSSES+=

CFLAGS=-fPIC -Wall 
CFLAGS+=
#CFLAGS+=-g

LDFLAGS+=-lsqlite3

GPP=g++
CC=gcc

PROGRAM = sqlite

SRCS=$(wildcard src/*.cpp)
OBJECTS = $(SRCS:.cpp=.o)

.PHONY: all clean doc $(BUSSES)

all:	$(PROGRAM)
	@echo " ALL DONE. $@"

$(PROGRAM):	$(BUSSES) $(OBJECTS) $(PROGRAM).o
	@echo -n ">>> Linking   "
	$(GPP)  -o $(PROGRAM) $(OBJECTS) $(PROGRAM).o $(LDFLAGS)

$(BUSSES):
	@cd $@; $(MAKE);

%.o:	%.c | %.h
	@echo -e -n " cc $<:\t";
	$(CC) -c $< $(CFLAGS)

%.o:	%.cc | %.hh
	@echo -e -n " cc $<:\t";
	$(GPP) -c $< $(CFLAGS)

%.o:	%.cpp | %.h
	@echo -e -n " CC $<:\t";
	$(GPP) -c $< $(CFLAGS)  

%.o:	%.cpp
	@echo -e -n " CC $<:\t";
	$(GPP) -c $< $(CFLAGS)

doc:
	@echo " creating documentation"
	doxygen doxygen/doxyfile

clean:
	@echo " CLEAN"
	@rm -f *.o
	@rm -f src/*.o
	@echo " CLEAN."
