// -*- mode: c++; coding: utf-8 -*-

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

#include <Ice/EndpointFactory.h>
#include <Ice/Communicator.h>
#include <Ice/ProtocolInstance.h>
#include <Ice/Plugin.h>

#include <IcePy/Communicator.h>

#include "PyUtils.h"
#include "PyFunctions.h"
#include "PyEndpointI.h"
#include "debug.h"

extern "C" {

Ice::Plugin*
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

    IceInternal::EndpointFactoryPtr factory = new PyEndpoint::PyEndpointFactory(name, ic);
    return new IceInternal::EndpointFactoryPlugin(ic, factory);
}

}

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
    PyObjectPtr module = PyFunc::importModule(moduleName);
    PyObjectPtr factoryClass = PyFunc::getClass(module, factoryName);
    PyObjectPtr pyCom = IcePy::createCommunicator(ic);
    PyObjectPtr call_args = Py_BuildValue("(O)", pyCom.get());

    _pyFactory = PyFunc::newInstance(factoryClass, call_args);

    // FIXME: take this from Python's factory
    Ice::Short endp_type = type();
    std::string endp_protocol = "";
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

    // PyTuple_SetItem steals a reference to object

    // PyObject* str_tuple = PyTuple_New(str.size());
    // for (unsigned int i=0; i<str.size(); i++){
    // 	PyObject* item = PyString_FromString(str[i].c_str());
    // 	PyTuple_SetItem(str_tuple, i, item);
    // }

    // PyObjectPtr args = PyTuple_New(2);
    // PyTuple_SetItem(args, 0, Py_BuildValue("b", oaEndpoint));
    // PyTuple_SetItem(args, 1, str_tuple);

    // ZeroC code:
    // IPEndpointIPtr endpt = new TcpEndpointI(_instance);
    // endpt->initWithOptions(args, oaEndpoint);
    // return endpt;

    PyObjectPtr pyEndpoint = PyFunc::callMethod(_pyFactory, "create");
    IceInternal::EndpointIPtr endp = new PyEndpoint::PyEndpointI(_instance, pyEndpoint);
    endp->initWithOptions(args, oaEndpoint);
    return endp;
}

IceInternal::EndpointIPtr
PyEndpoint::PyEndpointFactory::read(IceInternal::BasicStream*) const {
    trace();

    fixme("Not implemented");
    return NULL;
}

void
PyEndpoint::PyEndpointFactory::destroy() {
    trace();

    fixme("Not implemented");
}

IceInternal::EndpointFactoryPtr
PyEndpoint::PyEndpointFactory::clone(const IceInternal::ProtocolInstancePtr&) const {
    trace();

    fixme("Not implemented");
    return NULL;
}
