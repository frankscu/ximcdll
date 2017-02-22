DEBUG        := -g
CXX          := g++
CC           := gcc
LD           := g++
CFLAGS       := -fPIC -O0 -Wall -Wextra -Werror -pedantic -Wno-unused
LDFLAGS      := $(DEBUG)
SOFLAGS      := -shared

#ROOTCINT     := rootcint
ROOTCINT     := rootcling
ROOTCONFIG   := root-config
ROOTCFLAGS   := $(shell $(ROOTCONFIG) --cflags)
ROOTLDFLAGS  := $(shell $(ROOTCONFIG) --ldflags)
ROOTLIBS     := $(shell $(ROOTCONFIG) --libs)
ROOTGLIBS    := $(shell $(ROOTCONFIG) --glibs)
HASTHREAD    := $(shell $(ROOTCONFIG) --has-thread)

CXXFLAGS     += $(ROOTCFLAGS)
#LDFLAGS      += $(ROOTLDFLAGS)
LIBSLIN      := $(ROOTGLIBS) 

#CFLAGS		 += $(CXXFLAGS)
CFLAGS 		 += -F./ximc/macosx
LDFLAGS 	 += -framework libximc -rpath '@executable_path/' -rpath './ximc/macosx'



libname =libtximc
full_libname =$(libname).so

.PHONY : all clean

all : $(full_libname)

$(full_libname) : TXIMC.o tximcDict.o
	$(CXX) -shared -o $@ $(CFLAGS) $(LDFLAGS) -std=c++11 -I$(ROOTSYS)/include $^ $(LIBSLIN)

tximcDict.o: tximcDict.cc
	$(CXX)  $(CFLAGS) -std=c++11 -I$(ROOTSYS)/include -c $< -o $@

tximcDict.cc:  TXIMC.h linkdef.h
	$(ROOTCINT) -f $@ $(CFLAGS) -c $^

TXIMC.o: TXIMC.cpp TXIMC.h 
	$(CXX) -std=c++11 -I$(ROOTSYS)/include $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(full_libname) $(libname)* tximcDict*
