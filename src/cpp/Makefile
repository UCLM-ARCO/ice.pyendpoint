# -*- mode: makefile-gmake; coding: utf-8 -*-

CXX        = g++

# DEBUG_OPS += -DEXTRA_DEBUG
# DEBUG_OPS += -DDEBUG -ggdb

CXXFLAGS   = -I. -Wall $$(python-config --includes) $(DEBUG_OPS)
LDFLAGS    = -L. $$(python-config --ldflags) \
	     -W1,--export-dynamic -fPIC -shared

OBJS       = PluginI.o Instance.o EndpointI.o PyFunctions.o ConnectorsCallback.o \
	     ConnectorI.o TransceiverI.o
LIB        = libIcePyEndpoint.so.34


all: $(LIB)

$(LIB): $(OBJS)
	$(CXX) $(LDFLAGS)  -o $@ $^
	ln -sf $@ $(LIB:%.34=%)


.PHONY: clean
clean:
	$(RM) -vrf *~ *.o *.so *.so.*
