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

#ifndef _PYTRANSCEIVER_H_
#define _PYTRANSCEIVER_H_

#include "Ice/ProtocolInstanceF.h"
#include "Ice/Transceiver.h"
#include "Ice/Network.h"

#include "PyEndpointI.h"
#include "PyHandle.h"


namespace PyEndpoint {

class PyTransceiver : public IceInternal::Transceiver,
		      public IceInternal::NativeInfo {
public:

    virtual IceInternal::NativeInfoPtr getNativeInfo();

    virtual IceInternal::SocketOperation initialize(IceInternal::Buffer&, IceInternal::Buffer&, bool&);
    virtual IceInternal::SocketOperation closing(bool, const Ice::LocalException&);
    virtual void close();
    virtual IceInternal::EndpointIPtr bind();
    virtual IceInternal::SocketOperation write(IceInternal::Buffer&);
    virtual IceInternal::SocketOperation read(IceInternal::Buffer&, bool&);
    virtual std::string protocol() const;
    virtual std::string toString() const;
    virtual std::string toDetailedString() const;
    virtual Ice::ConnectionInfoPtr getInfo() const;
    virtual void checkSendSize(const IceInternal::Buffer&);
    virtual void setBufferSize(int rcvSize, int sndSize);

private:
    PyTransceiver(const IceInternal::ProtocolInstancePtr&, PyObjectPtr);
    PyTransceiver(const PyEndpointIPtr&, const IceInternal::ProtocolInstancePtr&, PyObjectPtr);
    virtual ~PyTransceiver() {};

    PyObjectPtr getPy() { return _pyTransceiver; };

    friend class PyEndpointI;
    friend class PyConnector;
    friend class PyAcceptor;

    PyEndpointIPtr _endpoint;
    const IceInternal::ProtocolInstancePtr _instance;
    PyObjectPtr _pyTransceiver;
};

}

#endif /* _PYTRANSCEIVER_H_ */
