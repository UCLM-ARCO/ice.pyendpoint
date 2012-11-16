# -*- mode: python; coding: utf-8 -*-

import sys
import socket


ENDPOINT_TYPE = 10
ENDPOINT_PROTO = "example"


class StdoutLogger(object):
    lastindex = 0

    def __init__(self, header="", index=0):
        self.header = header
        self.index = index
        self.lastindex = index

    def __del__(self):
        self.lastindex -= 1
        if self.lastindex == 0:
            sys.stdout.write("\n")

    def __lshift__(self, msg):
        sys.stdout.write(self.header + str(msg))
        return StdoutLogger(index=self.index + 1)


log = StdoutLogger("PYTHON: ")


class EndpointFactoryI(object):
    def __init__(self):
        log << "EndpointFactoryI.__init__()"

    def __del__(self):
        log << "EndpointFactoryI.__del__()"

    def type(self):
        log << "EndpointFactoryI.type()"
        return ENDPOINT_TYPE

    def protocol(self):
        log << "EndpointFactoryI.protocol()"
        return ENDPOINT_PROTO

    def create(self, strEndpoint, oaEndpoint):
        log << "EndpointFactoryI.create('{}', '{}')".format(
            strEndpoint, oaEndpoint)

        return EndpointI(strEndpoint)

    def destroy(self):
        log << "EndpointFactoryI.destroy()"


class EndpointI(object):
    def __init__(self, strEndpoint):
        log << "EndpointI.__init__()"
        self.strEndpoint = strEndpoint

    def __del__(self):
        log << "EndpointI.__del__()"

    def __lt__(self, other):
        log << "EndpointI.__lt__(other)", id(self), id(other)
        return id(self) < id(other)

    def toString(self):
        log << "EndpointI.toString()"
        return ENDPOINT_PROTO + self.strEndpoint

    def getCompress(self):
        log << "EndpointI.getCompress()"
        return 0

    def setCompress(self, compress):
        log << "EndpointI.setCompress()"
        return self

    def datagram(self):
        log << "EndpointI.datagram()"
        return True

    def secure(self):
        log << "EndpointI.secure()"
        return False

    def transceiver(self):
        log << "EndpointI.transceiver(endp)"

        # If no acceptor needed, create new endpoint (or reuse this,
        # I'm not sure if will work) and new transceiver, and return
        # both (endp, transceiver). Otherwise, return this endpoint,
        # and None as transceiver

        return self, None

    def connectors_async(self, callback):
        log << "EndpointI.connectors_async()"
        connectors = [ConnectorI()]
        callback.connectors(connectors)


class ConnectorI(object):
    def __init__(self):
        log << "ConnectorI.__init__()"

    def __lt__(self, other):
        log << "Connector.__lt__(other)", id(self), id(other)
        return id(self) < id(other)

    def connect(self):
        log << "Connector.connect()"
        return TransceiverI()


class TransceiverI(object):
    def __init__(self):
        log << "TransceiverI.__init__()"
        self.s = socket.socket()
        self.s.connect(("127.0.0.1", 9000))

    def __del__(self):
        log << "TransceiverI.__del__()"

    def toString(self):
        log << "TransceiverI.toString()"
        return "WHAT?"

    def type(self):
        log << "TransceiverI.type()"
        return "example"

    def fd(self):
        log << "TransceiverI.fd()"
        return self.s.fileno()

    def initialize(self, retvals):
        log << "TransceiverI.initialize()"
        return retvals['SocketOperationNone']

    def write(self, data):
        log << "TransceiverI.write(data)"
        self.s.send(data)
        return True

    def close(self):
        log << "TransceiverI.close()"
        self.s.close()

