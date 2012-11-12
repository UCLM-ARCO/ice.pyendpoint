# -*- mode: python; coding: utf-8 -*-

ENDPOINT_TYPE = 10

class EndpointFactory(object):
    def type(self):
        print "PYTHON EndpointFactory.type()"
        return ENDPOINT_TYPE

    def protocol(self):
        print "PYTHON EndpointFactory.protocol()"
        return "example"


