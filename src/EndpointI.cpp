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

#include <Python.h>
#include "PyHandle.h"
#include "PyFunctions.h"
#include "Instance.h"
#include "EndpointI.h"


PyEndpoint::EndpointFactoryI::EndpointFactoryI(const InstancePtr& instance) {

    Ice::PropertiesPtr props = instance->communicator()->getProperties();
    std::string moduleName = props->getProperty("PyEndpoint.Module");
    if (moduleName.empty()) {
    	std::cerr << "Property 'PyEndpoint.Module' not set!" << std::endl;
    	throw PyFunc::RuntimeError();
    }

    PyObjectPtr module = PyFunc::importModule(moduleName);
    PyObjectPtr factoryClass = PyFunc::getClass(module, "EndpointFactory");
    _pyFactory = PyFunc::newInstance(factoryClass);
}

PyEndpoint::EndpointFactoryI::~EndpointFactoryI() {
}

Ice::Short
PyEndpoint::EndpointFactoryI::type() const {

    PyObjectPtr result = PyFunc::callMethod(_pyFactory, "type");
    return PyFunc::getAsInteger(result);
}

std::string
PyEndpoint::EndpointFactoryI::protocol() const {

    PyObjectPtr result = PyFunc::callMethod(_pyFactory, "protocol");
    return PyFunc::getAsString(result);
}

IceInternal::EndpointIPtr
PyEndpoint::EndpointFactoryI::create(const std::string& info, bool oaEndpoint) const {

    PyObjectPtr pyEndpoint = PyFunc::callMethod(_pyFactory, "create", args);
    //return new EndpointI(pyEndpoint, _instance, info, oaEndpoint);
}

IceInternal::EndpointIPtr
PyEndpoint::EndpointFactoryI::read(IceInternal::BasicStream*) const {
    std::cout << "EndpointFactoryI.read() NOT IMPLEMENTED!!" << std::endl;
    throw;
}

void
PyEndpoint::EndpointFactoryI::destroy() {
}

