/* -*- mode: c++; coding: utf-8; truncate-lines: true -*- */

//
// Copyright (c) 2014 Oscar Aceña. All rights reserved.
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

#include "PyFunctions.h"
#include "AcceptorI.h"
#include "TransceiverI.h"

#include "debug.h"


IceInternal::NativeInfoPtr
PyEndpoint::AcceptorI::getNativeInfo() {
    return this;
}

void
PyEndpoint::AcceptorI::close() {
    PyFunc::callMethod(_pyAcceptor, "close");
}

void
PyEndpoint::AcceptorI::listen() {
    PyFunc::callMethod(_pyAcceptor, "listen");
    _fd = PyFunc::getAsInteger(PyFunc::callMethod(_pyAcceptor, "fd"));
}

IceInternal::TransceiverPtr
PyEndpoint::AcceptorI::accept() {

    PyObjectPtr pyTransceiver = PyFunc::callMethod(_pyAcceptor, "accept");
    TransceiverI* trans = new PyEndpoint::TransceiverI(_instance, pyTransceiver);
    return trans;
}

std::string
PyEndpoint::AcceptorI::toString() const {
    fixme("Not implemented");
}

PyEndpoint::AcceptorI::AcceptorI(const InstancePtr& instance, PyObjectPtr pyAcceptor) :
    _instance(instance),
    _pyAcceptor(pyAcceptor) {
}

