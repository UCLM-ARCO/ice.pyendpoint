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
#include "PyUtils.h"

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
PyEndpoint::EndpointFactoryI::create(const std::string& info, bool oaEndpoint) const {
    std::cout << " - call to EndpointFactoryI.create()" << std::endl;

    PyObjectPtr args = Py_BuildValue("sb", info.c_str(), oaEndpoint);
    PyObjectPtr pyEndpoint = PyFunc::callMethod(_pyFactory, "create", args);

    std::cout << "pyEndpoint @ " << pyEndpoint.get() << std::endl;
    std::cout << " - now copy..." << std::endl;

    return new EndpointI(pyEndpoint);
}

IceInternal::EndpointIPtr
PyEndpoint::EndpointFactoryI::read(IceInternal::BasicStream*) const {
    std::cout << __FILE__ << ":" << __LINE__
	      << " NOT IMPLEMENTED!!" << std::endl;
    throw;
}

void
PyEndpoint::EndpointFactoryI::destroy() {

    PyFunc::callMethod(_pyFactory, "destroy");
}

PyEndpoint::EndpointI::EndpointI(PyObjectPtr pyEndpoint) :
    _pyEndpoint(pyEndpoint) {

    std::cout << " - ok" << std::endl;
    std::cout << " - this: " << this << std::endl;
}

PyEndpoint::EndpointI::~EndpointI() {
    std::cout << "call to ~EndpointI()" << std::endl;
}

void
PyEndpoint::EndpointI::streamWrite(IceInternal::BasicStream*) const {
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
	      << " NOT IMPLEMENTED!!" << std::endl;
    throw;
}

Ice::Short
PyEndpoint::EndpointI::type() const {
    std::cout << __FILE__ << ":" << __LINE__
	      << " NOT IMPLEMENTED!!" << std::endl;
    throw;
}

Ice::Int
PyEndpoint::EndpointI::timeout() const {
    std::cout << __FILE__ << ":" << __LINE__
	      << " NOT IMPLEMENTED!!" << std::endl;
    throw;
}

IceInternal::EndpointIPtr
PyEndpoint::EndpointI::timeout(Ice::Int) const {
    std::cout << __FILE__ << ":" << __LINE__
	      << " NOT IMPLEMENTED!!" << std::endl;
    throw;
}

IceInternal::EndpointIPtr
PyEndpoint::EndpointI::connectionId(const ::std::string&) const {
    std::cout << __FILE__ << ":" << __LINE__
	      << " NOT IMPLEMENTED!!" << std::endl;
    throw;
}

bool
PyEndpoint::EndpointI::compress() const {
    std::cout << __FILE__ << ":" << __LINE__
	      << " NOT IMPLEMENTED!!" << std::endl;
    throw;
}

IceInternal::EndpointIPtr
PyEndpoint::EndpointI::compress(bool) const {
    std::cout << __FILE__ << ":" << __LINE__
	      << " NOT IMPLEMENTED!!" << std::endl;
    throw;
}

bool
PyEndpoint::EndpointI::datagram() const {

    std::cout << " - datagram() pyEndpoint @ " << _pyEndpoint.get() << std::endl;
    std::cout << " - this: " << this << std::endl;
    PyObjectPtr result = PyFunc::callMethod(_pyEndpoint, "datagram");
    return PyFunc::getAsBool(result);
}

bool
PyEndpoint::EndpointI::secure() const {

    std::cout << " - secure() pyEndpoint @ " << _pyEndpoint.get() << std::endl;
    std::cout << " - this: " << this << std::endl;
    PyObjectPtr result = PyFunc::callMethod(_pyEndpoint, "secure");
    return PyFunc::getAsBool(result);
}

bool
PyEndpoint::EndpointI::unknown() const {
    std::cout << __FILE__ << ":" << __LINE__
	      << " NOT IMPLEMENTED!!" << std::endl;
    throw;
}

IceInternal::TransceiverPtr
PyEndpoint::EndpointI::transceiver(IceInternal::EndpointIPtr&) const {
    std::cout << __FILE__ << ":" << __LINE__
	      << " NOT IMPLEMENTED!!" << std::endl;
    throw;
}

std::vector<IceInternal::ConnectorPtr>
PyEndpoint::EndpointI::connectors() const {
    // std::cout << __FILE__ << ":" << __LINE__
    //  	      << " NOT IMPLEMENTED!!" << std::endl;

    por alguna razon, aqui _pyEndpoint es un objeto distinto, que no tiene
	las estructuras correctamente inicializadas

    std::cout << " - connectors() pyEndpoint @ " << _pyEndpoint.get() << std::endl;
    std::cout << " - this: " << this << std::endl;
    PyObjectPtr result = PyFunc::callMethod(_pyEndpoint, "connectors");

    std::cout << "OK, IT MAY WORK!!" << std::endl;
    throw;
}

void
PyEndpoint::EndpointI::connectors_async(const IceInternal::EndpointI_connectorsPtr&) const {
    std::cout << __FILE__ << ":" << __LINE__
	      << " NOT IMPLEMENTED!!" << std::endl;
    throw;
}

IceInternal::AcceptorPtr
PyEndpoint::EndpointI::acceptor(IceInternal::EndpointIPtr&, const std::string&) const {
    std::cout << __FILE__ << ":" << __LINE__
	      << " NOT IMPLEMENTED!!" << std::endl;
    throw;
}

std::vector<IceInternal::EndpointIPtr>
PyEndpoint::EndpointI::expand() const {
    std::cout << __FILE__ << ":" << __LINE__
	      << " NOT IMPLEMENTED!!" << std::endl;
    throw;
}

bool
PyEndpoint::EndpointI::equivalent(const IceInternal::EndpointIPtr&) const {
    std::cout << __FILE__ << ":" << __LINE__
	      << " NOT IMPLEMENTED!!" << std::endl;
    throw;
}

bool
PyEndpoint::EndpointI::operator==(const IceInternal::EndpointI&) const {
    std::cout << __FILE__ << ":" << __LINE__
	      << " NOT IMPLEMENTED!!" << std::endl;
    throw;
}

bool
PyEndpoint::EndpointI::operator!=(const IceInternal::EndpointI&) const {
    std::cout << __FILE__ << ":" << __LINE__
	      << " NOT IMPLEMENTED!!" << std::endl;
    throw;
}

bool
PyEndpoint::EndpointI::operator<(const IceInternal::EndpointI&) const {
    std::cout << __FILE__ << ":" << __LINE__
	      << " NOT IMPLEMENTED!!" << std::endl;
    throw;
}

