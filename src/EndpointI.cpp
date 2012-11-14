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
#include <Ice/Communicator.h>
#include <Ice/Properties.h>

#include "PyFunctions.h"
#include "EndpointI.h"
#include "Instance.h"


PyEndpoint::EndpointI::EndpointI(const InstancePtr& instance, PyObjectPtr pyEndpoint) :
    _instance(instance),
    _pyEndpoint(pyEndpoint) {

    std::cout << " - call to EndpointI() [1]" << std::endl;
}

void
PyEndpoint::EndpointI::streamWrite(IceInternal::BasicStream* s) const {

    std::cout << __FILE__ << ":" << __LINE__
	      << " NOT IMPLEMENTED!!" << std::endl;
    throw;
}

std::string
PyEndpoint::EndpointI::toString() const {

    PyObjectPtr result = PyFunc::callMethod(_pyEndpoint, "toString");
    return PyFunc::getAsString(result);
}

Ice::EndpointInfoPtr
PyEndpoint::EndpointI::getInfo() const {

    std::cout << __FILE__ << ":" << __LINE__
	      << ": Not implemented!" << std::endl;
    throw;
}

Ice::Short
PyEndpoint::EndpointI::type() const {

    std::cout << " - call to type() this: " << this << std::endl;

    PyObjectPtr result = PyFunc::callMethod(_pyEndpoint, "type");
    return PyFunc::getAsInteger(result);
}

Ice::Int
PyEndpoint::EndpointI::timeout() const {

    std::cout << " - call to timeout() this: " << this << std::endl;

    PyObjectPtr result = PyFunc::callMethod(_pyEndpoint, "timeout");
    return PyFunc::getAsInteger(result);
}

IceInternal::EndpointIPtr
PyEndpoint::EndpointI::timeout(Ice::Int timeout) const {

    std::cout << __FILE__ << ":" << __LINE__
	      << ": Not implemented!" << std::endl;
    throw;
}

IceInternal::EndpointIPtr
PyEndpoint::EndpointI::connectionId(const std::string& connectionId) const {

    std::cout << __FILE__ << ":" << __LINE__
	      << ": Not implemented!" << std::endl;
    throw;
}

bool
PyEndpoint::EndpointI::compress() const {

    std::cout << " - call to compress() this: " << this << std::endl;

    PyObjectPtr result = PyFunc::callMethod(_pyEndpoint, "timeout");
    return PyFunc::getAsBool(result);
}

IceInternal::EndpointIPtr
PyEndpoint::EndpointI::compress(bool compress) const {

    std::cout << __FILE__ << ":" << __LINE__
	      << ": Not implemented!" << std::endl;
    throw;
}

bool
PyEndpoint::EndpointI::datagram() const {

    std::cout << " - call to datagram() this: " << this << std::endl;

    PyObjectPtr result = PyFunc::callMethod(_pyEndpoint, "datagram");
    return PyFunc::getAsBool(result);
}

bool
PyEndpoint::EndpointI::secure() const {

    std::cout << " - call to secure() this: " << this << std::endl;

    PyObjectPtr result = PyFunc::callMethod(_pyEndpoint, "secure");
    return PyFunc::getAsBool(result);
}

IceInternal::TransceiverPtr
PyEndpoint::EndpointI::transceiver(IceInternal::EndpointIPtr& endp) const {

    std::cout << __FILE__ << ":" << __LINE__
	      << ": Not implemented!" << std::endl;
    throw;
}

std::vector<IceInternal::ConnectorPtr>
PyEndpoint::EndpointI::connectors() const {

    std::cout << __FILE__ << ":" << __LINE__
	      << ": Not implemented!" << std::endl;
    throw;
}

void
PyEndpoint::EndpointI::connectors_async(const IceInternal::EndpointI_connectorsPtr& callback) const {

    std::cout << " - call to connectors_async() this: " << this << std::endl;

    std::cout << __FILE__ << ":" << __LINE__
	      << ": Not implemented!" << std::endl;
    throw;
}

IceInternal::AcceptorPtr
PyEndpoint::EndpointI::acceptor(IceInternal::EndpointIPtr& endp, const std::string& adapterName) const {

    std::cout << __FILE__ << ":" << __LINE__
	      << ": Not implemented!" << std::endl;
    throw;
}

std::vector<IceInternal::EndpointIPtr>
PyEndpoint::EndpointI::expand() const {

    std::cout << __FILE__ << ":" << __LINE__
	      << ": Not implemented!" << std::endl;
    throw;
}

bool
PyEndpoint::EndpointI::equivalent(const IceInternal::EndpointIPtr& endpoint) const {

    std::cout << __FILE__ << ":" << __LINE__
	      << ": Not implemented!" << std::endl;
    throw;
}

bool
PyEndpoint::EndpointI::operator==(const Ice::LocalObject& r) const {

    std::cout << __FILE__ << ":" << __LINE__
	      << ": Not implemented!" << std::endl;
    throw;
}

bool
PyEndpoint::EndpointI::operator<(const Ice::LocalObject& r) const {

    std::cout << __FILE__ << ":" << __LINE__
	      << ": Not implemented!" << std::endl;
    throw;
}

Ice::Int
PyEndpoint::EndpointI::hashInit() const {

    std::cout << __FILE__ << ":" << __LINE__
	      << ": Not implemented!" << std::endl;
    throw;
}

PyEndpoint::EndpointFactoryI::EndpointFactoryI(const InstancePtr& instance) :
    _instance(instance) {

    Ice::PropertiesPtr props = instance->communicator()->getProperties();
    std::string moduleName = props->getProperty("PyEndpoint.Module");
    if (moduleName.empty()) {
    	std::cerr << "Property 'PyEndpoint.Module' not set!" << std::endl;
    	throw PyFunc::RuntimeError();
    }

    PyObjectPtr module = PyFunc::importModule(moduleName);
    PyObjectPtr factoryClass = PyFunc::getClass(module, "EndpointFactoryI");
    _pyFactory = PyFunc::newInstance(factoryClass);
}

PyEndpoint::EndpointFactoryI::~EndpointFactoryI() {

    std::cout << " - call to ~EndpointFactoryI()" << std::endl;
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
PyEndpoint::EndpointFactoryI::create(const std::string& str, bool oaEndpoint) const {

    std::cout << " - call to EndpointFactoryI::create()" << std::endl;

    PyObjectPtr args = Py_BuildValue("sb", str.c_str(), oaEndpoint);
    PyObjectPtr pyEndpoint = PyFunc::callMethod(_pyFactory, "create", args);

    return new EndpointI(_instance, pyEndpoint);
}

IceInternal::EndpointIPtr
PyEndpoint::EndpointFactoryI::read(IceInternal::BasicStream* s) const {
    std::cout << __FILE__ << ":" << __LINE__
	      << " NOT IMPLEMENTED!!" << std::endl;
    throw;
}

void
PyEndpoint::EndpointFactoryI::destroy() {

    PyFunc::callMethod(_pyFactory, "destroy");
    _instance = 0;
}
