// -*- mode: c++; coding: utf-8 -*-

//
// Copyright (c) 2012-2017 Oscar Aceña. All rights reserved.
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

#include <Ice/EndpointFactory.h>
#include <Ice/Communicator.h>
#include <Ice/ProtocolInstance.h>
#include <Ice/Plugin.h>

#include "PyUtils.h"
#include "PyFunctions.h"
#include "PyEndpointF.h"
#include "PyEndpointI.h"
#include "PyTransceiver.h"
#include "PyAcceptor.h"
#include "PyConnectorsCallback.h"
#include "PyCommunicator.h"
#include "PyBasicStream.h"
#include "debug.h"


extern "C" {

ICE_DECLSPEC_EXPORT Ice::Plugin*
addPyEndpointSupport(const Ice::CommunicatorPtr& ic,
		     const std::string& name,
		     const Ice::StringSeq& args) {
    trace();

    Py_Initialize();

    // If threads are not initialized, then the main thread is not a
    // python interpreter: init threads and release GIL
    if (not PyEval_ThreadsInitialized()) {
    	PyEval_InitThreads();
    	PyEval_ReleaseLock();
    }

    PyEndpoint::PyConnectorsCallback_initModule();
    PyEndpoint::BasicStream_initModule();

    IceInternal::EndpointFactoryPtr factory = new PyEndpoint::PyEndpointFactory(name, ic);
    return new IceInternal::EndpointFactoryPlugin(ic, factory);
}

}

PyEndpoint::PyEndpointI::PyEndpointI(const IceInternal::ProtocolInstancePtr& instance,
				     PyObjectPtr pyEndpoint) :
    _instance(instance),
    _pyEndpoint(pyEndpoint) {

    _protocol = PyFunc::getAsString(PyFunc::callMethod(_pyEndpoint, "protocol"));
    _connectionId = PyFunc::getAsString(PyFunc::callMethod(_pyEndpoint, "connectionId"));

    trace();
}

Ice::EndpointInfoPtr
PyEndpoint::PyEndpointI::getInfo() const {
    trace();
    fixme("Not implemented");
}

void
PyEndpoint::PyEndpointI::streamWrite(IceInternal::BasicStream* s) const {
    trace();
    PyGILEnsurer e;

    PyObjectPtr pyStream = BasicStream_new(s);
    PyObjectPtr args = Py_BuildValue("(O)", pyStream.get());
    PyFunc::callMethod(_pyEndpoint, "streamWrite", args);
}

Ice::Short
PyEndpoint::PyEndpointI::type() const {
    trace();

    PyObjectPtr result = PyFunc::callMethod(_pyEndpoint, "type");
    return PyFunc::getAsInteger(result);
}

const std::string&
PyEndpoint::PyEndpointI::protocol() const {
    trace();

    return _protocol;
}

Ice::Int
PyEndpoint::PyEndpointI::timeout() const {
    trace();

    return PyFunc::getAsInteger(PyFunc::callMethod(_pyEndpoint, "timeout"));
}

IceInternal::EndpointIPtr
PyEndpoint::PyEndpointI::timeout(Ice::Int) const {
    trace();
    fixme("Not implemented");
}

bool
PyEndpoint::PyEndpointI::compress() const {
    trace();

    return false;
}

IceInternal::EndpointIPtr
PyEndpoint::PyEndpointI::compress(bool enabled) const {
    trace();

    return const_cast<PyEndpoint::PyEndpointI*>(this);
}

bool
PyEndpoint::PyEndpointI::datagram() const {
    trace();

    return PyFunc::getAsBool(PyFunc::callMethod(_pyEndpoint, "datagram"));
}

bool
PyEndpoint::PyEndpointI::secure() const {
    trace();

    return PyFunc::getAsBool(PyFunc::callMethod(_pyEndpoint, "secure"));
}

PyEndpoint::PyEndpointIPtr
PyEndpoint::PyEndpointI::endpoint(const PyAcceptorPtr& acceptor) const {
    trace();
    PyGILEnsurer e;

    PyObjectPtr args = Py_BuildValue("(O)", acceptor->getPy().get());
    PyObjectPtr pyEndpoint = PyFunc::callMethod(_pyEndpoint, "endpoint", args);

    return new PyEndpointI(_instance, pyEndpoint);
}

