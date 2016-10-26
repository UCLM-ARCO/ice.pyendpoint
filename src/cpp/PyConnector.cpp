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

#include "PyConnector.h"
#include "PyTransceiver.h"
#include "PyFunctions.h"


IceInternal::TransceiverPtr
PyEndpoint::PyConnector::connect() {
    trace();

    PyObjectPtr result = PyFunc::callMethod(_pyConnector, "connect");
    return new PyEndpoint::PyTransceiver(_instance, result);
}

Ice::Short
PyEndpoint::PyConnector::type() const {
    trace();

    PyObjectPtr result = PyFunc::callMethod(_pyConnector, "type");
    return PyFunc::getAsInteger(result);
}

std::string
PyEndpoint::PyConnector::toString() const {
    trace();

    PyObjectPtr result = PyFunc::callMethod(_pyConnector, "toString");
    return PyFunc::getAsString(result);
}

bool
PyEndpoint::PyConnector::operator==(const IceInternal::Connector&) const {
    trace();
    fixme("Not implemented!");
}

bool
PyEndpoint::PyConnector::operator!=(const IceInternal::Connector&) const {
    trace();
    fixme("Not implemented!");
}

bool
PyEndpoint::PyConnector::operator<(const IceInternal::Connector& other) const {
    trace();

    const PyEndpoint::PyConnector* p = dynamic_cast<const PyEndpoint::PyConnector*>(&other);
    if (not p) {
        return type() < other.type();
    }

    PyGILEnsurer e;
    PyObjectPtr pyOther = ((PyEndpoint::PyConnector&)other)._pyConnector;
    PyObjectPtr args = Py_BuildValue("(O)", pyOther.get());
    PyObjectPtr result = PyFunc::callMethod(_pyConnector, "__lt__", args);
    return PyFunc::getAsBool(result);
}

PyEndpoint::PyConnector::PyConnector(const IceInternal::ProtocolInstancePtr& instance,
				     PyObjectPtr& pyConnector) :
    _instance(instance),
    _pyConnector(pyConnector) {

    trace();
}
