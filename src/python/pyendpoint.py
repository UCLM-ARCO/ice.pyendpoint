# -*- mode: python; coding: utf-8 -*-

# Note: do not remove imoprt Ice: if the endpoint is loaded on C++,
# both 'engines' (c++ and python) should be connected.
import Ice

import sys
import uuid
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

    def type(self):
        trace()
        return self._type

    def protocol(self):
        trace()
        return self._protocol

    def create(self):
        """Return a new instance of your Endpoint."""

        raise NotImplementedError("EndpointFactoryI.create()")

    def read(self, s):
        """Read endpoint info from stream and create a new one."""

        raise NotImplementedError("EndpointFactoryI.read()")

    def destroy(self):
        trace()


class EndpointI(object):
    def __init__(self, communicator, protocol):
        trace()

        self._communicator = communicator
        self._protocol = protocol
        self._connectionId = uuid.uuid4().get_hex()

    def __del__(self):
        trace()

    def __lt__(self, other):
        trace()
        return id(self) < id(other)

    def initWithOptions(self, args, oaEndpoint):
        """Here you must parse endpoint options."""

        raise NotImplementedError("EndpointI.initWithOptions()")

    def options(self):
        """Return a string with the options part of a stringfied proxy that
        uses this endpoint. """

        raise NotImplementedError("EndpointI.options()")

    def streamWrite(self, stream):
        """Marshall your endpoint to be sent over the wire."""

        raise NotImplementedError("EndpointI.streamWrite()")

    def toString(self):
        """Return a string representation of your endpoint."""

        raise NotImplementedError("EndpointI.streamWrite()")

    def datagram(self):
        """Return True if this endpoint is datagram oriented (not connection oriented)."""

        raise NotImplementedError("EndpointI.datagram()")

    def protocol(self):
        trace()
        return self._protocol

    def connectionId(self):
        trace()
        return self._connectionId

    def secure(self):
        trace()
        return False

    def timeout(self):
        trace()
        return 60

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

        if self._fd < 0 and log.activated:
            print "WARNING: file descriptor is {}, this could be a problem".format(self._fd)

        return self._fd


class Acceptor(NativeInfo):
    def listen(self):
        """Start listening for new clients."""

        raise NotImplementedError("Acceptor.listen()")

    def accept(self):
        """Accept a new incomming connection."""

        raise NotImplementedError("Acceptor.accept()")

    def close(self):
        """Stop and close your incoming devices"""

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

    def type(self):
        trace()
        return self._type

    def connect(self):
        """Perform an active conncetion."""

        raise NotImplementedError("ConnectorI.connect()")


class TransceiverI(NativeInfo):
    def __init__(self, communicator, protocol, connect=False, fd=-1):
        trace()

        NativeInfo.__init__(self, fd)

        self._communicator = communicator
        self._protocol = protocol
        self._connect = connect

    def __del__(self):
        trace()

    def toString(self):
        """Return a string representation of this transceiver."""

        raise NotImplementedError("TransceiverI.toString()")

    def protocol(self):
        trace()
        return self._protocol

    def getInfo(self):
        """Return here the ConnectionInfo: incoming:b, adapterName:s, connectionId:s."""

        raise NotImplementedError("TransceiverI.getInfo()")

    def initialize(self):
        trace()
        return 0

    def bind(self):
        """When communications are not connection oriented, make here the
        initial binding, and return an Enpoint."""

        raise NotImplementedError("TransceiverI.bind()")

    def closing(self, initiator):
        """If not connection oriented, return False. Otherwise, return 'initiator'"""

        raise NotImplementedError("TransceiverI.closing()")

    def write(self, buff):
        """Write buff data to medium. Return True if all was fine, False if
        need to retry."""

        raise NotImplementedError("TransceiverI.write")

    def read(self, buff):
        """Read data from medium and store it on buff. Return (state,
        size). 'state' as True if all was fine, or False if need to
        retry. """

        raise NotImplementedError("TransceiverI.read")

    def close(self):
        """Close your medium."""

        raise NotImplementedError("TransceiverI.close")
