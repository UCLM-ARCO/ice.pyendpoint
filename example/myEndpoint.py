# -*- mode: python; coding: utf-8 -*-

ENDPOINT_TYPE = 10
ENDPOINT_PROTO = "example"


class EndpointFactoryI(object):
    def __init__(self):
        print "PYTHON: EndpointFactoryI.__init__()"

    def __del__(self):
        print "PYTHON: EndpointFactoryI.__del__()"

    def type(self):
        print "PYTHON: EndpointFactoryI.type()"
        return ENDPOINT_TYPE

    def protocol(self):
        print "PYTHON: EndpointFactoryI.protocol()"
        return ENDPOINT_PROTO

    def create(self, strEndpoint, oaEndpoint):
        print "PYTHON: EndpointFactoryI.create('{}', '{}')".format(
            strEndpoint, oaEndpoint)

        return ExampleEndpointI(strEndpoint)

    def destroy(self):
        print "PYTHON: EndpointFactoryI.destroy()"


class ExampleEndpointI(object):
    def __init__(self, strEndpoint):
        print "PYTHON: EndpointI.__init__()"
        self.strEndpoint = strEndpoint

    def __del__(self):
        print "PYTHON: EndpointI.__del__()"

    def toString(self):
        print "PYTHON: EndpointI.toString()"
        return ENDPOINT_PROTO + self.strEndpoint

    def datagram(self):
        print "PYTHON: EndpointI.datagram()"
        return True

    def secure(self):
        print "PYTHON: EndpointI.secure()"
        return False

    def connectors_async(self, callback):
        print "PYTHON: EndpointI.connectors_async()"
        connectors = [ConnectorI(), ConnectorI()]
        callback.connectors(connectors)


class ConnectorI(object):
    def __lt__(self, other):
        print "PYTHON: Connector.__lt__(other)", id(self), id(other)
        return id(self) < id(other)

    def connect(self):
        print "PYTHON: Connector.connect()"
        return TransceiverI()


class TransceiverI(object):
    pass