PyEndpoint::PyEndpointIPtr
PyEndpoint::PyEndpointI::endpoint(const PyTransceiverPtr& trans) const {
    trace();
    PyGILEnsurer e;

    PyObjectPtr args = Py_BuildValue("(O)", trans->getPy().get());
    PyObjectPtr pyEndpoint = PyFunc::callMethod(_pyEndpoint, "endpoint", args);

    return new PyEndpointI(_instance, pyEndpoint);
}

const std::string&
PyEndpoint::PyEndpointI::connectionId() const {
    trace();

    return _connectionId;
}

IceInternal::EndpointIPtr
PyEndpoint::PyEndpointI::connectionId(const std::string&) const {
    trace();
    fixme("Not implemented");
}

IceInternal::TransceiverPtr
PyEndpoint::PyEndpointI::transceiver() const {
    trace();

    PyObjectPtr pyTransceiver = PyFunc::callMethod(_pyEndpoint, "transceiver");

    // if need an acceptor, return a NULL transceiver
    if (pyTransceiver == Py_None) {
        return NULL;
    }

    // otherwise, return a new transceiver
    return new PyEndpoint::PyTransceiver
	(const_cast<PyEndpoint::PyEndpointI*>(this), _instance, pyTransceiver);
}

IceInternal::AcceptorPtr
PyEndpoint::PyEndpointI::acceptor(const std::string&) const {
    trace();

    PyObjectPtr pyAcceptor = PyFunc::callMethod(_pyEndpoint, "acceptor");

    // if not connection oriented, return a NULL transceiver
    if (pyAcceptor == Py_None) {
        return NULL;
    }

    // otherwise, return the given acceptor
    return new PyEndpoint::PyAcceptor(const_cast<PyEndpointI*>(this), _instance, pyAcceptor);
}

std::vector<IceInternal::EndpointIPtr>
PyEndpoint::PyEndpointI::expand() const {
    trace();

    std::vector<IceInternal::EndpointIPtr> endps;
    endps.push_back(const_cast<PyEndpoint::PyEndpointI*>(this));
    return endps;
}

bool
PyEndpoint::PyEndpointI::equivalent(const IceInternal::EndpointIPtr& other) const {
    trace();

    const PyEndpoint::PyEndpointI* endp = dynamic_cast<const PyEndpoint::PyEndpointI*>(other.get());
    if (not endp) {
	return false;
    }

    PyGILEnsurer e;
    PyObjectPtr args = Py_BuildValue("(O)", endp->getPy().get());
    PyObjectPtr retval = PyFunc::callMethod(_pyEndpoint, "equivalent", args);
    return PyFunc::getAsBool(retval);
}

Ice::Int
PyEndpoint::PyEndpointI::hash() const {
    trace();
    fixme("Not implemented");
}

std::string
PyEndpoint::PyEndpointI::options() const {
    trace();

    PyObjectPtr retval = PyFunc::callMethod(_pyEndpoint, "options");
    return PyFunc::getAsString(retval);
}

void
PyEndpoint::PyEndpointI::connectors_async(Ice::EndpointSelectionType,
					  const IceInternal::EndpointI_connectorsPtr& cb) const {
    trace();

    PyGILEnsurer e;
    PyObjectPtr pyCb = PyConnectorsCallback_new(_instance, cb);

    // this returns a new reference
    PyObjectPtr args = Py_BuildValue("(O)", pyCb.get());

    PyFunc::callMethod(_pyEndpoint, "connectors_async", args);
}

bool
PyEndpoint::PyEndpointI::operator==(const Ice::LocalObject&) const {
    trace();
    fixme("Not implemented");
}

bool
PyEndpoint::PyEndpointI::operator<(const Ice::LocalObject& other) const {
    trace();

    const PyEndpoint::PyEndpointI* p
	= dynamic_cast<const PyEndpoint::PyEndpointI*>(&other);

    if (not p) {
        const IceInternal::EndpointI* e
	    = dynamic_cast<const IceInternal::EndpointI*>(&other);

        if (not e) {
            return false;
        }

        return type() < e->type();
    }

    // Py_BuildValue returns a new reference
    PyGILEnsurer e;
    PyObjectPtr pyOther = p->_pyEndpoint;
    PyObjectPtr args = Py_BuildValue("(O)", pyOther.get());
    return PyFunc::getAsBool(PyFunc::callMethod(_pyEndpoint, "__lt__", args));
}

