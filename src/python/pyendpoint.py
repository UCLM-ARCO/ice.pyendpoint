# -*- mode: python; coding: utf-8 -*-

# Note: do not remove imoprt Ice: if the endpoint is loaded on C++,
# both 'engines' (c++ and python) should be connected.

import Ice
import sys

import inspect


class log(object):
    activated = False


def trace():
    if not log.activated:
        return

    curframe = inspect.currentframe()
    callframe = inspect.getouterframes(curframe, 2)
    path, line, method = callframe[1][1:4]

    print "PYTHON: {}:{} {}".format(path, line, method)
    sys.stdout.flush()


class EndpointFactoryI(object):
    def __init__(self, communicator):
        trace()

        self._communicator = communicator
        self._type = -1
        self._protocol = ""

    def __del__(self):
        trace()

    def getCommunicator(self):
        trace()
        return self._communicator

    def type(self):
        trace()
        return self._type

    def protocol(self):
        trace()
        return self._protocol

    def create(self, strEndpoint, oaEndpoint):
        trace()
        return EndpointI(self._communicator, self._protocol, strEndpoint, oaEndpoint)

    def read(self, s):
        trace()
        raise NotImplementedError("EndpointFactoryI.read()")

    def destroy(self):
        trace()


class BasicStream(object):
    def __init__(self, data):
        trace()

        self._data = data


class EndpointI(object):
    def __init__(self, communicator, protocol, strEndpoint, oaEndpoint):
        trace()

        self._communicator = communicator
        self._protocol = protocol
        self._type = -1
        self._strEndpoint = strEndpoint
        self._oaEndpoint = oaEndpoint

    def __del__(self):
        trace()

    def __lt__(self, other):
        trace()

        return id(self) < id(other)

    def streamWrite(self, stream):
        trace()

        raise NotImplementedError("EndpointI.streamWrite()")

    def getCommunicator(self):
        trace()

        return self._communicator

    def toString(self):
        trace()

        return self._protocol + self._strEndpoint

    def getCompress(self):
        trace()

        return 0

    def setCompress(self, compress):
        trace()

        return self

    def type(self):
        trace()

        return self._type

    def datagram(self):
        trace()

        return True

    def secure(self):
        trace()

        return False

    def timeout(self):
        trace()

        return 60

    def transceiver(self):
        trace()

        raise NotImplementedError("EndpointI.transceiver(endp)")

        # endp = EndpointI(
        #     self._communicator, self._protocol, self._strEndpoint)
        # trans = TransceiverI(self._communicator, self._protocol)
        # return endp, trans

    def connectors_async(self, callback):
        trace()

        raise NotImplementedError("EndpointI.connectors_async()")

        # connectors = [ConnectorI(self._communicator, self._protocol)]
        # callback.connectors(connectors)

    def acceptor(self):
        trace()

        raise NotImplementedError("EndpointI.acceptor()")

    def expand(self):
        trace()

        return [self]


# Note: could not create an instance of Ice.ConnectionInfo here
class ConnectionInfo(object):
    def __init__(self, incoming, adapterName, connectionId):
        trace()

        self.incoming = incoming
        self.adapterName = adapterName
        self.connectionId = connectionId


class NativeInfo(object):
    def __init__(self, fd=-1):
        trace()

        self._fd = fd

    def fd(self):
        trace()

        return self._fd


class Acceptor(NativeInfo):
    def listen(self):
        trace()

        raise NotImplementedError("Acceptor.listen()")

    def accept(self):
        trace()

        raise NotImplementedError("Acceptor.accept()")

    def close(self):
        trace()

        raise NotImplementedError("Acceptor.close()")


class ConnectorI(object):
    def __init__(self, communicator, protocol):
        trace()

        self._communicator = communicator
        self._protocol = protocol
        self._type = -1

    def __lt__(self, other):
        trace()

        return id(self) < id(other)

    def getCommunicator(self):
        trace()

        return self._communicator

    def type(self):
        trace()

        return self._type

    def connect(self):
        trace()

        raise NotImplementedError("ConnectorI.connect()")

        # return TransceiverI(self._communicator, self.protocol, True)


class TransceiverI(NativeInfo):
    def __init__(self, communicator, protocol, connect=False, fd=-1):
        trace()

        NativeInfo.__init__(self, fd)

        self._communicator = communicator
        self._protocol = protocol
        self._connect = connect

    def __del__(self):
        trace()

    def getCommunicator(self):
        trace()

        return self._communicator

    def toString(self):
        trace()

        raise NotImplementedError("TransceiverI.toString()")

    def type(self):
        trace()

        return self._protocol

    def getInfo(self):
        trace()

        raise NotImplementedError("TransceiverI.getInfo()")

    def initialize(self, retvals):
        trace()

        return retvals['SocketOperationNone']

    def getMaxPaquetSize(self):
        trace()

        return 256

    def write(self, buff):
        trace()

        raise NotImplementedError("TransceiverI.write")

    def read(self, buff):
        trace()

        raise NotImplementedError("TransceiverI.read")

    def close(self):
        trace()

        raise NotImplementedError("TransceiverI.close")
