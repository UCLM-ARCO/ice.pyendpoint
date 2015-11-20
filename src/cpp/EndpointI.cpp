/* -*- mode: c++; coding: utf-8; truncate-lines: true -*- */

//
// Copyright (c) 2012-2014 Oscar Aceña. All rights reserved.
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

#include <Ice/Communicator.h>
#include <Ice/Properties.h>
#include <Ice/LocalException.h>

#include "PyFunctions.h"
#include "TransceiverI.h"
#include "EndpointI.h"
#include "AcceptorI.h"
#include "Instance.h"
#include "BasicStream.h"

#include "debug.h"


PyEndpoint::EndpointI::EndpointI(const InstancePtr& instance, PyObjectPtr pyEndpoint) :
    _instance(instance),
    _pyEndpoint(pyEndpoint) {

    trace();
}

PyEndpoint::EndpointI::~EndpointI() {
};

void
PyEndpoint::EndpointI::streamWrite(IceInternal::BasicStream* s) const {
    trace();

    PyObjectPtr pyStream = BasicStream_new(s);
    PyObjectPtr args = Py_BuildValue("(O)", pyStream.get());
    PyFunc::callMethod(_pyEndpoint, "streamWrite", args);
}

std::string
PyEndpoint::EndpointI::toString() const {
    trace();

    PyObjectPtr result = PyFunc::callMethod(_pyEndpoint, "toString");
    return PyFunc::getAsString(result);
}

Ice::EndpointInfoPtr
PyEndpoint::EndpointI::getInfo() const {
    trace();
    fixme("Not implemented");
}

Ice::Short
PyEndpoint::EndpointI::type() const {
    trace();

    PyObjectPtr result = PyFunc::callMethod(_pyEndpoint, "type");
    return PyFunc::getAsInteger(result);
}

std::string
PyEndpoint::EndpointI::protocol() const {
    trace();
    fixme("Not implemented");
}

Ice::Int
PyEndpoint::EndpointI::timeout() const {
    trace();

    PyObjectPtr result = PyFunc::callMethod(_pyEndpoint, "timeout");
    return PyFunc::getAsInteger(result);
}

IceInternal::EndpointIPtr
PyEndpoint::EndpointI::timeout(Ice::Int timeout) const {
    trace();

    return const_cast<EndpointI*>(this);
}

IceInternal::EndpointIPtr
PyEndpoint::EndpointI::connectionId(const std::string& connectionId) const {
    trace();
    fixme("Not implemented");
}

bool
PyEndpoint::EndpointI::compress() const {
    trace();

    PyObjectPtr result = PyFunc::callMethod(_pyEndpoint, "getCompress");
    return PyFunc::getAsBool(result);
}

IceInternal::EndpointIPtr
PyEndpoint::EndpointI::compress(bool compress) const {
    trace();

    // this returns a new reference
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
    trace();

    PyObjectPtr result = PyFunc::callMethod(_pyEndpoint, "datagram");
    return PyFunc::getAsBool(result);
}

bool
PyEndpoint::EndpointI::secure() const {
    trace();

    PyObjectPtr result = PyFunc::callMethod(_pyEndpoint, "secure");
    return PyFunc::getAsBool(result);
}

IceInternal::TransceiverPtr
PyEndpoint::EndpointI::transceiver(IceInternal::EndpointIPtr& endp) const {
    trace();

    PyObjectPtr pyEndp;
    PyObjectPtr pyTransceiver;
    TransceiverI* trans;

    PyObjectPtr result = PyFunc::callMethod(_pyEndpoint, "transceiver");

    // this put on out params borrowed references
    if (not PyArg_ParseTuple(result, "OO", &pyEndp, &pyTransceiver)) {
    	std::cerr << "ValueError, need endpoint and transceiver!" << std::endl;
	throw PyFunc::RuntimeError();
    }

    // need to 'steal' the borrowed references from PyArg_ParseTuple
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
PyEndpoint::EndpointI::connectors(Ice::EndpointSelectionType selType) const {
    trace();
    fixme("Not implemented");
}

void
PyEndpoint::EndpointI::connectors_async(Ice::EndpointSelectionType selType, const IceInternal::EndpointI_connectorsPtr& cb) const {
    trace();

    PyObjectPtr pyCb = ConnectorsCallback_new(_instance, cb);

    // this returns a new reference
    PyObjectPtr args = Py_BuildValue("(O)", pyCb.get());

    PyFunc::callMethod(_pyEndpoint, "connectors_async", args);
}

IceInternal::AcceptorPtr
PyEndpoint::EndpointI::acceptor(IceInternal::EndpointIPtr& endp,
				const std::string&) const {
    trace();

    PyObjectPtr pyEndp;
    PyObjectPtr pyAcceptor;
    AcceptorI* acceptor;

    PyObjectPtr result = PyFunc::callMethod(_pyEndpoint, "acceptor");

    // this put on out params borrowed references
    if (not PyArg_ParseTuple(result, "OO", &pyEndp, &pyAcceptor)) {
    	std::cerr << "ValueError, need endpoint and acceptor!" << std::endl;
	throw PyFunc::RuntimeError();
    }

    // need to 'steal' the borrowed references from PyArg_ParseTuple
    pyEndp.steal();
    pyAcceptor.steal();

    endp = new PyEndpoint::EndpointI(_instance, pyEndp);
    acceptor = new PyEndpoint::AcceptorI(_instance, pyAcceptor);

    return acceptor;
}

std::vector<IceInternal::EndpointIPtr>
PyEndpoint::EndpointI::expand() const {
    trace();

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

	// PyList_GetItem returns a borrowed reference
	pyEndpoint = PyObjectPtr::fromBorrowed(PyList_GetItem(endpList, i));

	endpoint = new PyEndpoint::EndpointI(_instance, pyEndpoint);
	retval.push_back(endpoint);
    }

    return retval;
}

