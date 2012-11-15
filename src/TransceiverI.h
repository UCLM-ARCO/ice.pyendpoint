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

#ifndef PYENDPOINT_TRANSCEIVER_I_H
#define PYENDPOINT_TRANSCEIVER_I_H

#include "Ice/Transceiver.h"


namespace PyEndpoint {

class ConnectorI;

class TransceiverI : public IceInternal::Transceiver,
		     public IceInternal::NativeInfo {

public:

    virtual IceInternal::NativeInfoPtr getNativeInfo();
    virtual IceInternal::SocketOperation initialize();
    virtual void close();
    virtual bool write(IceInternal::Buffer&);
    virtual bool read(IceInternal::Buffer&);
    virtual std::string type() const;
    virtual std::string toString() const;
    virtual Ice::ConnectionInfoPtr getInfo() const;
    virtual void checkSendSize(const IceInternal::Buffer&, size_t);

private:

    TransceiverI(const InstancePtr&, PyObjectPtr pyTransceiver);
    virtual ~TransceiverI();
    friend class ConnectorI;

    const InstancePtr _instance;
};

typedef IceUtil::Handle<TransceiverI> TransceiverIPtr;

}

#endif // PYENDPOINT_TRANSCEIVER_I_H
