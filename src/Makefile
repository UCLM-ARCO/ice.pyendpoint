# -*- mode: makefile-gmake; coding: utf-8 -*-

CXX     = g++
LDFLAGS = -L.

LIB     = libIcePyEndpoint.so.34


all: $(LIB)

$(LIB): PluginI.cpp
	$(CXX) -o $@ -fPIC -shared $^
	ln -s $@ $(LIB:%.34=%)


.PHONY: clean
clean:
	$(RM) -vrf *~ *.o *.so *.so.*
