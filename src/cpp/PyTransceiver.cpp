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

#include "PyTransceiver.h"

IceInternal::NativeInfoPtr
PyEndpoint::PyTransceiver::getNativeInfo() {
    trace();
    fixme("Not implemented!");
}

IceInternal::SocketOperation
PyEndpoint::PyTransceiver::initialize(IceInternal::Buffer&, IceInternal::Buffer&, bool&) {
    trace();
    fixme("Not implemented!");
}

IceInternal::SocketOperation
PyEndpoint::PyTransceiver::closing(bool, const Ice::LocalException&) {
    trace();
    fixme("Not implemented!");
}

void
PyEndpoint::PyTransceiver::close() {
    trace();
    fixme("Not implemented!");
}

IceInternal::SocketOperation
PyEndpoint::PyTransceiver::write(IceInternal::Buffer&) {
    trace();
    fixme("Not implemented!");
}

IceInternal::SocketOperation
PyEndpoint::PyTransceiver::read(IceInternal::Buffer&, bool&) {
    trace();
    fixme("Not implemented!");
}

std::string
PyEndpoint::PyTransceiver::protocol() const {
    trace();
    fixme("Not implemented!");
}

std::string
PyEndpoint::PyTransceiver::toString() const {
    trace();
    fixme("Not implemented!");
}

std::string
PyEndpoint::PyTransceiver::toDetailedString() const {
    trace();
    fixme("Not implemented!");
}

Ice::ConnectionInfoPtr
PyEndpoint::PyTransceiver::getInfo() const {
    trace();
    fixme("Not implemented!");
}

void
PyEndpoint::PyTransceiver::checkSendSize(const IceInternal::Buffer&) {
    trace();
    fixme("Not implemented!");
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
}