void
PyEndpoint::PyEndpointI::initWithOptions(std::vector<std::string>& args, bool oaEndpoint) {
    trace();
    PyGILEnsurer e;

    // PyTuple_SetItem steals a reference to object

    PyObject* args_tuple = PyTuple_New(args.size());
    for (unsigned int i=0; i<args.size(); i++){
	PyObject* item = PyUnicode_FromString(args[i].c_str());
	PyTuple_SetItem(args_tuple, i, item);
    }

    PyObjectPtr fn_args = PyTuple_New(2);
    PyTuple_SetItem(fn_args, 0, args_tuple);
    PyTuple_SetItem(fn_args, 1, Py_BuildValue("b", oaEndpoint));

    PyFunc::callMethod(_pyEndpoint, "initWithOptions", fn_args);

    // Replace argument vector with unknown args
    std::vector<std::string> unknown;
    args = unknown;
}

void
PyEndpoint::PyEndpointI::initWithOptions(std::vector<std::string>&) {
    trace();
    fixme("Not implemented");
}

// --------------------------------------------------------------------------------

PyEndpoint::PyEndpointFactory::PyEndpointFactory(const std::string& name,
						 const Ice::CommunicatorPtr& ic) {
    trace();

    std::string preffix = name;
    Ice::PropertiesPtr props = ic->getProperties();

    std::string moduleName = props->getProperty(preffix + ".Module");
    if (moduleName.empty()) {
	std::string msg = "Property '" + preffix + ".Module' not set!";
	throw Ice::PluginInitializationException("", 0, msg);
    }

    std::string factoryName =
     	props->getPropertyWithDefault(preffix + ".Factory", "EndpointFactoryI");

    // all of this creates new references
    PyGILEnsurer e;
    _pyCommunicator = PyEndpoint::createCommunicator(ic);
    PyObjectPtr module = PyFunc::importModule(moduleName);
    PyObjectPtr factoryClass = PyFunc::getClass(module, factoryName);
    PyObjectPtr call_args = Py_BuildValue("(O)", _pyCommunicator.get());

    _pyFactory = PyFunc::newInstance(factoryClass, call_args);

    Ice::Short endp_type = type();
    std::string endp_protocol = protocol();
    bool endp_secure = false;

    _instance = new IceInternal::ProtocolInstance(ic, endp_type, endp_protocol, endp_secure);
}

PyEndpoint::PyEndpointFactory::~PyEndpointFactory() {
    trace();
}

Ice::Short
PyEndpoint::PyEndpointFactory::type() const {
    trace();

    PyObjectPtr result = PyFunc::callMethod(_pyFactory, "type");
    return PyFunc::getAsInteger(result);
}

std::string
PyEndpoint::PyEndpointFactory::protocol() const {
    trace();

    PyObjectPtr result = PyFunc::callMethod(_pyFactory, "protocol");
    return PyFunc::getAsString(result);
}

IceInternal::EndpointIPtr
PyEndpoint::PyEndpointFactory::create(std::vector<std::string>& args, bool oaEndpoint) const {
    trace();

    PyObjectPtr pyEndpoint = PyFunc::callMethod(_pyFactory, "create");
    PyEndpoint::PyEndpointIPtr endp = new PyEndpoint::PyEndpointI(_instance, pyEndpoint);
    endp->initWithOptions(args, oaEndpoint);
    return endp;
}

IceInternal::EndpointIPtr
PyEndpoint::PyEndpointFactory::read(IceInternal::BasicStream* s) const {
    trace();
    PyGILEnsurer e;

    PyObjectPtr pyStream = BasicStream_new(s);
    PyObjectPtr args = Py_BuildValue("(O)", pyStream.get());
    PyObjectPtr pyEndpoint = PyFunc::callMethod(_pyFactory, "read", args);

    if (pyEndpoint == Py_None) {
    	std::cerr << "ValueError, invalid endpoint returned!"
		  << std::endl;
	throw PyFunc::RuntimeError();
    }

    return new PyEndpoint::PyEndpointI(_instance, pyEndpoint);
}

void
PyEndpoint::PyEndpointFactory::destroy() {
    trace();

    PyFunc::callMethod(_pyFactory, "destroy");
    _instance = 0;
}

IceInternal::EndpointFactoryPtr
PyEndpoint::PyEndpointFactory::clone(const IceInternal::ProtocolInstancePtr&) const {
    trace();

    fixme("Not implemented");
    return NULL;
}
