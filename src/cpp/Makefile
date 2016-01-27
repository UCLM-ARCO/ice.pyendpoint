# -*- mode: makefile-gmake; coding: utf-8 -*-

CXX        = g++
PYTHON_VER = python2.7

# If segfault...
# DEBUG_OPS += -DEXTRA_DEBUG
# DEBUG_OPS += -DDEBUG -ggdb

VER        = 36
LIB        = libIcePyEndpoint.so.$(VER)
CXXFLAGS   = -I. -IIcePy -Wall $$(python-config --includes) $(DEBUG_OPS) -fPIC
LDFLAGS    = -L. $$(python-config --ldflags) \
	     -Wl,-soname,$(LIB) -fPIC -shared \
	     -Wl,--no-undefined

LDLIBS     = $$(python-config --libs) \
	    -lIce -lIceUtil -lSlice -lIceSSL

OBJS       = PyFunctions.o \
	     PyEndpointI.o \
	     PyTransceiver.o \
	     PyAcceptor.o \
	     PyConnectorsCallback.o \
	     PyConnector.o \
	     PyCommunicator.o

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
