/* -*- mode: c++; coding: utf-8 -*- */

#include "EndpointI.h"


PyEndpoint::EndpointFactoryI::~EndpointFactoryI() {
}

Ice::Short
PyEndpoint::EndpointFactoryI::type() const {
    // FIXME: this must be set in python
    return 10;
}

std::string
PyEndpoint::EndpointFactoryI::protocol() const {
    // FIXME: this must be set in python
    return "example";
}

IceInternal::EndpointIPtr
PyEndpoint::EndpointFactoryI::create(const std::string&, bool) const {
    throw;
}

IceInternal::EndpointIPtr
PyEndpoint::EndpointFactoryI::read(IceInternal::BasicStream*) const {
    throw;
}

void
PyEndpoint::EndpointFactoryI::destroy() {
}

PyEndpoint::EndpointFactoryI::EndpointFactoryI(const InstancePtr&) {
}
