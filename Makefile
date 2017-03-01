CUR_DIR      := $(shell pwd)
SRC_DIR 	 := $(CUR_DIR)/src
INC_DIR 	 := $(CUR_DIR)/include
LIB_DIR 	 := $(CUR_DIR)/lib
DEBUG        := -g
CXX          := g++
CC           := gcc
LD           := g++
CFLAGS       := -fPIC -O0 -Wall -Wextra -Werror -pedantic -Wno-unused
LDFLAGS      := $(DEBUG)
SOFLAGS      := -shared

ROOTCINT     := rootcint
ROOTCONFIG   := root-config
ROOTCFLAGS   := $(shell $(ROOTCONFIG) --cflags)
ROOTLDFLAGS  := $(shell $(ROOTCONFIG) --ldflags)
ROOTLIBS     := $(shell $(ROOTCONFIG) --libs)
ROOTGLIBS    := $(shell $(ROOTCONFIG) --glibs)
HASTHREAD    := $(shell $(ROOTCONFIG) --has-thread)

CXXFLAGS     += $(ROOTCFLAGS)
LIBSLIN      := $(ROOTGLIBS) 

CFLAGS 		 += -F$(LIB_DIR)/ximc/macosx
LDFLAGS 	 += -framework libximc -rpath '$(LIB_DIR)/ximc/macosx'



libname =libtximc
full_libname =$(libname).so

.PHONY : all clean

all : $(LIB_DIR)/$(full_libname)

$(LIB_DIR)/$(full_libname) : $(LIB_DIR)/TXIMC.o $(LIB_DIR)/TXIMCGUI.o $(LIB_DIR)/tximcDict.o
	$(CXX) -shared $(CFLAGS) $(LDFLAGS) -std=c++11 -I$(ROOTSYS)/include $(LIBSLIN) $^ -o $@ 

$(LIB_DIR)/tximcDict.o: $(LIB_DIR)/tximcDict.cc
	$(CXX) $(CFLAGS) -std=c++11 -I$(ROOTSYS)/include -c $< -o $@ 

$(LIB_DIR)/tximcDict.cc: $(INC_DIR)/TXIMC.h $(INC_DIR)/TXIMCGUI.h $(INC_DIR)/linkdef.h
	$(ROOTCINT) -f $@ $(CFLAGS) -c $^ 

$(LIB_DIR)/TXIMC.o: $(SRC_DIR)/TXIMC.cpp $(INC_DIR)/TXIMC.h 

$(LIB_DIR)/TXIMCGUI.o: $(SRC_DIR)/TXIMCGUI.cpp $(INC_DIR)/TXIMCGUI.h 
	$(CXX) -std=c++11 -I$(ROOTSYS)/include -I$(INC_DIR) -c $< -o $@

clean:
	rm -f *.o $(LIB_DIR)/$(full_libname) $(LIBD_DIR)/$(libname)* $(LIB_DIR)/tximcDict*
