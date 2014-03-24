# -*- mode: python; coding: utf-8 -*-

import socket

from pyendpoint import (
     EndpointFactoryI, EndpointI, ConnectorI, TransceiverI, ConnectionInfo,
     log
)

# # log.activated = True


class TwowayEndpointFactoryI(EndpointFactoryI):
    def __init__(self, communicator):
        EndpointFactoryI.__init__(self, communicator)
        self._type = 20
        self._protocol = "twowayEndp"

    def create(self, strEndpoint, oaEndpoint):
        return TwowayEndpointI(self._communicator, self._protocol, strEndpoint, oaEndpoint)


class TwowayEndpointI(EndpointI):
    def transceiver(self):
        endp = TwowayEndpointI(
            self._communicator, self._protocol, self._strEndpoint, self._oaEndpoint)
        trans = TwowayTransceiverI(self._communicator, self._protocol, False)
        return endp, trans

#     def connectors_async(self, callback):
#         connectors = [TwowayConnectorI(self._communicator, self._protocol)]
#         callback.connectors(connectors)


# class TwowayConnectorI(ConnectorI):
#     def connect(self):
#         return TwowayTransceiverI(self._communicator, self._protocol, True)


class TwowayTransceiverI(TransceiverI):
    def __init__(self, communicator, protocol, connect=False):
        log << "TransceiverI.__init__()"
        TransceiverI.__init__(self, communicator, protocol, connect)

        self.s = socket.socket(type=socket.SOCK_STREAM)
        if connect:
            self.incoming = False
            self.s.connect(("127.0.0.1", 9000))
        else:
            self.incoming = True
            self.s.bind(("127.0.0.1", 9000))

    def toString(self):
        log << "TransceiverI.toString()"
        return "twowayEndp -h 127.0.0.1 -p 9000"

#     def getInfo(self):
#         adapterName = ""
#         connectionId = ""
#         return ConnectionInfo(self.incoming, adapterName, connectionId)

    def fd(self):
        log << "TransceiverI.fd()"
        return self.s.fileno()

#     def write(self, buff):
#         log << "TransceiverI.write()"
#         self.s.send(buff)
#         return True

#     def read(self, buff):
#         log << "TransceiverI.read()"
#         size = self.s.recv_into(buff, len(buff))
#         return True, size

    def close(self):
        log << "TransceiverI.close()"
        self.s.close()




