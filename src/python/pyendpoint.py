# -*- mode: python; coding: utf-8 -*-

import sys


class StdoutLogger(object):
    lastindex = 0

    def __init__(self, header="", index=0, activated=False):
        self.header = header
        self.index = index
        self.lastindex = index
        self.activated = activated

    def write(self, msg):
        if self.activated:
            sys.stdout.write(msg)

    def __del__(self):
        self.lastindex -= 1
        if self.lastindex == 0:
            self.write("\n")

    def __lshift__(self, msg):
        self.write(self.header + str(msg))
        return StdoutLogger(
            index=self.index + 1, activated=self.activated)


log = StdoutLogger("PYTHON: ")


class EndpointFactoryI(object):
    def __init__(self, typeNo, protocol):
        log << "EndpointFactoryI.__init__()"
        self._typeNo = typeNo
        self._protocol = protocol

    def __del__(self):
        log << "EndpointFactoryI.__del__()"

    def type(self):
        log << "EndpointFactoryI.type()"
        return self._typeNo

    def protocol(self):
        log << "EndpointFactoryI.protocol()"
        return self._protocol

    def create(self, strEndpoint, oaEndpoint):
        log << "EndpointFactoryI.create('{}', '{}')".format(
            strEndpoint, oaEndpoint)

        return EndpointI(self._protocol, strEndpoint)

    def destroy(self):
        log << "EndpointFactoryI.destroy()"


class EndpointI(object):
    def __init__(self, protocol, strEndpoint):
        log << "EndpointI.__init__()"
        self._protocol = protocol
        self._strEndpoint = strEndpoint

    def __del__(self):
        log << "EndpointI.__del__()"

    def __lt__(self, other):
        log << "EndpointI.__lt__(other)", id(self), id(other)
        return id(self) < id(other)

    def toString(self):
        log << "EndpointI.toString()"
        return self._protocol + self._strEndpoint

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
        endp = EndpointI(self._protocol, self._strEndpoint)
        trans = TransceiverI(self._protocol)
        return endp, trans

    def connectors_async(self, callback):
        log << "EndpointI.connectors_async()"
        connectors = [ConnectorI(self._protocol)]
        callback.connectors(connectors)

    def expand(self):
        log << "EndpointI.expand()"
        return [self]


class ConnectorI(object):
    def __init__(self, protocol):
        log << "ConnectorI.__init__()"
        self._protocol = protocol

    def __lt__(self, other):
        log << "ConnectorI.__lt__(other)", id(self), id(other)
        return id(self) < id(other)

    def connect(self):
        log << "ConnectorI.connect()"
        return TransceiverI(self.protocol, True)


class TransceiverI(object):
    def __init__(self, protocol, connect=False):
        log << "TransceiverI.__init__()"
        self._protocol = protocol

    def __del__(self):
        log << "TransceiverI.__del__()"

    def toString(self):
        log << "TransceiverI.toString()"
        return "undefined"

    def type(self):
        log << "TransceiverI.type()"
        return self._protocol

    def fd(self):
        log << "TransceiverI.fd()"
        return -1

    def initialize(self, retvals):
        log << "TransceiverI.initialize()"
        return retvals['SocketOperationNone']

    def getMaxPaquetSize(self):
        log << "TransceiverI.getMaxPaquetSize()"
        return 256

    def write(self, buff):
        log << "TransceiverI.write(buff)"
        return True

    def read(self, buff):
        log << "TransceiverI.read(buff)"
        return True, 0

    def close(self):
        log << "TransceiverI.close()"
