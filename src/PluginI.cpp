// -*- mode: c++; coding: utf-8 -*-

#include <iostream>
#include "PluginI.h"

// loader function
extern "C" {

ICE_DECLSPEC_EXPORT Ice::Plugin*
addPyEndpointSupport(const Ice::CommunicatorPtr& communicator,
		     const std::string& name,
		     const Ice::StringSeq& args) {

    std::cout << "Se va a cargar un plugin llamado: '"
	      << name << "'" << std::endl;
    return new PluginI();
}}

void
PluginI::initialize() {
    std::cout << "Ha sido cargado el plugin más tonto del mundo." << std::endl;
}

void
PluginI::destroy() {
    std::cout << "Ha sido descargado el plugin más tonto del mundo." << std::endl;
}
