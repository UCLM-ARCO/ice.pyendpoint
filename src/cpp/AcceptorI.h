/* -*- mode: c++; coding: utf-8; truncate-lines: true -*- */

//
// Copyright (c) 2014 Oscar Aceña. All rights reserved.
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

#ifndef PYENDPOINT_ACCEPTOR_I_H
#define PYENDPOINT_ACCEPTOR_I_H

#include <Ice/Acceptor.h>

#include "PyHandle.h"
#include "InstanceF.h"


namespace PyEndpoint {

class AcceptorI : public IceInternal::Acceptor, public IceInternal::NativeInfo {
public:

    virtual IceInternal::NativeInfoPtr getNativeInfo();
    virtual void close();
    virtual void listen();
    virtual IceInternal::TransceiverPtr accept();
    virtual std::string toString() const;

private:

    AcceptorI(const InstancePtr&, PyObjectPtr);
    virtual ~AcceptorI() {};

    friend class EndpointI;

    const InstancePtr _instance;
    PyObjectPtr _pyAcceptor;
};

}

#endif // PYENDPOINT_ACCEPTOR_I_H

