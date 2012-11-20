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

#include <Python.h>  // include first this to avoid GCC annoying warnings

// #include "/home/oscar.acena/usr/src/zeroc-ice-3.4.2/py/modules/IcePy/Communicator.h"

#include <Ice/Communicator.h>
#include <Ice/Properties.h>
#include <Ice/LocalException.h>

#include "PyFunctions.h"
#include "TransceiverI.h"
#include "EndpointI.h"
#include "Instance.h"

#include "debug.h"


PyEndpoint::EndpointI::EndpointI(const InstancePtr& instance, PyObjectPtr pyEndpoint) :
    _instance(instance),
    _pyEndpoint(pyEndpoint) {

    IDG std::cout << " - call to EndpointI() [1] (this: "
		  << this << ")" << std::endl;
}

void
PyEndpoint::EndpointI::streamWrite(IceInternal::BasicStream* s) const {

    IDG std::cout << " - call to EndpointI::streamWrite(s) [1] (this: "
		  << this << ")" << std::endl;

    std::cout << __FILE__ << ":" << __LINE__
	      << " NOT IMPLEMENTED!!" << std::endl;
    throw;
}

std::string
PyEndpoint::EndpointI::toString() const {

    IDG std::cout << " - call to EndpointI::toString() (this: "
		  << this << ")" << std::endl;

    PyObjectPtr result = PyFunc::callMethod(_pyEndpoint, "toString");
    return PyFunc::getAsString(result);
}

Ice::EndpointInfoPtr
PyEndpoint::EndpointI::getInfo() const {

    IDG std::cout << " - call to EndpointI::getInfo() (this: "
		  << this << ")" << std::endl;

    std::cout << __FILE__ << ":" << __LINE__
	      << ": Not implemented!" << std::endl;
    throw;
}

Ice::Short
PyEndpoint::EndpointI::type() const {

    IDG std::cout << " - call to EndpointI::type() (this: "
		  << this << ")" << std::endl;

    PyObjectPtr result = PyFunc::callMethod(_pyEndpoint, "type");
    return PyFunc::getAsInteger(result);
}

Ice::Int
PyEndpoint::EndpointI::timeout() const {

    IDG std::cout << " - call to EndpointI::timeout() (this: "
		  << this << ")" << std::endl;

    PyObjectPtr result = PyFunc::callMethod(_pyEndpoint, "timeout");
    return PyFunc::getAsInteger(result);
}

IceInternal::EndpointIPtr
PyEndpoint::EndpointI::timeout(Ice::Int timeout) const {

    IDG std::cout << " - call to EndpointI::timeout("
		  << timeout << ") (this: "
		  << this << ")" << std::endl;

    std::cout << __FILE__ << ":" << __LINE__
	      << ": Not implemented!" << std::endl;
    throw;
}

IceInternal::EndpointIPtr
PyEndpoint::EndpointI::connectionId(const std::string& connectionId) const {

    IDG std::cout << " - call to EndpointI::connectionId('"
		  << connectionId << "') (this: "
		  << this << ")" << std::endl;

    std::cout << __FILE__ << ":" << __LINE__
	      << ": Not implemented!" << std::endl;
    throw;
}

bool
PyEndpoint::EndpointI::compress() const {

    IDG std::cout << " - call to EndpointI::compress() (this: "
		  << this << ")" << std::endl;

    PyObjectPtr result = PyFunc::callMethod(_pyEndpoint, "getCompress");
    return PyFunc::getAsBool(result);
}

IceInternal::EndpointIPtr
PyEndpoint::EndpointI::compress(bool compress) const {

    IDG std::cout << " - call to EndpointI::compress("
		  << compress << ") (this: "
		  << this << ")" << std::endl;

    PyObjectPtr args = Py_BuildValue("(b)", compress);
    PyObjectPtr pyEndpoint = PyFunc::callMethod(_pyEndpoint, "setCompress", args);

    if (pyEndpoint == _pyEndpoint) {
	return const_cast<EndpointI*>(this);
    }
    else {
	return new EndpointI(_instance, pyEndpoint);
    }
}

bool
PyEndpoint::EndpointI::datagram() const {

    IDG std::cout << " - call to EndpointI::datagram() (this: "
		  << this << ")" << std::endl;

    PyObjectPtr result = PyFunc::callMethod(_pyEndpoint, "datagram");
    return PyFunc::getAsBool(result);
}

