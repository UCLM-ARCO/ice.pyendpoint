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

#ifndef PLUGIN_H
#define PLUGIN_H

#include <Ice/Ice.h>
#include "PyHandle.h"
#include "InstanceF.h"

namespace PyEndpoint {

class PluginI : public Ice::Plugin {
public:

    PluginI(const Ice::CommunicatorPtr&);
    ~PluginI();

    void initialize();
    void destroy();

private:

    InstancePtr _instance;
};

}

#endif // PLUGIN_H
