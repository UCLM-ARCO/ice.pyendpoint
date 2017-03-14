# -*- mode: makefile-gmake; coding: utf-8 -*-

CXX        = g++

# If segfault...
# DEBUG_OPS += -DEXTRA_DEBUG
DEBUG_OPS += -DDEBUG
DEBUG_OPS += -ggdb

VER        = 36
LIB        = libIcePyEndpoint.so.$(VER)
CXXFLAGS   = -I. -IIcePy -Wall $$(python3-config --includes) $(DEBUG_OPS) -fPIC
LDFLAGS    = -L. $$(python3-config --ldflags) \
	     -Wl,-soname,$(LIB) -fPIC -shared \
	     -Wl,--no-undefined

LDLIBS     = $$(python3-config --libs) \
	    -lIce -lIceUtil -lSlice -lIceSSL

OBJS       = PyFunctions.o \
	     PyEndpointI.o \
	     PyTransceiver.o \
	     PyAcceptor.o \
	     PyConnectorsCallback.o \
	     PyConnector.o \
	     PyCommunicator.o \
	     PyBasicStream.o

vpath %.cpp IcePy


all: $(LIB)

$(LIB): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)
	ln -sf $@ $(LIB:%.$(VER)=%)

install: all
	install -d $(DESTDIR)/usr/lib
	install -m 644 $(LIB) $(DESTDIR)/usr/lib
	ln -sf $(LIB) $(DESTDIR)/usr/lib/$(LIB:%.$(VER)=%)


.PHONY: clean
clean:
	$(RM) -vr *~ *.o *.so *.so.*
