// -*- mode: c++; coding: utf-8 -*-

#include "PluginI.h"
#include "Instance.h"


// loader function
extern "C" {

using namespace PyEndpoint;

ICE_DECLSPEC_EXPORT Ice::Plugin*
addPyEndpointSupport(const Ice::CommunicatorPtr& communicator,
		     const std::string& name,
		     const Ice::StringSeq& args) {
    return new PluginI(communicator);
}}


// Plugin interface
PyEndpoint::PluginI::PluginI(const Ice::CommunicatorPtr& communicator) {
    _instance = new Instance(communicator);
}

void
PyEndpoint::PluginI::initialize() {
    _instance->initialize();
}

void
PyEndpoint::PluginI::destroy() {
    _instance->destroy();
    _instance = 0;
}
