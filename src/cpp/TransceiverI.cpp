// -*- mode: c++; coding: utf-8 -*-

//
// Copyright (c) 2012 Oscar Aceña. All rights reserved.
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

#include <Python.h>  // include first this to avoid GCC annoying warnings

#include "PyFunctions.h"
#include "TransceiverI.h"
#include "Ice/Network.h"

#include "debug.h"


IceInternal::NativeInfoPtr
PyEndpoint::TransceiverI::getNativeInfo() {

    IDG std::cout << " - call to TransceiverI::getNativeInfo()" << std::endl;

    return this;
}

IceInternal::SocketOperation
PyEndpoint::TransceiverI::initialize() {

    IDG std::cout << " - call to TransceiverI::initialize()" << std::endl;

    PyObjectPtr retvals = PyDict_New();

    PyObjectPtr soNone = PyInt_FromLong(IceInternal::SocketOperationNone);
    PyObjectPtr soRead = PyInt_FromLong(IceInternal::SocketOperationRead);
    PyObjectPtr soWrite = PyInt_FromLong(IceInternal::SocketOperationWrite);
    PyObjectPtr soConnect = PyInt_FromLong(IceInternal::SocketOperationConnect);

    PyDict_SetItemString(retvals, "SocketOperationNone", soNone);
    PyDict_SetItemString(retvals, "SocketOperationRead", soRead);
    PyDict_SetItemString(retvals, "SocketOperationWrite", soWrite);
    PyDict_SetItemString(retvals, "SocketOperationConnect", soConnect);

    PyObjectPtr args = Py_BuildValue("(O)", retvals.get());
    PyObjectPtr result = PyFunc::callMethod(_pyTransceiver, "initialize", args);
    return (IceInternal::SocketOperation) PyFunc::getAsInteger(result);
}

void
PyEndpoint::TransceiverI::close() {

    IDG std::cout << " - call to TransceiverI::close()" << std::endl;

    PyFunc::callMethod(_pyTransceiver, "close");
}

bool
PyEndpoint::TransceiverI::write(IceInternal::Buffer& buf) {

    IDG std::cout << " - call to TransceiverI::write()" << std::endl;

    PyObjectPtr pyBuf = PyBuffer_FromMemory(buf.i, buf.b.size());
    PyObjectPtr args = Py_BuildValue("(O)", pyBuf.get());
    PyObjectPtr result = PyFunc::callMethod(_pyTransceiver, "write", args);
    return PyFunc::getAsBool(result);
}

bool
PyEndpoint::TransceiverI::read(IceInternal::Buffer& buf) {

    IDG std::cout << " - call to TransceiverI::read()" << std::endl;

    PyObjectPtr maxSizeResult = PyFunc::callMethod(_pyTransceiver, "getMaxPaquetSize");
    const int maxPacketSize = PyFunc::getAsInteger(maxSizeResult);

    assert(buf.i == buf.b.begin());
    buf.b.resize(maxPacketSize);
    buf.i = buf.b.begin();

    PyObjectPtr pyBuf = PyBuffer_FromReadWriteMemory(buf.i, buf.b.size());
    PyObjectPtr args = Py_BuildValue("(O)", pyBuf.get());
    PyObjectPtr result = PyFunc::callMethod(_pyTransceiver, "read", args);

    if (not PyTuple_Check(result)) {
    	std::cerr << "ValueError, need status and read size!" << std::endl;
	throw PyFunc::RuntimeError();
    }

    bool retval = PyFunc::getAsBool(PyObjectPtr::fromBorrowed(PyTuple_GetItem(result, 0)));
    if (not retval) {
	return retval;
    }

    int size = PyFunc::getAsInteger(PyObjectPtr::fromBorrowed(PyTuple_GetItem(result, 1)));
    buf.b.resize(size);
    buf.i = buf.b.end();

    return retval;
}

std::string
PyEndpoint::TransceiverI::type() const {

    IDG std::cout << " - call to TransceiverI::type()" << std::endl;

    PyObjectPtr result = PyFunc::callMethod(_pyTransceiver, "type");
    return PyFunc::getAsString(result);
}

std::string
PyEndpoint::TransceiverI::toString() const {

    IDG std::cout << " - call to TransceiverI::toString()"
		  << " (this: " << this << ")" << std::endl;

    PyObjectPtr result = PyFunc::callMethod(_pyTransceiver, "toString");
    return PyFunc::getAsString(result);
}

Ice::ConnectionInfoPtr
PyEndpoint::TransceiverI::getInfo() const {

    IDG std::cout << " - call to TransceiverI::getInfo()" << std::endl;

    std::cout << __FILE__ << ":" << __LINE__
	      << ": Not implemented!" << std::endl;
    throw;
}

void
PyEndpoint::TransceiverI::checkSendSize(const IceInternal::Buffer& buf,
					size_t messageSizeMax) {

    IDG std::cout << " - call to TransceiverI::checkSendSize()" << std::endl;

    // FIXME: should this get checked on Python?
    if(buf.b.size() > messageSizeMax) {
        IceInternal::Ex::throwMemoryLimitException(__FILE__, __LINE__,
						   buf.b.size(), messageSizeMax);
    }
}

PyEndpoint::TransceiverI::TransceiverI(const InstancePtr& instance,
				       PyObjectPtr pyTransceiver) :
    _instance(instance),
    _pyTransceiver(pyTransceiver) {

    IDG std::cout << " - call to TransceiverI::TransceiverI()"
		  << " (this: " << this << ")" << std::endl;

    PyObjectPtr result = PyFunc::callMethod(_pyTransceiver, "fd");
    _fd = PyFunc::getAsInteger(result);
}

PyEndpoint::TransceiverI::~TransceiverI() {

    IDG std::cout << " - call to TransceiverI::~TransceiverI()"
		  << " (this: " << this << ")" << std::endl;
}
