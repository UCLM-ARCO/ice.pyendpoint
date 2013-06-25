# -*- mode: python; coding: utf-8 -*-

ENDPOINT_TYPE = 20
ENDPOINT_PROTO = "test"


class EndpointFactoryI(object):
    def __init__(self, ic):
        self._ic = ic

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
        self.strEndpoint = strEndpoint

    def toString(self):
        return ENDPOINT_PROTO + self.strEndpoint
