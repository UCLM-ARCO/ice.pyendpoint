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

#include <boost/python.hpp>

#include <Ice/EndpointFactory.h>
#include <Ice/Communicator.h>
#include <Ice/ProtocolInstance.h>
#include <Ice/Plugin.h>

#include "PyEndpointI.h"
#include "debug.h"

namespace bp = boost::python;

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

    std::string preffix = name;
    Ice::PropertiesPtr props = ic->getProperties();
    std::string moduleName = props->getProperty(preffix + ".Module");
    if (!moduleName.empty()) {
     	std::cerr << "Property '" + preffix + ".Module' not set!" << std::endl;
	throw FIXME_createAValidException;
    }

    // std::string factoryName =
    // 	props->getPropertyWithDefault(preffix + ".Factory", "EndpointFactoryI");

    // // all of this creates new references
    // PyObjectPtr module = PyFunc::importModule(moduleName);
    // PyObjectPtr factoryClass = PyFunc::getClass(module, factoryName);
    // PyObjectPtr pyCom = IcePy::createCommunicator(instance->communicator());
    // PyObjectPtr args = Py_BuildValue("(O)", pyCom.get());

    // _pyFactory = PyFunc::newInstance(factoryClass, args);








    IceInternal::EndpointFactoryPtr factory = new PyEndpoint::PyEndpointFactory(ic);
    return new IceInternal::EndpointFactoryPlugin(ic, factory);
}

}

PyEndpoint::PyEndpointFactory::PyEndpointFactory(const Ice::CommunicatorPtr& ic) {
    trace();

    // FIXME: take this from Python's factory
    Ice::Short type = -1;
    std::string protocol = "";
    bool secure = false;

    _instance = new IceInternal::ProtocolInstance(ic, type, protocol, secure);
}

PyEndpoint::PyEndpointFactory::~PyEndpointFactory() {
    trace();
}

Ice::Short
PyEndpoint::PyEndpointFactory::type() const {
    trace();

    return -1;
}

std::string
PyEndpoint::PyEndpointFactory::protocol() const {
    trace();

    return "";
}

IceInternal::EndpointIPtr
PyEndpoint::PyEndpointFactory::create(std::vector<std::string>&, bool) const {
    trace();

    return NULL;
}

IceInternal::EndpointIPtr
PyEndpoint::PyEndpointFactory::read(IceInternal::BasicStream*) const {
    trace();

    return NULL;
}

void
PyEndpoint::PyEndpointFactory::destroy() {
    trace();
}

IceInternal::EndpointFactoryPtr
PyEndpoint::PyEndpointFactory::clone(const IceInternal::ProtocolInstancePtr&) const {
    trace();

    return NULL;
}
