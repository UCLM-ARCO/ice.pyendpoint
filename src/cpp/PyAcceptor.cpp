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

#include "PyAcceptor.h"
#include "PyEndpointI.h"
#include "PyFunctions.h"

IceInternal::NativeInfoPtr
PyEndpoint::PyAcceptor::getNativeInfo() {
    trace();

    return this;
}

void
PyEndpoint::PyAcceptor::close() {
    trace();

    PyFunc::callMethod(_pyAcceptor, "close");
}

IceInternal::EndpointIPtr
PyEndpoint::PyAcceptor::listen() {
    trace();

    PyFunc::callMethod(_pyAcceptor, "listen");
    _fd = PyFunc::getAsInteger(PyFunc::callMethod(_pyAcceptor, "fd"));

    _endpoint = _endpoint->endpoint(this);
    return _endpoint;
}

IceInternal::TransceiverPtr
PyEndpoint::PyAcceptor::accept() {
    trace();
    fixme("Not implemented!");
}

std::string
PyEndpoint::PyAcceptor::protocol() const {
    trace();
    fixme("Not implemented!");
}

std::string
PyEndpoint::PyAcceptor::toString() const {
    trace();
    fixme("Not implemented!");
}

std::string
PyEndpoint::PyAcceptor::toDetailedString() const {
    trace();
    fixme("Not implemented!");
}

PyEndpoint::PyAcceptor::PyAcceptor(const PyEndpointIPtr& endpoint,
				   const IceInternal::ProtocolInstancePtr& instance,
				   PyObjectPtr& pyAcceptor) :
    _endpoint(endpoint),
    _instance(instance),
    _pyAcceptor(pyAcceptor) {

    trace();
}

PyEndpoint::PyAcceptor::~PyAcceptor() {
    trace();
}
