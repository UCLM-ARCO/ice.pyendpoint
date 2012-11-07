/* -*- mode: c++; coding: utf-8 -*- */

#include <Ice/ProtocolPluginFacade.h>
#include "Instance.h"
#include "EndpointI.h"


IceUtil::Shared*
IceInternal::upCast(PyEndpoint::Instance* p) {
    return p;
}

PyEndpoint::Instance::Instance(const Ice::CommunicatorPtr& communicator) {

    _facade = IceInternal::getProtocolPluginFacade(communicator);
    _facade->addEndpointFactory(new EndpointFactoryI(this));
}

void
PyEndpoint::Instance::initialize() {
}

void
PyEndpoint::Instance::destroy() {
}
