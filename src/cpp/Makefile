# -*- mode: makefile-gmake; coding: utf-8 -*-

CXX        = g++
PYTHON_VER = python2.7

# If segfault...
# DEBUG_OPS += -DEXTRA_DEBUG
DEBUG_OPS += -DDEBUG -ggdb

VER        = 36
LIB        = libIcePyEndpoint.so.$(VER)
PYTHON_ICE = /usr/lib/$(PYTHON_VER)/dist-packages/IcePy.so
CXXFLAGS   = -I. -IIcePy -Wall $$(python-config --includes) $(DEBUG_OPS) -fPIC
LDFLAGS    = -L. $$(python-config --ldflags) \
	     -Wl,-soname,$(LIB) -fPIC -shared \
	     -Wl,--no-undefined -L/home/oscar/repos/ice36-arco/src/python/python

LDLIBS     = $$(python-config --libs) \
	    -lIcePy -lIce -lIceUtil -lSlice -lIceSSL


ICEPY_OBJS = Communicator.o \
	     Util.o \
	     Properties.o \
	     Logger.o \
	     Thread.o Operation.o BatchRequestInterceptor.o ObjectFactory.o \
	     Proxy.o Endpoint.o EndpointInfo.o ObjectAdapter.o PropertiesAdmin.o \
	     ImplicitContext.o Types.o Current.o Connection.o ConnectionInfo.o

OBJS       = $(ICEPY_OBJS) \
	     PyFunctions.o \
	     PyEndpointI.o \
	     PyTransceiver.o \
	     PyAcceptor.o \
	     PyConnectorsCallback.o \
	     PyConnector.o \

	     # $(PYTHON_ICE) \
	     # EndpointFactoryManager.o \
	     # OpaqueEndpointI.o \
	     # Instance.o \
	     # Instance.o \
             # EndpointI.o \
             # PyFunctions.o \
	     # ConnectorsCallback.o \
             # ConnectorI.o \
	     # TransceiverI.o \
	     # BasicStream.o \
	     # AcceptorI.o \

vpath %.cpp IcePy


all: $(LIB)

$(LIB): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)
	ln -sf $@ $(LIB:%.$(VER)=%)

install: all
	install -d $(DESTDIR)/usr/lib
	install -m 644 $(LIB) $(DESTDIR)/usr/lib
	ln -sf $(LIB) $(DESTDIR)/usr/lib/$(LIB:%.$(VER)=%)
	ln -sf $(PYTHON_ICE) $(DESTDIR)/usr/lib/IcePy.so.$(VER)


.PHONY: clean
clean:
	$(RM) -vr *~ *.o *.so *.so.*
