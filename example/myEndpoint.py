# -*- mode: python; coding: utf-8 -*-

ENDPOINT_TYPE = 10
ENDPOINT_PROTO = "example"


class EndpointFactoryI(object):
    def __init__(self):
        print "PYTHON: EndpointFactoryI.__init__()"

    def __del__(self):
        print "PYTHON: EndpointFactoryI.__del__()"

    def type(self):
        return ENDPOINT_TYPE

    def protocol(self):
        return ENDPOINT_PROTO

    def create(self, strEndpoint, oaEndpoint):
        return ExampleEndpointI(strEndpoint)

    def destroy(self):
        pass


class ExampleEndpointI(object):
    def __init__(self, strEndpoint):
        print "PYTHON: ExampleEndpointI.__init__()"
        self.strEndpoint = strEndpoint

    def __del__(self):
        print "PYTHON: ExampleEndpointI.__del__()"

    def toString(self):
        return ENDPOINT_PROTO + self.strEndpoint

    def datagram(self):
        return True

    def secure(self):
        return False
