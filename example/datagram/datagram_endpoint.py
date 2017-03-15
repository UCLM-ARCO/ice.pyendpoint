# -*- mode: python; coding: utf-8 -*-

import socket

from pyendpoint import (
    EndpointFactoryI,
    EndpointI,
    ConnectorI,
    TransceiverI,
    ConnectionInfo,
    log,
    trace
)

log.activated = False


class DatagramEndpointFactoryI(EndpointFactoryI):
    def __init__(self, communicator):
        trace()
        EndpointFactoryI.__init__(self, communicator)

        self._type = 10
        self._protocol = "datagramEndp"

    def create(self):
        trace()
        return DatagramEndpointI(self._communicator, self._protocol)


class DatagramEndpointI(EndpointI):
    def initWithOptions(self, args, oaEndpoint):
        trace()

        self.oaEndpoint = oaEndpoint
        self.p1_param = ""

        try:
            i = args.index("-p1")
            if i + 1 < len(args):
                self.p1_param = args[i + 1]
        except ValueError:
            pass

    def options(self):
        trace()

        retval = ""
        if self.p1_param:
            retval += " -p1 {}".format(self.p1_param)

        return retval

    def transceiver(self):
        trace()
        return DatagramTransceiverI(self._communicator, self._protocol, False)

    def endpoint(self, trans):
        trace()

        args = []
        if self.p1_param:
            args.append("-p1")
            args.append(self.p1_param)

        endp = DatagramEndpointI(self._communicator, self._protocol)
        endp.initWithOptions(args, self.oaEndpoint)
        return endp

    def datagram(self):
        trace()
        return True

    def connectors_async(self, callback):
        trace()

        connectors = [DatagramConnectorI(self._communicator, self._protocol)]
        callback.connectors(connectors)


class DatagramConnectorI(ConnectorI):
    def connect(self):
        trace()
        return DatagramTransceiverI(self._communicator, self._protocol, True)


class DatagramTransceiverI(TransceiverI):
    def __init__(self, communicator, protocol, connect=False):
        trace()

        TransceiverI.__init__(self, communicator, protocol, connect)
        self._incoming = not connect
        self._s = socket.socket(type=socket.SOCK_DGRAM)
        self._fd = self._s.fileno()

        if self._connect:
            self._s.connect(("127.0.0.1", 9000))

    def bind(self):
        trace()
        self._s.bind(("127.0.0.1", 9000))

    def toString(self):
        trace()
        return "datagramEndp -h 127.0.0.1 -p 9000"

    def getInfo(self):
        adapterName = ""
        connectionId = ""
        return ConnectionInfo(self._incoming, adapterName, connectionId)

    def write(self, buff):
        trace()

        self._s.send(buff)
        return True

    def read(self, buff):
        trace()
        size = self._s.recv_into(buff, len(buff))
        return True, size

    def close(self):
        trace()
        self._s.close()
