# -*- mode: python; coding: utf-8 -*-

import socket
from pyendpoint import EndpointFactoryI, EndpointI, ConnectorI, TransceiverI

from pyendpoint import log
# log.activated = True


class MyEndpointFactoryI(EndpointFactoryI):
    def __init__(self, communicator):
        EndpointFactoryI.__init__(self, communicator)
        self._type = 10
        self._protocol = "example"

    def create(self, strEndpoint, oaEndpoint):
        return MyEndpointI(self._communicator, self._protocol, strEndpoint)


class MyEndpointI(EndpointI):
    def transceiver(self):
        endp = MyEndpointI(
            self._communicator, self._protocol, self._strEndpoint)
        trans = MyTransceiverI(self._communicator, self._protocol, False)
        return endp, trans

    def connectors_async(self, callback):
        connectors = [MyConnectorI(self._communicator, self._protocol)]
        callback.connectors(connectors)


class MyConnectorI(ConnectorI):
    def connect(self):
        return MyTransceiverI(self._communicator, self._protocol, True)


class MyTransceiverI(TransceiverI):
    def __init__(self, communicator, protocol, connect=False):
        log << "TransceiverI.__init__()"
        TransceiverI.__init__(self, communicator, protocol, connect)

        self.s = socket.socket(type=socket.SOCK_DGRAM)
        if connect:
            self.s.connect(("127.0.0.1", 9000))
        else:
            self.s.bind(("127.0.0.1", 9000))

    def toString(self):
        log << "TransceiverI.toString()"
        return "example -h 127.0.0.1 -p 9000"

    def fd(self):
        log << "TransceiverI.fd()"
        return self.s.fileno()

    def write(self, buff):
        log << "TransceiverI.write()"
        self.s.send(buff)
        return True

    def read(self, buff):
        log << "TransceiverI.read()"
        size = self.s.recv_into(buff, len(buff))
        return True, size

    def close(self):
        log << "TransceiverI.close()"
        self.s.close()
