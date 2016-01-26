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

#     def getCommunicator(self):
#         trace()
#         return self._communicator

    def type(self):
        trace()
        return self._type

    def protocol(self):
        trace()
        return self._protocol

    def create(self):
        trace()
        return EndpointI(self._communicator, self._protocol)

#     def read(self, s):
#         trace()
#         raise NotImplementedError("EndpointFactoryI.read()")

    def destroy(self):
        trace()


# class BasicStream(object):
#     def __init__(self, data):
#         trace()

#         self._data = data


class EndpointI(object):
    def __init__(self, communicator, protocol):
        trace()

        self._communicator = communicator
        self._protocol = protocol

#         self._type = -1
#         self._strEndpoint = strEndpoint
#         self._oaEndpoint = oaEndpoint

#     def __del__(self):
#         trace()

#     def __lt__(self, other):
#         trace()

#         return id(self) < id(other)

    def initWithOptions(self, args, oaEndpoint):
        """Here you must parse endpoint options."""

        raise NotImplementedError("EndpointI.initWithOptions()")

    def options(self):
        """Return a string with the options part of a stringfied proxy that
        uses this endpoint. """

        raise NotImplementedError("EndpointI.options()")

#     def streamWrite(self, stream):
#         trace()

#         raise NotImplementedError("EndpointI.streamWrite()")

#     def getCommunicator(self):
#         trace()

#         return self._communicator

#     def toString(self):
#         trace()

#         return self._protocol + self._strEndpoint

#     def getCompress(self):
#         trace()

#         return 0

#     def setCompress(self, compress):
#         trace()

#         return self

#     def type(self):
#         trace()

#         return self._type

    def datagram(self):
        """Return True if this endpoint is datagram oriented (not connection oriented)."""

        raise NotImplementedError("EndpointI.datagram()")

    def protocol(self):
        trace()
        return self._protocol

    def secure(self):
        """Return True if this endpoint is secure."""

        return False

#     def timeout(self):
#         trace()

#         return 60

    def transceiver(self):
        """Return an instance of your Transceiver, if this endpoint is not
        connection oriented. Otherwise, return None."""

        raise NotImplementedError("EndpointI.transceiver()")

    def acceptor(self):
        """Return an instance of your Acceptor, if this endpoint is
        connection oriented. Otherwise, return None."""

        raise NotImplementedError("EndpointI.acceptor()")

    def endpoint(self, aceptor):
        """Return a new endpoint, using the acceptor's information."""

        raise NotImplementedError("EndpointI.endpoint()")

    def connectors_async(self, callback):
        """Return a list of connectors for this endpoint"""

        raise NotImplementedError("EndpointI.connectors_async()")


# # Note: could not create an instance of Ice.ConnectionInfo here
# class ConnectionInfo(object):
#     def __init__(self, incoming, adapterName, connectionId):
#         trace()

#         self.incoming = incoming
#         self.adapterName = adapterName
#         self.connectionId = connectionId


class NativeInfo(object):
    def __init__(self, fd=-1):
        trace()

        self._fd = fd

    def fd(self):
        trace()

        return self._fd


class Acceptor(NativeInfo):
    def listen(self):
        """Start listening for new clients."""

        raise NotImplementedError("Acceptor.listen()")

#     def accept(self):
#         trace()

#         raise NotImplementedError("Acceptor.accept()")

    def close(self):
        """Stop and close your incoming devices"""

        raise NotImplementedError("Acceptor.close()")


class ConnectorI(object):
    def __init__(self, communicator, protocol):
        trace()

        self._communicator = communicator
        self._protocol = protocol
        self._type = -1

#     def __lt__(self, other):
#         trace()

#         return id(self) < id(other)

#     def getCommunicator(self):
#         trace()

#         return self._communicator

#     def type(self):
#         trace()

#         return self._type

#     def connect(self):
#         trace()

#         raise NotImplementedError("ConnectorI.connect()")

#         # return TransceiverI(self._communicator, self.protocol, True)


# class TransceiverI(NativeInfo):
#     def __init__(self, communicator, protocol, connect=False, fd=-1):
#         trace()

#         NativeInfo.__init__(self, fd)

#         self._communicator = communicator
#         self._protocol = protocol
#         self._connect = connect

#     def __del__(self):
#         trace()

#     def getCommunicator(self):
#         trace()

#         return self._communicator

#     def toString(self):
#         trace()

#         raise NotImplementedError("TransceiverI.toString()")

#     def type(self):
#         trace()

#         return self._protocol

#     def getInfo(self):
#         trace()

#         raise NotImplementedError("TransceiverI.getInfo()")

#     def initialize(self, retvals):
#         trace()

#         return retvals['SocketOperationNone']

#     def getMaxPaquetSize(self):
#         trace()

#         return 256

#     def write(self, buff):
#         trace()

#         raise NotImplementedError("TransceiverI.write")

#     def read(self, buff):
#         trace()

#         raise NotImplementedError("TransceiverI.read")

#     def close(self):
#         trace()

#         raise NotImplementedError("TransceiverI.close")
