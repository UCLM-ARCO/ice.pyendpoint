# -*- mode: makefile-gmake; coding: utf-8 -*-

CXX        = g++-4.6
PYTHON_VER = python2.7

# If segfault...
# DEBUG_OPS += -DEXTRA_DEBUG
# DEBUG_OPS += -DDEBUG -ggdb

VER        = 35
LIB        = libIcePyEndpoint.so.$(VER)
PYTHON_ICE = /usr/lib/$(PYTHON_VER)/dist-packages/IcePy.so
CXXFLAGS   = -I. -Wall $$(python-config --includes) $(DEBUG_OPS) -fPIC
LDFLAGS    = -L. $$(python-config --ldflags) \
	     -Wl,-soname,$(LIB) -fPIC -shared
LDLIBS     = $$(python-config --libs)

OBJS       = PluginI.o Instance.o EndpointI.o PyFunctions.o \
	     ConnectorsCallback.o ConnectorI.o TransceiverI.o \
	     BasicStream.o AcceptorI.o # $(PYTHON_ICE)

all: $(LIB)

$(LIB): $(OBJS)
	$(CXX) $(LDFLAGS) $(LDLIBS) -o $@ $^
	ln -sf $@ $(LIB:%.$(VER)=%)

install: all
	install -d $(DESTDIR)/usr/lib
	install -m 644 $(LIB) $(DESTDIR)/usr/lib
	ln -sf $(LIB) $(DESTDIR)/usr/lib/$(LIB:%.$(VER)=%)
	ln -sf $(PYTHON_ICE) $(DESTDIR)/usr/lib/IcePy.so.$(VER)


.PHONY: clean
clean:
	$(RM) -vrf *~ *.o *.so *.so.*
