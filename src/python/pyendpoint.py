# -*- mode: python; coding: utf-8 -*-

# Note: do not remove imoprt Ice: if the endpoint is loaded on C++,
# both 'engines' (c++ and python) should be connected.

import Ice
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
    def __init__(self, communicator):
        log << "EndpointFactoryI.__init__()"
        self._communicator = communicator
        self._type = -1
        self._protocol = ""

    def __del__(self):
        log << "EndpointFactoryI.__del__()"

    def getCommunicator(self):
        log << "EndpointFactoryI.getCommunicator()"
        return self._communicator

    def type(self):
        log << "EndpointFactoryI.type()"
        return self._type

    def protocol(self):
        log << "EndpointFactoryI.protocol()"
        return self._protocol

    def create(self, strEndpoint, oaEndpoint):
        log << "EndpointFactoryI.create('{}', '{}')".format(
            strEndpoint, oaEndpoint)

        return EndpointI(self._communicator, self._protocol, strEndpoint, oaEndpoint)

    def read(self, s):
        log << "EndpointFactoryI.read()"
        raise NotImplementedError("EndpointFactoryI.read()")

    def destroy(self):
        log << "EndpointFactoryI.destroy()"


class BasicStream(object):
    def __init__(self, data):
        self._data = data


class EndpointI(object):
    def __init__(self, communicator, protocol, strEndpoint, oaEndpoint):
        log << "EndpointI.__init__()"
        self._communicator = communicator
        self._protocol = protocol
        self._type = -1
        self._strEndpoint = strEndpoint
        self._oaEndpoint = oaEndpoint

    def __del__(self):
        log << "EndpointI.__del__()"

    def __lt__(self, other):
        log << "EndpointI.__lt__(other)", id(self), id(other)
        return id(self) < id(other)

    def streamWrite(self, stream):
        log << "EndpointI.streamWrite()"
        raise NotImplementedError("EndpointI.streamWrite()")

    def getCommunicator(self):
        log << "EndpointI.getCommunicator()"
        return self._communicator

    def toString(self):
        log << "EndpointI.toString()"
        return self._protocol + self._strEndpoint

    def getCompress(self):
        log << "EndpointI.getCompress()"
        return 0

    def setCompress(self, compress):
        log << "EndpointI.setCompress()"
        return self

    def type(self):
        log << "EndpointI.type()"
        return self._type

    def datagram(self):
        log << "EndpointI.datagram()"
        return True

    def secure(self):
        log << "EndpointI.secure()"
        return False

    def timeout(self):
        log << "EndpointI.timeout()"
        return 60

    def transceiver(self):
        log << "EndpointI.transceiver(endp)"
        raise NotImplementedError("EndpointI.transceiver(endp)")

        # endp = EndpointI(
        #     self._communicator, self._protocol, self._strEndpoint)
        # trans = TransceiverI(self._communicator, self._protocol)
        # return endp, trans

    def connectors_async(self, callback):
        log << "EndpointI.connectors_async()"
        raise NotImplementedError("EndpointI.connectors_async()")

        # connectors = [ConnectorI(self._communicator, self._protocol)]
        # callback.connectors(connectors)

    def acceptor(self):
        log << "EndpointI.acceptor()"
        raise NotImplementedError("EndpointI.acceptor()")

    def expand(self):
        log << "EndpointI.expand()"
        return [self]


# Note: could not create an instance of Ice.ConnectionInfo here
class ConnectionInfo(object):
    def __init__(self, incoming, adapterName, connectionId):
        self.incoming = incoming
        self.adapterName = adapterName
        self.connectionId = connectionId


class NativeInfo(object):
    def __init__(self, fd=-1):
        self._fd = fd

    def fd(self):
        return self._fd


class Acceptor(NativeInfo):
    def listen(self):
        log << "Acceptor.listen()"
        raise NotImplementedError("Acceptor.listen()")

    def accept(self):
        log << "Acceptor.accept()"
        raise NotImplementedError("Acceptor.accept()")

    def close(self):
        log << "Acceptor.close()"
        raise NotImplementedError("Acceptor.close()")


class ConnectorI(object):
    def __init__(self, communicator, protocol):
        log << "ConnectorI.__init__()"
        self._communicator = communicator
        self._protocol = protocol
        self._type = -1

    def __lt__(self, other):
        log << "ConnectorI.__lt__(other)", id(self), id(other)
        return id(self) < id(other)

    def getCommunicator(self):
        log << "ConnectorI.getCommunicator()"
        return self._communicator

    def type(self):
        log << "ConnectorI.type()"
        return self._type

    def connect(self):
        log << "ConnectorI.connect()"
        raise NotImplementedError("ConnectorI.connect()")

        # return TransceiverI(self._communicator, self.protocol, True)


class TransceiverI(NativeInfo):
    def __init__(self, communicator, protocol, connect=False, fd=-1):
        NativeInfo.__init__(self, fd)

        log << "TransceiverI.__init__()"
        self._communicator = communicator
        self._protocol = protocol
        self._connect = connect

    def __del__(self):
        log << "TransceiverI.__del__()"

    def getCommunicator(self):
        return self._communicator

    def toString(self):
        log << "TransceiverI.toString()"
        raise NotImplementedError("TransceiverI.toString()")

    def type(self):
        log << "TransceiverI.type()"
        return self._protocol

    def getInfo(self):
        log << "TransceiverI.getInfo()"
        raise NotImplementedError("TransceiverI.getInfo()")

    def initialize(self, retvals):
        log << "TransceiverI.initialize()"
        return retvals['SocketOperationNone']

    def getMaxPaquetSize(self):
        log << "TransceiverI.getMaxPaquetSize()"
        return 256

    def write(self, buff):
        log << "TransceiverI.write(buff)"
        raise NotImplementedError("TransceiverI.write")

    def read(self, buff):
        log << "TransceiverI.read(buff)"
        raise NotImplementedError("TransceiverI.read")

    def close(self):
        log << "TransceiverI.close()"
        raise NotImplementedError("TransceiverI.close")
