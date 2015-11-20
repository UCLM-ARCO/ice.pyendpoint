# -*- mode: python; coding: utf-8 -*-

import socket

from pyendpoint import (
    EndpointFactoryI, EndpointI, ConnectorI, TransceiverI, ConnectionInfo,
    Acceptor, log, trace
)

# log.activated = True


class TwowayEndpointFactoryI(EndpointFactoryI):
    def __init__(self, communicator):
        EndpointFactoryI.__init__(self, communicator)
        self._type = 20
        self._protocol = "twowayEndp"

    def create(self, strEndpoint, oaEndpoint):
        return TwowayEndpointI(self._communicator, self._protocol, strEndpoint, oaEndpoint)


class TwowayConnectorI(ConnectorI):
    def __init__(self, communicator, protocol):
        ConnectorI.__init__(self, communicator, protocol)
        self.sock = socket.socket(type=socket.SOCK_STREAM)

    def connect(self):
        self.sock.connect(("127.0.0.1", 9000))
        return TwowayTransceiverI(self._communicator, self._protocol, self.sock, False)


class TwowayAcceptor(Acceptor):
    def __init__(self, communicator, protocol):
        trace()

        Acceptor.__init__(self)
        self._communicator = communicator
        self._protocol = protocol

        self.client = None
        self.sock = socket.socket(type=socket.SOCK_STREAM)
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.sock.bind(("127.0.0.1", 9000))

    def close(self):
        trace()
        self.sock.close()

    def listen(self):
        trace()
        self.sock.listen(1)
        self._fd = self.sock.fileno()

    def accept(self):
        self.client, addr = self.sock.accept()
        self._fd = self.client.fileno()
        return TwowayTransceiverI(self._communicator, self._protocol, self.client, True)


class TwowayEndpointI(EndpointI):
    def transceiver(self):
        trace()
        return self, None

    def connectors_async(self, callback):
        trace()
        connectors = [TwowayConnectorI(self._communicator, self._protocol)]
        callback.connectors(connectors)

    def acceptor(self):
        return self, TwowayAcceptor(self._communicator, self._protocol)

    def datagram(self):
        trace()
        return False


class TwowayTransceiverI(TransceiverI):
    def __init__(self, communicator, protocol, sock, incoming=False):
        trace()

        TransceiverI.__init__(self, communicator, protocol, fd=sock.fileno())
        self.incoming = incoming
        self.sock = sock

    def toString(self):
        trace()
        return "twowayEndp -h 127.0.0.1 -p 9000"

    def getInfo(self):
        adapterName = ""
        connectionId = ""
        return ConnectionInfo(self.incoming, adapterName, connectionId)

    def write(self, buff):
        trace()
        self.sock.send(buff)
        return True

    def read(self, buff):
        trace()
        size = self.sock.recv_into(buff, len(buff))
        return True, size

    def close(self):
        trace()
        self.sock.close()
