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

#ifndef PYENDPOINT_PLUGIN_I_H
#define PYENDPOINT_PLUGIN_I_H

#include "InstanceF.h"

#include <Ice/Plugin.h>
#include <Ice/CommunicatorF.h>

namespace PyEndpoint {

class PluginI : public Ice::Plugin {
public:

    PluginI(const Ice::CommunicatorPtr&, const std::string&);

    virtual void initialize();
    virtual void destroy();

private:

    InstancePtr _instance;
};

}

#endif // PYENDPOINT_PLUGIN_I_H
