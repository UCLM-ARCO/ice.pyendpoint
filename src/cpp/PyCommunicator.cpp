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

#include "PyCommunicator.h"
#include "PyFunctions.h"
#include "debug.h"

struct CommunicatorObject {
    PyObject_HEAD
    Ice::CommunicatorPtr* communicator;

    // This struct has more fields here, take care...
};

PyObjectPtr
PyEndpoint::createCommunicator(const Ice::CommunicatorPtr& ic) {
    trace();
    PyGILEnsurer e;
    
    PyObjectPtr IcePy = PyFunc::importModule("IcePy");
    PyObjectPtr Communicator = PyFunc::getClass(IcePy, "Communicator");
    PyObjectPtr pyIc = PyFunc::newInstance(Communicator);

    CommunicatorObject* _ic = reinterpret_cast<CommunicatorObject*>(pyIc.get());
    (*_ic->communicator)->destroy();

    _ic->communicator = new Ice::CommunicatorPtr(ic);

    return pyIc;
}