bool
PyEndpoint::EndpointI::secure() const {

    IDG std::cout << " - call to EndpointI::secure() (this: "
		  << this << ")" << std::endl;

    PyObjectPtr result = PyFunc::callMethod(_pyEndpoint, "secure");
    return PyFunc::getAsBool(result);
}

IceInternal::TransceiverPtr
PyEndpoint::EndpointI::transceiver(IceInternal::EndpointIPtr& endp) const {

    IDG std::cout << " - call to EndpointI::transceiver(endp) (this: "
		  << this << ")" << std::endl;

    PyObjectPtr pyEndp;
    PyObjectPtr pyTransceiver;
    TransceiverI* trans;

    PyObjectPtr result = PyFunc::callMethod(_pyEndpoint, "transceiver");
    if (not PyArg_ParseTuple(result, "OO", &pyEndp, &pyTransceiver)) {
    	std::cerr << "ValueError, need endpoint and transceiver!" << std::endl;
	throw PyFunc::RuntimeError();
    }

    // need to 'steal' the borrowed references from PyArg
    pyEndp.steal();
    pyTransceiver.steal();

    // if need an acceptor, return a NULL transceiver
    if (pyTransceiver == Py_None) {
	endp = const_cast<EndpointI*>(this);
        return 0;
    }

    // otherwise, return the given transceiver
    trans = new PyEndpoint::TransceiverI(_instance, pyTransceiver);

    if (pyEndp == _pyEndpoint) {
	endp = const_cast<EndpointI*>(this);
    }
    else {
	endp = new EndpointI(_instance, pyEndp);
    }

    return trans;
}

std::vector<IceInternal::ConnectorPtr>
PyEndpoint::EndpointI::connectors() const {

    IDG std::cout << " - call to EndpointI::connectors() (this: "
		  << this << ")" << std::endl;

    std::cout << __FILE__ << ":" << __LINE__
	      << ": Not implemented!" << std::endl;
    throw;
}

void
PyEndpoint::EndpointI::connectors_async(const IceInternal::EndpointI_connectorsPtr& cb) const {

    IDG std::cout << " - call to EndpointI::connectors_async(callback) (this: "
		  << this << ")" << std::endl;

    PyObjectPtr pyCb = ConnectorsCallback_new(_instance, cb);
    PyObjectPtr args = Py_BuildValue("(O)", pyCb.get());
    PyFunc::callMethod(_pyEndpoint, "connectors_async", args);
}

IceInternal::AcceptorPtr
PyEndpoint::EndpointI::acceptor(IceInternal::EndpointIPtr& endp,
				const std::string& adapterName) const {

    IDG std::cout << " - call to EndpointI::acceptor(endp, '"
		  << adapterName << "') (this: "
		  << this << ")" << std::endl;

    std::cout << __FILE__ << ":" << __LINE__
	      << ": Not implemented!" << std::endl;
    throw;
}

std::vector<IceInternal::EndpointIPtr>
PyEndpoint::EndpointI::expand() const {

    IDG std::cout << " - call to EndpointI::expand() (this: "
		  << this << ")" << std::endl;

    PyObjectPtr endpList = PyFunc::callMethod(_pyEndpoint, "expand");
    if (not PyList_Check(endpList)) {
    	std::cerr << "ValueError, need endpoint list from expand()" << std::endl;
     	throw PyFunc::RuntimeError();
    }

    if (PyList_Size(endpList) == 0) {
    	std::cerr << "ValueError, need at least one endpoint from expand()" << std::endl;
     	throw PyFunc::RuntimeError();
    }


    IceInternal::EndpointIPtr endpoint;
    PyObjectPtr pyEndpoint;
    std::vector<IceInternal::EndpointIPtr> retval;

    for (short i=0; i<PyList_Size(endpList); i++) {
	pyEndpoint = PyObjectPtr::fromBorrowed(PyList_GetItem(endpList, i));
	endpoint = new PyEndpoint::EndpointI(_instance, pyEndpoint);
	retval.push_back(endpoint);
    }

    return retval;
}

bool
PyEndpoint::EndpointI::equivalent(const IceInternal::EndpointIPtr& endpoint) const {

    IDG std::cout << " - call to EndpointI::equivalent() (this: "
		  << this << ")" << std::endl;

    std::cout << __FILE__ << ":" << __LINE__
	      << ": Not implemented!" << std::endl;
    throw;
}

