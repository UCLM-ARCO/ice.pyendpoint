/* -*- mode: c++; coding: utf-8 -*- */

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
#include <Ice/CommunicatorF.h>
#include <Ice/ProtocolPluginFacade.h>

#include "Instance.h"
#include "EndpointI.h"

IceUtil::Shared*
IceInternal::upCast(PyEndpoint::Instance* p) {
    return p;
}

PyEndpoint::Instance::Instance(const Ice::CommunicatorPtr& ic) {
    __setNoDelete(true);

    _facade = IceInternal::getProtocolPluginFacade(ic);
    _facade->addEndpointFactory(new EndpointFactoryI(this));

    __setNoDelete(false);
}

void
PyEndpoint::Instance::initialize() {
}

void
PyEndpoint::Instance::destroy() {
    _facade = 0;
}


Ice::CommunicatorPtr
PyEndpoint::Instance::communicator() const {
    return _facade->getCommunicator();
}
