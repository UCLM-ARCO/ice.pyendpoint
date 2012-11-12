# -*- mode: makefile-gmake; coding: utf-8 -*-

CXX      = g++

CXXFLAGS = -I. -Wall $$(python-config --includes) -ggdb
LDFLAGS  = -L. $$(python-config --ldflags)


OBJS     = PluginI.o Instance.o EndpointI.o PyFunctions.o
LIB      = libIcePyEndpoint.so.34


all: $(LIB)

$(LIB): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ -fPIC -shared $^
	ln -sf $@ $(LIB:%.34=%)


.PHONY: clean
clean:
	$(RM) -vrf *~ *.o *.so *.so.*
