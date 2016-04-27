BUSSES+=src

CFLAGS=-fPIC -Wall 
CFLAGS+=-Iinclude/
#CFLAGS+=-g

LDFLAGS+=

GPP=g++
CC=gcc

PROGRAM = main
PROGRAM_2 = main_PowerBoard

OBJECTS = $(wildcard src/*.o)

.PHONY: all clean doc $(BUSSES)

all:	$(PROGRAM) $(PROGRAM_2)
	@echo " ALL DONE. $@"

$(PROGRAM):	$(PROGRAM).o $(OBJECTS) $(BUSSES)
	@echo -n ">>> Linking   "
	$(GPP)  -o $(PROGRAM) $(OBJECTS) $(PROGRAM).o $(LDFLAGS)

$(PROGRAM_2):	$(PROGRAM_2).o $(OBJECTS) $(BUSSES)
	@echo -n ">>> Linking   "
	$(GPP)  -o $(PROGRAM_2) $(OBJECTS) $(PROGRAM_2).o $(LDFLAGS)

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
