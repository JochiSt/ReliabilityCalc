BUSSES+=src

CFLAGS=-fPIC -Wall 
CFLAGS+=-I../include
#CFLAGS+=-g

LDFLAGS+=

GPP=g++
CC=gcc

SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o )

.PHONY: all clean doc $(BUSSES)

all:	$(OBJS)
	@echo " ALL DONE. $@"

$(PROGRAM):	$(PROGRAM).o $(OBJECTS) $(BUSSES)
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
	doxygen ../Doxyfile

clean:
	@echo " CLEAN"
	@rm -f *.o
	@echo " CLEAN."

allclean:
	@echo " CLEAN ALL"
	@for dir in $(BUSSES); do ( cd $$dir; $(MAKE) allclean; ); done
	@rm -f $(LIBNAME)
	@rm -f *.o
	@echo " CLEAN."
