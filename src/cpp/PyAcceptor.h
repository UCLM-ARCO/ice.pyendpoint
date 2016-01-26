/* -*- mode: c++; coding: utf-8; truncate-lines: true -*- */

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

#ifndef _PYACCEPTOR_H_
#define _PYACCEPTOR_H_

#include "Ice/ProtocolInstanceF.h"
#include "Ice/Acceptor.h"
#include "Ice/Network.h"

#include "PyEndpointF.h"
#include "PyHandle.h"


namespace PyEndpoint {

class PyAcceptor : public IceInternal::Acceptor,
		   public IceInternal::NativeInfo {
public:

    virtual IceInternal::NativeInfoPtr getNativeInfo();
    virtual void close();
    virtual IceInternal::EndpointIPtr listen();

    virtual IceInternal::TransceiverPtr accept();
    virtual std::string protocol() const;
    virtual std::string toString() const;
    virtual std::string toDetailedString() const;

private:

    PyAcceptor(const PyEndpointIPtr&, const IceInternal::ProtocolInstancePtr&, PyObjectPtr&);
    virtual ~PyAcceptor();

    PyObjectPtr getPy() { return _pyAcceptor; };

    friend class PyEndpointI;

    PyEndpointIPtr _endpoint;
    IceInternal::ProtocolInstancePtr _instance;
    PyObjectPtr _pyAcceptor;
};

}

#endif /* _PYACCEPTOR_H_ */
