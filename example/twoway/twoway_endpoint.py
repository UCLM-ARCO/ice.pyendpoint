# -*- mode: python; coding: utf-8 -*-

import socket

from pyendpoint import (
    EndpointFactoryI, EndpointI, ConnectorI, TransceiverI, ConnectionInfo,
    Acceptor, log
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
        log << "TwowayAcceptor.__init__()"

        Acceptor.__init__(self)
        self._communicator = communicator
        self._protocol = protocol

        self.client = None
        self.sock = socket.socket(type=socket.SOCK_STREAM)
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.sock.bind(("127.0.0.1", 9000))

    def close(self):
        log << "TwowayAcceptor.close()"
        self.sock.close()

    def listen(self):
        log << "TwowayAcceptor.listen()"
        self.sock.listen(1)
        self._fd = self.sock.fileno()

    def accept(self):
        self.client, addr = self.sock.accept()
        self._fd = self.client.fileno()
        return TwowayTransceiverI(self._communicator, self._protocol, self.client, True)


class TwowayEndpointI(EndpointI):
    def transceiver(self):
        log << "EndpointI.transceiver()"
        return self, None

    def connectors_async(self, callback):
        log << "EndpointI.connectors_async()"
        connectors = [TwowayConnectorI(self._communicator, self._protocol)]
        callback.connectors(connectors)

    def acceptor(self):
        return self, TwowayAcceptor(self._communicator, self._protocol)

    def datagram(self):
        log << "EndpointI.datagram()"
        return False


class TwowayTransceiverI(TransceiverI):
    def __init__(self, communicator, protocol, sock, incoming=False):
        log << "TransceiverI.__init__()"

        TransceiverI.__init__(self, communicator, protocol, fd=sock.fileno())
        self.incoming = incoming
        self.sock = sock

    def toString(self):
        log << "TransceiverI.toString()"
        return "twowayEndp -h 127.0.0.1 -p 9000"

    def getInfo(self):
        adapterName = ""
        connectionId = ""
        return ConnectionInfo(self.incoming, adapterName, connectionId)

    def write(self, buff):
        log << "TransceiverI.write()"
        self.sock.send(buff)
        return True

    def read(self, buff):
        log << "TransceiverI.read()"
        size = self.sock.recv_into(buff, len(buff))
        return True, size

    def close(self):
        log << "TransceiverI.close()"
        self.sock.close()




