BUSSES+=src

CFLAGS=-fPIC 
CFLAGS+=-Wall 
CFLAGS+=-Iinclude/
CFLAGS+=-g
#CFLAGS+=-fpermissive

LDFLAGS+=-lsqlite3 -lgsl -lgslcblas -lm
LDFLAGS+=-L. -lReliability
LDFLAGS+=$(shell curl-config --libs)

###############################################################################
# library....
# use $$HOME directory as default location
# (do not check in something like LIB_INSTALL_PATH=/home/t2k_user as it
# will break the build for everybody at the next update)
LIB_INSTALL_PATH=$(HOME)/lib
INC_INSTALL_PATH=$(HOME)/include/liblab

LIBNAME=libReliability.a

##############################################################################
# compiler selection
GPP=g++
CC=gcc
AR=ar

##############################################################################

PROGRAM = main
PROGRAM_2 = main_PowerBoard
PROGRAM_3 = main_GCU
PROGRAM_4 = main_BASE_Hamamatsu
#PROGRAM_5 = main_TsinghuaFMC
PROGRAM_6 = main_ESS
PROGRAM_7 = main_HVU

SRCS=$(wildcard src/*.cpp)
OBJECTS = $(SRCS:.cpp=.o)

.PHONY: all clean doc lib install $(BUSSES)

all:	lib $(PROGRAM) $(PROGRAM_2) $(PROGRAM_3) $(PROGRAM_4) $(PROGRAM_5) $(PROGRAM_6) $(PROGRAM_7)
	@echo " ALL DONE. $@"

$(PROGRAM):	lib $(PROGRAM).o
	@echo -n ">>> Linking   "
	$(GPP)  -o $(PROGRAM) $(PROGRAM).o $(LDFLAGS)

$(PROGRAM_2):	lib $(PROGRAM_2).o
	@echo -n ">>> Linking   "
	$(GPP)  -o $(PROGRAM_2) $(PROGRAM_2).o $(LDFLAGS)

$(PROGRAM_3):	lib $(PROGRAM_3).o
	@echo -n ">>> Linking   "
	$(GPP)  -o $(PROGRAM_3) $(PROGRAM_3).o $(LDFLAGS)

$(PROGRAM_4):	lib $(PROGRAM_4).o
	@echo -n ">>> Linking   "
	$(GPP)  -o $(PROGRAM_4) $(PROGRAM_4).o $(LDFLAGS)

$(PROGRAM_5):	lib $(PROGRAM_5).o
	@echo -n ">>> Linking   "
	$(GPP)  -o $(PROGRAM_5) $(PROGRAM_5).o $(LDFLAGS)

$(PROGRAM_6):	lib $(PROGRAM_6).o
	@echo -n ">>> Linking   "
	$(GPP)  -o $(PROGRAM_6) $(PROGRAM_6).o $(LDFLAGS)

$(PROGRAM_7):	lib $(PROGRAM_7).o
	@echo -n ">>> Linking   "
	$(GPP)  -o $(PROGRAM_7) $(PROGRAM_7).o $(LDFLAGS)

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

lib:	$(BUSSES)
	rm -f $(LIBNAME)
	@echo -en " LIB:\t"
	$(AR) rsc $(LIBNAME) `for dir in $(BUSSES); do ( find $$dir -name '*.o'; ); done` 
	@echo -en "\n*** The library now contains following files ***\n"
	@$(AR) tv $(LIBNAME)

doc:
	@echo " creating documentation"
	doxygen doxygen/doxyfile

clean:
	@echo " CLEAN ALL"
	@for dir in $(BUSSES); do ( cd $$dir; $(MAKE) clean; ); done
	@rm -f $(LIBNAME)
	@rm -f libReliability.so
	@rm -f libReliability.a
	@rm -f *.o
	@rm -f src/*.o
	@echo " CLEAN."
