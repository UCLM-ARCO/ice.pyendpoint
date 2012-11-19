# -*- mode: makefile-gmake; coding: utf-8 -*-

CXX        = g++

# DEBUG_OPS += -DEXTRA_DEBUG
# DEBUG_OPS += -DDEBUG -ggdb

LIB        = libIcePyEndpoint.so.34

CXXFLAGS   = -I. -Wall $$(python-config --includes) $(DEBUG_OPS) -fPIC
LDFLAGS    = -L. $$(python-config --ldflags) \
	     -Wl,-soname,$(LIB) -fPIC -shared

OBJS       = PluginI.o Instance.o EndpointI.o PyFunctions.o ConnectorsCallback.o \
	     ConnectorI.o TransceiverI.o


all: $(LIB)

$(LIB): $(OBJS)
	$(CXX) $(LDFLAGS)  -o $@ $^
	ln -sf $@ $(LIB:%.34=%)

install: all
	install -d $(DESTDIR)/usr/lib
	install -m 644 $(LIB) $(DESTDIR)/usr/lib
	ln -sf $(LIB) $(DESTDIR)/usr/lib/$(LIB:%.34=%)


.PHONY: clean
clean:
	$(RM) -vrf *~ *.o *.so *.so.*
