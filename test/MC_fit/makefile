BUSSES+=

CFLAGS=-fPIC -Wall 
CFLAGS+=-I../../include/
CFLAGS+=-g
#CFLAGS+=$(shell root-config --cflags)

LDFLAGS+=-lsqlite3 -lgsl -lgslcblas -lm
LDFLAGS+=-L../../ -lReliability
LDFLAGS+=$(shell curl-config --libs)
#LDFLAGS+=$(shell root-config --libs)

##############################################################################
# compiler selection
#GPP=g++ -std=c++0x
GPP=g++
CC=gcc
AR=ar

##############################################################################

PROGRAM = main_testMC

SRCS=$(wildcard src/*.cpp)
OBJECTS = $(SRCS:.cpp=.o)

.PHONY: all clean doc $(BUSSES)

all:	$(PROGRAM) 
	@echo " ALL DONE. $@"

$(PROGRAM):	$(PROGRAM).o
	@echo -n ">>> Linking   "
	$(GPP)  -o $(PROGRAM) $(PROGRAM).o $(LDFLAGS)

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
	@echo " CLEAN ALL"
	@for dir in $(BUSSES); do ( cd $$dir; $(MAKE) clean; ); done
	@rm -f *.o
	@rm -f src/*.o
	@echo " CLEAN."
