/* -*- mode: c++; coding: utf-8; truncate-lines: true -*- */

//
// Copyright (c) 2012-2016 Oscar Aceña. All rights reserved.
//
// This file is part of PyEndpoint
//
// PyEndpoint is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// PyEndpoint is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with PyEndpoint.  If not, see <http://www.gnu.org/licenses/>.
//

#include <Ice/Connection.h>

#include "PyEndpointI.h"
#include "PyTransceiver.h"
#include "PyFunctions.h"


IceInternal::NativeInfoPtr
PyEndpoint::PyTransceiver::getNativeInfo() {
    trace();

    return this;
}

IceInternal::SocketOperation
PyEndpoint::PyTransceiver::initialize(IceInternal::Buffer&, IceInternal::Buffer&, bool&) {
    trace();

    PyObjectPtr result = PyFunc::callMethod(_pyTransceiver, "initialize");
    int sop = PyFunc::getAsInteger(result);

    return sop == 0 ? IceInternal::SocketOperationNone : IceInternal::SocketOperationConnect;
}

IceInternal::SocketOperation
PyEndpoint::PyTransceiver::closing(bool initiator, const Ice::LocalException&) {
    trace();
    PyGILEnsurer e;

    PyObjectPtr args = Py_BuildValue("(b)", initiator);
    PyObjectPtr result = PyFunc::callMethod(_pyTransceiver, "closing", args);
    bool sop = PyFunc::getAsBool(result);

    return sop ? IceInternal::SocketOperationRead : IceInternal::SocketOperationNone;
}

void
PyEndpoint::PyTransceiver::close() {
    trace();

    PyFunc::callMethod(_pyTransceiver, "close");
}

IceInternal::EndpointIPtr
PyEndpoint::PyTransceiver::bind() {
    trace();

    PyFunc::callMethod(_pyTransceiver, "bind");

    _endpoint = _endpoint->endpoint(this);
    return _endpoint;
}

IceInternal::SocketOperation
PyEndpoint::PyTransceiver::write(IceInternal::Buffer& buf) {
    trace();
    PyGILEnsurer e;

    PyObjectPtr pyBuf = PyMemoryView_FromMemory((char*)buf.i, buf.b.size(), PyBUF_READ);
    PyObjectPtr args = Py_BuildValue("(O)", pyBuf.get());
    PyObjectPtr result = PyFunc::callMethod(_pyTransceiver, "write", args);
    bool ok = PyFunc::getAsBool(result);

    return ok ? IceInternal::SocketOperationNone : IceInternal::SocketOperationWrite;
}

IceInternal::SocketOperation
PyEndpoint::PyTransceiver::read(IceInternal::Buffer& buf, bool&) {
    trace();
    PyGILEnsurer e;

    PyObjectPtr maxSizeResult = PyFunc::callMethod(_pyTransceiver, "getMaxPaquetSize");
    const int maxPacketSize = PyFunc::getAsInteger(maxSizeResult);
    // const int maxPacketSize = 256;

    assert(buf.i == buf.b.begin());
    buf.b.resize(maxPacketSize);
    buf.i = buf.b.begin();

    PyObjectPtr pyBuf = PyMemoryView_FromMemory((char*)buf.i, buf.b.size(), PyBUF_WRITE);
    PyObjectPtr args = Py_BuildValue("(O)", pyBuf.get());
    PyObjectPtr result = PyFunc::callMethod(_pyTransceiver, "read", args);

    if (not PyTuple_Check(result)) {
    	std::cerr << "ValueError, need status and read size!" << std::endl;
    	throw PyFunc::RuntimeError();
    }

    bool ok = PyFunc::getAsBool(PyObjectPtr::fromBorrowed(PyTuple_GetItem(result, 0)));
    if (not ok) {
    	return IceInternal::SocketOperationRead;
    }

    int size = PyFunc::getAsInteger(PyObjectPtr::fromBorrowed(PyTuple_GetItem(result, 1)));
    buf.b.resize(size);
    buf.i = buf.b.end();

    return IceInternal::SocketOperationNone;
}

std::string
PyEndpoint::PyTransceiver::protocol() const {
    trace();

    PyObjectPtr result = PyFunc::callMethod(_pyTransceiver, "protocol");
    return PyFunc::getAsString(result);
}

std::string
PyEndpoint::PyTransceiver::toString() const {
    trace();

    PyObjectPtr result = PyFunc::callMethod(_pyTransceiver, "toString");
    return PyFunc::getAsString(result);
}

// Used on some Ice.Trace levels
std::string
PyEndpoint::PyTransceiver::toDetailedString() const {
    trace();

    PyObjectPtr result = PyFunc::callMethod(_pyTransceiver, "toDetailedString");
    return PyFunc::getAsString(result);
}

Ice::ConnectionInfoPtr
PyEndpoint::PyTransceiver::getInfo() const {
    trace();

    Ice::ConnectionInfoPtr info = new Ice::ConnectionInfo();
    PyObjectPtr pyInfo = PyFunc::callMethod(_pyTransceiver, "getInfo");

    info->incoming = PyFunc::getAsBool(PyFunc::getAttr(pyInfo, "incoming"));
    info->adapterName = PyFunc::getAsString(PyFunc::getAttr(pyInfo, "adapterName"));
    info->connectionId = PyFunc::getAsString(PyFunc::getAttr(pyInfo, "connectionId"));
    return info;
}

void
PyEndpoint::PyTransceiver::checkSendSize(const IceInternal::Buffer& buf) {
    trace();

    PyObjectPtr maxSizeResult = PyFunc::callMethod(_pyTransceiver, "getMaxPaquetSize");
    const int maxPacketSize = PyFunc::getAsInteger(maxSizeResult);
    // const int maxPacketSize = 256;

    // FIXME: should this get checked on Python?
    if (buf.b.size() > maxPacketSize) {
        IceInternal::Ex::throwMemoryLimitException
	    (__FILE__, __LINE__, buf.b.size(), maxPacketSize);
    }
}

void
PyEndpoint::PyTransceiver::setBufferSize(int rcvSize, int sndSize) {
    trace();
    fixme("Not implemented!");
}

PyEndpoint::PyTransceiver::PyTransceiver(const IceInternal::ProtocolInstancePtr& instance,
					 PyObjectPtr pyTransceiver) :
    _instance(instance),
    _pyTransceiver(pyTransceiver) {

    trace();

    PyObjectPtr result = PyFunc::callMethod(_pyTransceiver, "fd");
    _fd = PyFunc::getAsInteger(result);
}

PyEndpoint::PyTransceiver::PyTransceiver(const PyEndpointIPtr& endpoint,
					 const IceInternal::ProtocolInstancePtr& instance,
					 PyObjectPtr pyTransceiver) :
    _endpoint(endpoint),
    _instance(instance),
    _pyTransceiver(pyTransceiver) {

    trace();

    PyObjectPtr result = PyFunc::callMethod(_pyTransceiver, "fd");
    _fd = PyFunc::getAsInteger(result);
}