bool
PyEndpoint::EndpointI::operator==(const Ice::LocalObject& other) const {

    IDG std::cout << " - call to EndpointI::operator==(other) (this: "
		  << this << ")" << std::endl;

    std::cout << __FILE__ << ":" << __LINE__
	      << ": Not implemented!" << std::endl;
    throw;
}

bool
PyEndpoint::EndpointI::operator<(const Ice::LocalObject& other) const {

    IDG std::cout << " - call to EndpointI::operator<(other) (this: "
		  << this << ")" << std::endl;

    PyObjectPtr pyOther = dynamic_cast<const EndpointI*>(&other)->_pyEndpoint;
    PyObjectPtr args = Py_BuildValue("(O)", pyOther.get());
    PyObjectPtr result = PyFunc::callMethod(_pyEndpoint, "__lt__", args);
    return PyFunc::getAsBool(result);
}

Ice::Int
PyEndpoint::EndpointI::hashInit() const {

    IDG std::cout << " - call to EndpointI::hashInit() (this: "
		  << this << ")" << std::endl;

    std::cout << __FILE__ << ":" << __LINE__
	      << ": Not implemented!" << std::endl;
    throw;
}

PyEndpoint::EndpointFactoryI::EndpointFactoryI(const InstancePtr& instance) :
    _instance(instance) {

    IDG std::cout << " - call to EndpointFactoryI() (this: "
		  << this << ")" << std::endl;

    Ice::PropertiesPtr props = instance->communicator()->getProperties();
    std::string moduleName = props->getProperty("PyEndpoint.Module");
    if (moduleName.empty()) {
    	std::cerr << "Property 'PyEndpoint.Module' not set!" << std::endl;
    	throw PyFunc::RuntimeError();
    }

    std::string factoryName =
	props->getPropertyWithDefault("PyEndpoint.Factory", "EndpointFacoryI");

    PyObjectPtr module = PyFunc::importModule(moduleName);
    PyObjectPtr factoryClass = PyFunc::getClass(module, factoryName);
    PyObjectPtr pyCom = IcePy::createCommunicator(instance->communicator());
    PyObjectPtr args = Py_BuildValue("(O)", pyCom.get());

    _pyFactory = PyFunc::newInstance(factoryClass, args);
}

PyEndpoint::EndpointFactoryI::~EndpointFactoryI() {

    IDG std::cout << " - call to ~EndpointFactoryI() (this: "
		  << this << ")" << std::endl;
}

Ice::Short
PyEndpoint::EndpointFactoryI::type() const {

    IDG std::cout << " - call to EndpointFactoryI::type() (this: "
		  << this << ")" << std::endl;

    PyObjectPtr result = PyFunc::callMethod(_pyFactory, "type");
    return PyFunc::getAsInteger(result);
}

std::string
PyEndpoint::EndpointFactoryI::protocol() const {

    IDG std::cout << " - call to EndpointFactoryI::protocol() (this: "
		  << this << ")" << std::endl;

    PyObjectPtr result = PyFunc::callMethod(_pyFactory, "protocol");
    return PyFunc::getAsString(result);
}

IceInternal::EndpointIPtr
PyEndpoint::EndpointFactoryI::create(const std::string& str, bool oaEndpoint) const {

    IDG std::cout << " - call to EndpointFactoryI::create('"
		  << str << "', " << oaEndpoint << ") (this: "
		  << this << ")" << std::endl;

    PyObjectPtr args = Py_BuildValue("sb", str.c_str(), oaEndpoint);
    PyObjectPtr pyEndpoint = PyFunc::callMethod(_pyFactory, "create", args);

    return new EndpointI(_instance, pyEndpoint);
}

IceInternal::EndpointIPtr
PyEndpoint::EndpointFactoryI::read(IceInternal::BasicStream* s) const {

    IDG std::cout << " - call to EndpointFactoryI::read(s) (this: "
		  << this << ")" << std::endl;

    std::cout << __FILE__ << ":" << __LINE__
	      << " NOT IMPLEMENTED!!" << std::endl;
    throw;
}

void
PyEndpoint::EndpointFactoryI::destroy() {

    IDG std::cout << " - call to EndpointFactoryI::destroy() (this: "
		  << this << ")" << std::endl;

    PyFunc::callMethod(_pyFactory, "destroy");
    _instance = 0;
}