bool
PyEndpoint::EndpointI::equivalent(const IceInternal::EndpointIPtr& endpoint) const {
    trace();

    const EndpointI* endp = dynamic_cast<const EndpointI*>(endpoint.get());
    if(not endp) {
	return false;
    }

    fixme("Not implemented");
}

bool
PyEndpoint::EndpointI::operator==(const Ice::LocalObject& other) const {
    trace();
    fixme("Not implemented");
}

bool
PyEndpoint::EndpointI::operator<(const Ice::LocalObject& other) const {
    trace();

    const EndpointI* p = dynamic_cast<const EndpointI*>(&other);
    if (not p) {
        const IceInternal::EndpointI* e
	    = dynamic_cast<const IceInternal::EndpointI*>(&other);

        if (not e) {
            return false;
        }

        return type() < e->type();
    }

    PyObjectPtr pyOther = dynamic_cast<const EndpointI*>(&other)->_pyEndpoint;

    // Py_BuildValue returns a new reference
    PyObjectPtr args = Py_BuildValue("(O)", pyOther.get());

    PyObjectPtr result = PyFunc::callMethod(_pyEndpoint, "__lt__", args);
    return PyFunc::getAsBool(result);
}

std::vector<IceInternal::ConnectorPtr>
PyEndpoint::EndpointI::connectors(const std::vector<IceInternal::Address>&) const {
    trace();
    fixme("Not implemented");
}

Ice::Int
PyEndpoint::EndpointI::hashInit() const {
    trace();
    fixme("Not implemented");
}

PyEndpoint::EndpointFactoryI::EndpointFactoryI(const InstancePtr& instance) :
    _instance(instance) {
    trace();

    std::string preffix = instance->pluginName;

    Ice::PropertiesPtr props = instance->communicator()->getProperties();
    std::string moduleName = props->getProperty(preffix + ".Module");
    if (moduleName.empty()) {
    	std::cerr << "Property '" + preffix + ".Module' not set!" << std::endl;
    	throw PyFunc::RuntimeError();
    }

    std::string factoryName =
	props->getPropertyWithDefault(preffix + ".Factory", "EndpointFactoryI");

    // all of this creates new references
    PyObjectPtr module = PyFunc::importModule(moduleName);
    PyObjectPtr factoryClass = PyFunc::getClass(module, factoryName);
    PyObjectPtr pyCom = IcePy::createCommunicator(instance->communicator());
    PyObjectPtr args = Py_BuildValue("(O)", pyCom.get());

    _pyFactory = PyFunc::newInstance(factoryClass, args);
}

PyEndpoint::EndpointFactoryI::~EndpointFactoryI() {
    trace();
}

Ice::Short
PyEndpoint::EndpointFactoryI::type() const {
    trace();

    PyObjectPtr result = PyFunc::callMethod(_pyFactory, "type");
    return PyFunc::getAsInteger(result);
}

std::string
PyEndpoint::EndpointFactoryI::protocol() const {
    trace();

    /* NOTE: due an unknown error, on this stage, the Python object
       'True', is decremented, and eventually it will be destroyed. To
       avoid this happening, make sure here that it's reference count
       never gets near 0 */
    if (Py_True->ob_refcnt < 32000)
	Py_True->ob_refcnt = 32000;

    PyObjectPtr result = PyFunc::callMethod(_pyFactory, "protocol");
    return PyFunc::getAsString(result);
}

IceInternal::EndpointIPtr
PyEndpoint::EndpointFactoryI::create(const std::string& str, bool oaEndpoint) const {
    trace();

    PyObjectPtr args = Py_BuildValue("sb", str.c_str(), oaEndpoint);
    PyObjectPtr pyEndpoint = PyFunc::callMethod(_pyFactory, "create", args);

    return new EndpointI(_instance, pyEndpoint);
}

IceInternal::EndpointIPtr
PyEndpoint::EndpointFactoryI::read(IceInternal::BasicStream* s) const {
    trace();

    PyObjectPtr pyStream = BasicStream_new(s);
    PyObjectPtr args = Py_BuildValue("(O)", pyStream.get());
    PyObjectPtr pyEndpoint = PyFunc::callMethod(_pyFactory, "read", args);

    if (pyEndpoint == Py_None) {
    	std::cerr << "ValueError, invalid endpoint returned!"
		  << std::endl;
	throw PyFunc::RuntimeError();
    }

    return new EndpointI(_instance, pyEndpoint);
}

void
PyEndpoint::EndpointFactoryI::destroy() {
    trace();

    PyFunc::callMethod(_pyFactory, "destroy");
    _instance = 0;
}
