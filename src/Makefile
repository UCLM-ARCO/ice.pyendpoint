# -*- mode: makefile-gmake; coding: utf-8 -*-

CXX      = g++
CXXFLAGS = -ggdb
LDFLAGS  = -L.

OBJS     = PluginI.o Instance.o EndpointI.o
LIB      = libIcePyEndpoint.so.34


all: $(LIB)

$(LIB): $(OBJS)
	$(CXX) -o $@ -fPIC -shared $^
	ln -sf $@ $(LIB:%.34=%)


.PHONY: clean
clean:
	$(RM) -vrf *~ *.o *.so *.so.*
