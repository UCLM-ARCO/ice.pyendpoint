// -*- mode: c++; coding: utf-8 -*-

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
#include <Ice/BuiltinSequences.h>

#include "PluginI.h"
#include "Instance.h"

// loader function
extern "C" {

using namespace PyEndpoint;

ICE_DECLSPEC_EXPORT Ice::Plugin*
addPyEndpointSupport(const Ice::CommunicatorPtr& ic,
		     const std::string& name,
		     const Ice::StringSeq& args) {

    PluginI* plugin = new PluginI(ic);
    return plugin;
}}

// Plugin interface.
PyEndpoint::PluginI::PluginI(const Ice::CommunicatorPtr& ic) {
    PyEval_InitThreads();
    Py_Initialize();
    _instance = new Instance(ic);
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

