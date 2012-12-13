/* -*- mode: c++; coding: utf-8 -*- */

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

#include <Python.h>  // avoid an annoying warning on GCC
#include <Ice/Communicator.h>

#include "PyFunctions.h"
#include "ConnectorI.h"
#include "Instance.h"
#include "TransceiverI.h"
#include "EndpointI.h"

#include "debug.h"


IceInternal::TransceiverPtr
PyEndpoint::ConnectorI::connect() {

    IDG std::cout << " - call to ConnectorI::connect()" << std::endl;

    PyObjectPtr result = PyFunc::callMethod(_pyConnector, "connect");
    return new PyEndpoint::TransceiverI(_instance, result);
}

Ice::Short
PyEndpoint::ConnectorI::type() const {

    PyObjectPtr result = PyFunc::callMethod(_pyConnector, "type");
    return PyFunc::getAsInteger(result);
}

std::string
PyEndpoint::ConnectorI::toString() const {

    std::cout << __FILE__ << ":" << __LINE__
	      << ": Not implemented!" << std::endl;
    throw;
}

bool
PyEndpoint::ConnectorI::operator==(const IceInternal::Connector& r) const {

    std::cout << __FILE__ << ":" << __LINE__
	      << ": Not implemented!" << std::endl;
    throw;
}

bool
PyEndpoint::ConnectorI::operator!=(const IceInternal::Connector& r) const {

    std::cout << __FILE__ << ":" << __LINE__
	      << ": Not implemented!" << std::endl;
    throw;
}

bool
PyEndpoint::ConnectorI::operator<(const IceInternal::Connector& other) const {

    IDG std::cout << " - call to ConnectorI::operator<(other)" << std::endl;

    const ConnectorI* p = dynamic_cast<const ConnectorI*>(&other);
    if (not p) {
        return type() < other.type();
    }

    PyObjectPtr pyOther = ((PyEndpoint::ConnectorI&)other)._pyConnector;
    PyObjectPtr args = Py_BuildValue("(O)", pyOther.get());
    PyObjectPtr result = PyFunc::callMethod(_pyConnector, "__lt__", args);
    return PyFunc::getAsBool(result);
}

PyEndpoint::ConnectorI::ConnectorI(PyEndpoint::InstancePtr& instance,
				   PyObjectPtr& pyConnector) :
    _instance(instance),
    _pyConnector(pyConnector) {

    IDG std::cout << " - call to ConnectorI::ConnectorI() " << std::endl;
}

PyEndpoint::ConnectorI::~ConnectorI() {

    IDG std::cout << " - call to ConnectorI::~ConnectorI() " << std::endl;
}

